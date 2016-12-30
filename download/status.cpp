/****************************************************************************************
** status.cpp is part of yoDownet
**
** Copyright 2012, 2013 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "status.h"
#include "cmath"
#include <qdebug.h>

Status::Status(QObject *parent) :
    QObject(parent)
{
    _remainingTime = "";

    _segFileAlreadyBytes = _fileAlreadyBytes = _bytesTotal = _bytesSegTotal = 0;
    _bytesReceived = _bytesSegReceived = 0;
    _downloadRate = _progress = 0;
    _dlMode = NewDownload;
    setDownloadStatus(Idle);
    _segidx = _segsum = 0; //-1???

    startTime();
}

//由于文件总大小不准确，这儿计算有问题
QString Status::remainingTime() const
{
    if(downloadStatus()  != Status::Downloading || progress() == 100)
        return "";

    qint64 br = this->bytesReceived();
    qDebug()<<"remainingTime bytesTotal="<<bytesTotal()<<", bytesReceived="<< br <<", speed="<<downloadRate();
    double timeRemaining = ((double)(bytesTotal() - (br+fileAlreadyBytes()))) / downloadRate();
    if(timeRemaining == 0){
        timeRemaining = 1;
    }

    QString timeRemainingString = tr("Sec");
    if(timeRemaining > 60){
        timeRemaining = timeRemaining / 60;
        timeRemainingString = tr("Min");
    }
    timeRemaining = std::floor(timeRemaining);
    return QString("%1 %2")
            .arg(timeRemaining)
            .arg(timeRemainingString);
}

void Status::setDownloadRate(qint64 speed){
    _downloadRate = speed;
}

qint64 Status::downloadRate() const{
    if(downloadStatus() != Status::Downloading || progress() == 100)
        return -1;

    return (int)_downloadRate;
}

QString Status::downloadModeString() const
{
    switch(_dlMode){
    case NewDownload:
        return tr("New Download");
        break;
    case ResumeDownload:
        return tr("Resume Download");
        break;
    }
    return QString();
}

QString Status::downloadStatusString() const{
    return transDownLoadString(_dlStatus);
}

QString Status::transDownLoadString(int status){
    switch(status){
    case Idle:
        return "Idle";
//    case Starting:
//        return "Starting";
    case Downloading:
        return "Downloading";
    case WaitCombine:
        return "Combining";
    case Failed:
        return "Failed";
    case Paused:
        return "Paused";
    case WaitTrans:
        return "Translating";
    case WaitStore:
        return "Storing";
    case Finished:
        return "Finished";
    }

    return QString();
}

// 进度计算的方式如下：
// cur，sum，   1/sum*curPercent + cur/sum
// 0, 8 = > 1/8 *curPercent + 0/8
// 1,8 =>  1/8*curPercent + 1/8
// 7,8 => 1/8*curPercent + 7/8
// 8,8 => complete!!!

//bytesReceived=>本次运行总共接收字节数，如果从50%开始下载，则不含之前已下载的部分
//bytesSegTotal=>同上，只是待接收的总字节数
void Status::updateFileStatus(qint64 recv, qint64 total)
{
    if(recv<=0 || total<=0)
        return;

    //总大小 数据库或首次获取数据时预估计算得到

    //设置当前段的总大小
    setBytesSegTotal(segFileAlreadyBytes()  + total);

    //设置当段接收数据(保存用，当切换新段时，将数据累加到_bytesReceived上)
    setBytesSegReceived(recv);

    //计算速度这儿不能用recv，如果仅仅针对单段而已没有任何问题，但针对多段时就一定有问题，新段的下载recv是从0开始逐渐递增的。
    //用bytesReceived()为 任务本次开始累计接收数据量，这样比较合理

    //平均速度
    //setDownloadRate((bytesReceived() + recv) * 1000.0 / _startTime->elapsed());

    //平均速度不能很好的反应下载状况，还是采用下面的方法
    setDownloadRate(recv * 1000.0 / _startTime->elapsed());

    qint64 segRecv = segFileAlreadyBytes() + recv;

    float prg  = 0;
    if(bytesSegTotal() != 0)
        prg = (segRecv*100.0) / bytesSegTotal();
    setProgress((prg +segIdx()*100)/segSum() );

    qDebug() << QString("updateFileStatus:"
                        "recv=%1,total=%2,"
                        "segidx=%3,segsum=%4,"
                        "segrecv=%5,segtotal=%6"
                        "segprg=%7,prg=%8")
                .arg(recv).arg(total)
                .arg(segIdx()).arg(segSum())
                .arg(segRecv).arg(bytesSegTotal())
                .arg(prg).arg(progress());

}

void Status::startTime()
{
    _startTime = new QTime();
    _startTime->start();
}

void Status::setSegFileAlreadyBytes(const qint64 fileAlreadyBytes)
{
    _segFileAlreadyBytes = fileAlreadyBytes;
}
qint64 Status::segFileAlreadyBytes() const{
    return _segFileAlreadyBytes;
}

void Status::setFileAlreadyBytes(const qint64 fileAlreadyBytes)
{
    _fileAlreadyBytes = fileAlreadyBytes;
}
qint64 Status::fileAlreadyBytes() const{
    return _fileAlreadyBytes;
}

void Status::setBytesTotal(const qint64 totalLength)
{
    _bytesTotal = totalLength;
}

qint64 Status::bytesTotal() const
{
    return _bytesTotal;
}

void Status::setBytesSegTotal(const qint64 total){
    _bytesSegTotal = total;
}

qint64 Status::bytesSegTotal() const{
    return _bytesSegTotal;
}


//多段累计字节
void Status::setBytesReceived(const qint64 completedLength)
{
    _bytesReceived = completedLength;
}
qint64 Status::bytesReceived() const
{
    return _bytesReceived;
}


//单段累计字节
void Status::setBytesSegReceived(const qint64 completedLength)
{
    _bytesSegReceived = completedLength;
}

qint64 Status::bytesSegReceived() const
{
    return _bytesSegReceived;
}



int Status::progress() const
{
    return _progress;
}
void Status::setProgress(int p){
    _progress = p;
}

void Status::setDownloadMode(const Status::DownloadMode dlMode)
{
    _dlMode = dlMode;
}

Status::DownloadMode Status::downloadMode() const
{
    return _dlMode;
}

void Status::setDownloadStatus(const Status::DownloadStatus dlStatus)
{
    _dlStatus = dlStatus;
}

Status::DownloadStatus Status::downloadStatus() const
{
    return _dlStatus;
}

void Status::setSegInfo(int segidx, int segsum){
    _segidx = segidx;
    _segsum = segsum;
}

int Status::segIdx() const
{
    return _segidx;
}

int Status::segSum() const
{
    return _segsum;
}

//切换段时更新数据
void Status::nextSeg(){
    //累计已接收的数据量
    setBytesReceived(bytesReceived()+bytesSegReceived());

    //设置所有已下载的数据数
    setFileAlreadyBytes(fileAlreadyBytes() + bytesSegTotal());

    //清 段数据
    setBytesSegReceived(0);
    setBytesSegTotal(0);
    setSegFileAlreadyBytes(0);    //doStart 会根据实际情况再次初始化

    setDownloadStatus(Downloading);

    //setBytesTotal();
    //setDownloadRate();
    //setDownloadMode();

    //重设
    _startTime->restart();
}

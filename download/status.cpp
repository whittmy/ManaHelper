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
    startTime();
}

QString Status::remainingTime() const
{
    double timeRemaining = ((double)(_bytesTotal - _bytesReceived)) / _downloadRate;
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

//QString Status::downloadRate() const
//{
//    int speedInt = (int)_downloadRate;
//    if(speedInt < 0)
//        speedInt = 0;
    
//    QString unit;
//    if(speedInt < 1024){
//        unit = tr("bytes/sec");
//    }else if(speedInt < 1024*1024){
//        speedInt /= 1024;
//        unit = tr("KB/sec");
//    }else{
//        speedInt /= 1024*1024;
//        unit = tr("MB/sec");
//    }
//    return QString("%1 %2").arg(speedInt).arg(unit);

//}

qint64 Status::downloadRate() const{
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
    case Starting:
        return "Starting";
    case Downloading:
        return "Downloading";
    case WaitTrans:
        return "Finished";
    case Failed:
        return "Failed";
    case Paused:
        return "Paused";
    case Transing:
        return "Translating";
    case Storing:
        return "Storing";
    }

    return QString();
}

void Status::updateFileStatus(qint64 bytesReceived, qint64 bytesTotal)
{
    if (_fileAlreadyBytes == 0) {
        _fileAlreadyBytes = 1;
    }

    if (bytesTotal <= 0) {
        bytesTotal = 0;
    }

    _bytesTotal = _fileAlreadyBytes+bytesTotal;
    _bytesReceived = _fileAlreadyBytes+bytesReceived;
    _progress = (_bytesTotal==0)? 0 : (_bytesReceived * 100)/_bytesTotal; //notice the case(_bytesTotal==0)
    _downloadRate = bytesReceived * 1000.0 / _startTime->elapsed();

    qDebug() << QString("updateFileStatus:bytesReceived=%1,_fileAlreadyBytes=%2,bytesTotal=%3,progress=%4")
                .arg(bytesReceived)
                .arg(_fileAlreadyBytes)
                .arg(bytesTotal)
                .arg(_progress);

}

void Status::startTime()
{
    _startTime = new QTime();
    _startTime->start();
}

void Status::setFileAlreadyBytes(const qint64 fileAlreadyBytes)
{
    _fileAlreadyBytes = fileAlreadyBytes;
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

void Status::setBytesReceived(const qint64 completedLength)
{
    _bytesReceived = completedLength;
}

qint64 Status::bytesReceived() const
{
    return _bytesReceived;
}

int Status::progress() const
{
    return _progress;
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

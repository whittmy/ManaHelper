/****************************************************************************************
** status.h is part of yoDownet
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

#ifndef STATUS_H
#define STATUS_H

#include <QObject>
#include <QTime>
#include <QUuid>

class Status : public QObject
{
    Q_OBJECT
    Q_ENUMS(DownloadMode)
    Q_ENUMS(DownloadStatus)

public:
    explicit Status(QObject *parent = 0);

    enum DownloadMode{
        NewDownload,
        ResumeDownload
    };

    enum DownloadStatus{
        Idle,
        Failed,
        Paused,
        Downloading,
        WaitCombine, //下载完成等待合并
        WaitTrans, //等待转码
        WaitStore, //等待存储
        Finished //真正完成
    };
    static QString transDownLoadString(int status) ;
    QString downloadStatusString() const;
    QString remainingTime() const;
    QString downloadModeString() const;

    //already>>>
    void setSegFileAlreadyBytes(const qint64 fileAlreadyBytes);
    qint64 segFileAlreadyBytes() const;

    void setFileAlreadyBytes(const qint64 fileAlreadyBytes);
    qint64 fileAlreadyBytes() const;
    //<<<

    //total>>>>
    void setBytesTotal(const qint64 totalLength);
    qint64 bytesTotal() const;

    void setBytesSegTotal(const qint64 total);
    qint64 bytesSegTotal() const;
    //int progressSeg() const;
    //<<<<

    //receive>>
    void setBytesReceived(const qint64 completedLength);
    qint64 bytesReceived() const;

    void setBytesSegReceived(const qint64 completedLength);
    qint64 bytesSegReceived() const;
    //<<<


    int progress() const;
    void setProgress(int p);

    void setDownloadMode(const DownloadMode dlMode);
    DownloadMode downloadMode() const;

    void setDownloadStatus(const DownloadStatus dlStatus);
    DownloadStatus downloadStatus() const;

    void setDownloadRate(qint64 speed);
    qint64 downloadRate() const;

    void setSegInfo(int segidx, int segsum);
    int segSum() const;
    int segIdx() const;

    void nextSeg(); //段切换时要充值部分数据

public slots:
    void startTime();
    void updateFileStatus(qint64 bytesReceived, qint64 bytesSegTotal);

private:
    QString _remainingTime;

    //来源：1.读数据库；2.预估值(首次)=首段*段数
    //目的：1.显示；2.计算剩余时间(总数-已下载数 除以 速度)
    qint64 _bytesTotal;

    //用于计算当前段的进度 ： @2+(当前段已接收)/@1
    //@2: 任务启动前该段已下载的字节数
    //@1：当前段的总大小=@2+待接收
    qint64  _bytesSegTotal,_segFileAlreadyBytes;


    //@1: 任务本次启动累计接收数 ==>>也会计算 速度
    //@2: 任务启动前 已下载的所有段数据总和
    //结合 _bytesTotal计算剩余时间
    qint64 _bytesReceived, _fileAlreadyBytes;

    qint64 _bytesSegReceived; //用于备份当前段已动态接收的数据，为_bytesReceived值的计算提供必要条件

    int _downloadRate; //要根据本次运行中累计所接收的字节以及耗时来计算
    int _progress; //总进度
    QTime *_startTime;
    DownloadMode _dlMode;
    DownloadStatus _dlStatus;

    int _segidx, _segsum;

};

#endif // STATUS_H

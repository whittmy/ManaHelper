﻿#ifndef DLOADER_COMMON_H
#define DLOADER_COMMON_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSignalMapper>
#include <QUrl>
#include <QHash>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <download/download.h>
#include "download/status.h"
#include "util/logme.h"
#include <QTimer>

//每个任务的下载器
class DLoader_common : public QObject
{
    Q_OBJECT
public:
    ~DLoader_common();

    static DLoader_common* Instance();
    static void free();

    enum{
        ACTION_PAUSE,ACTION_DEL, ACTION_FINISH, ACTION_UPDATE,ACTION_RESUME
    };


private:
 explicit DLoader_common(QObject *parent = 0);

signals:
    void sg_dlInitialed(const Download *download);
    void sg_dlPaused(const Download *download);
    void sg_dlResumed(const Download *download);
    void sg_dlUpdated(const Download *download);
    void sg_dlRemoved(const Download *download);
    void sg_dlFinished(const Download *download);

    //删除任务即包含了任务对应的文件
   // void sg_taskReadyToRemove(Download *download);
    //void sg_downloadDoesNotExistToRemove(const QUuid &uuid);

public:
    //addDownload兼start操作
    void doStart(const Download *dl);
    void doPause(const QUuid &uuid);
    void doRemove(const QUuid &uuid);
    void freeReplyInfo(QNetworkReply* reply);
    void doSaveData(int type, const Download*dl);
private slots:
    void slot_replyMetaDataChanged(QObject *currentReply);
    void slot_httpReadyRead(QObject *currentReply);
    void slot_httpFinished(QObject *currentReply);
//    void slot_progress(qint64 recv, qint64 total);

    void onTimerOut();

private:
    void removeFile(const Download *download);

public:
    int getTaskingCnt(){return _downloadHash->size();} //获取正在下载的任务数

private:
    QNetworkAccessManager _manager;
    //QNetworkReply *_reply;
    QSignalMapper *_readyReadSignalMapper, *_metaChangedSignalMapper, *_finishedSignalMapper;
    QHash<QNetworkReply*, Download*> *_downloadHash;
    QHash<QUrl, Status*> *_statusHash;
    QHash<QUrl, QUrl> *_redirectHash;
    QUrl redirectUrl(const QUrl &possibleRedirectUrl, const QUrl &oldRedirectUrl) const;
    LogMe* _logger;
    static DLoader_common* mInstance;

    bool _bUserInterupt;

    QTimer *mTimer;
};

#endif // DLOADER_USUAL_H

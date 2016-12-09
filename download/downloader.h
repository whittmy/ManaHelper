/****************************************************************************************
** yodownet.h is part of yoDownet
**
** Copyright 2012, 2013, 2014 Alireza Savand <alireza.savand@gmail.com>
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

#ifndef YODOWNET_H
#define YODOWNET_H

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
#include "backend/logme.h"


//每个任务的下载器
class DownLoader : public QObject
{
    Q_OBJECT
public:
    explicit DownLoader(QObject *parent = 0);

signals:
    void downloadInitialed(const Download *download);
    void downloadPaused(const Download *download);
    void downlaodResumed(const Download *download);
    void downloadUpdated(const Download *download);
    void downloadRemoved(const QString &fileName);
    void downloadFinished(const QString &msg);
    void fileReadyToRemove(QFile *file);
    void downloadDoesNotExistToRemove(const QUuid &uuid);

public slots:
    //addDownload兼start操作
    void addDownload(const int ID, const QString &url, const QUuid &uuid=QUuid(), const QString &fileName=QString());
    void pauseDownload(const QUuid &uuid);
    void removeDownload(const QUuid &uuid);

private slots:
    void replyMetaDataChanged(QObject *currentReply);
    void startRequest(Download *newDownload);
    void httpReadyRead(QObject *currentReply);
    void httpFinished(QObject *currentReply);
    // TODO: Removing file can be done in `Download` class.
    void removeFile(QFile *file);

public:
    int getTaskingCnt(){return _downloadHash->size();} //获取正在下载的任务数

private:
    QNetworkAccessManager _manager;
    QNetworkReply *_reply;
    QSignalMapper *_readyReadSignalMapper;
    QSignalMapper *_metaChangedSignalMapper;
    QSignalMapper *_finishedSignalMapper;
    QHash<QNetworkReply*, Download*> *_downloadHash;
    QHash<QUrl, Status*> *_statusHash;

    QUrl redirectUrl(const QUrl &possibleRedirectUrl, const QUrl &oldRedirectUrl) const;
    LogMe* _logger;
};

#endif // YODOWNET_H

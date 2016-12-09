/****************************************************************************************
** DownLoader.cpp is part of DownLoader
**
** Copyright 2012, 2013, 2014 Alireza Savand <alireza.savand@gmail.com>
**
** DownLoader is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** DownLoader is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "downloader.h"
#include "util/paths.h"


DownLoader::DownLoader(QObject *parent) :
    QObject(parent),
    _downloadHash(new QHash<QNetworkReply*, Download*>),
    _logger(new LogMe(this)),
    _statusHash( new QHash<QUrl, Status*>)
{
    connect(this, SIGNAL(fileReadyToRemove(QFile*)), this, SLOT(removeFile(QFile*)));
}

void DownLoader::addDownload(const int ID, const QString &url, const QUuid &uuid, const QString &fileName)
{
    _logger->debug("addDownload");
    _logger->info(QString("%1,%2,%3,%4").arg(ID).arg(url).arg(uuid.toString()).arg(fileName));
    Download *newDownload = new Download(this);

    if (newDownload->newDownload(ID, QUrl(url), uuid, fileName)) {
        this->startRequest(newDownload);
    }
}

// TODO: emit signal when download hash is empty OR no download has been found
void DownLoader::pauseDownload(const QUuid &uuid)
{
    _logger->info(QString("Pausing download [%1]").arg(uuid.toString()));

    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->begin();
    while(i != _downloadHash->end()){
        if(i.value()->uuid() == uuid){
            _logger->info(QString("Found download [%1] in hash.").arg(uuid.toString()));

            i.value()->file()->write(i.key()->readAll());
            Status *status = _statusHash->find(i.key()->url()).value();
            status->setDownloadStatus(Status::Paused);

            _logger->info(QString("Emit 'downloadPaused' signal for [%1]").arg(uuid.toString()));
            emit downloadPaused(i.value());

            i.key()->abort();
            //i.key()->close();   //用了close就崩溃，我崩溃..
            _logger->debug("pauseDownload network-abort...");
            break;
        }
    }
    _logger->info("end pauseDownload");
}

void DownLoader::removeDownload(const QUuid &uuid)
{
    _logger->info(QString("Start Removing [%1] via downloader engine").arg(uuid.toString()));

    if(_downloadHash->isEmpty()){
        _logger->info(QString("Download hash is empty, emiting `fileReadyToRemove` singal to remove download with UUID: [%1]").arg(uuid.toString()));

        emit this->downloadDoesNotExistToRemove(uuid);
        return;
    }
    foreach(Download *download, _downloadHash->values()){
        if(download->uuid() == uuid){
            _logger->info(QString("Found download [%1] in hash.").arg(uuid.toString()));

            QNetworkReply *reply = _downloadHash->key(download);
            emit pauseDownload(reply->url().toString());
            emit fileReadyToRemove(download->file());
            break;
        }
    }
}

void DownLoader::replyMetaDataChanged(QObject *currentReply)
{
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    QNetworkReply *reply = i.key();
    Status *status = _statusHash->find(reply->url()).value();

    status->setBytesTotal(reply->header(QNetworkRequest::ContentLengthHeader).toULongLong());
}

void DownLoader::startRequest(Download *newDownload)
{
    _logger->debug("startRequest");
    _logger->info(QString("Starting request for '%1'").arg(newDownload->url().toString()));

    //这儿的断点续传的思路是，根据已下载的临时文件的大小作为断点，不用用自己记录的下载数据，可以避免数据不一致的麻烦。
    QNetworkRequest request(newDownload->url().toString());
    request.setRawHeader("Range", QByteArray("bytes=SIZE-").replace("SIZE", QVariant(newDownload->file()->size()).toByteArray()));

    newDownload->status()->setFileAlreadyBytes(newDownload->file()->size());

    _reply = _manager.get(request);

    newDownload->status()->setDownloadStatus(Status::Starting);

    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->insert(_reply, newDownload);
    QHash<QUrl, Status*>::iterator statusIt = _statusHash->insert(i.key()->url(), newDownload->status());

    if (statusIt.value()->downloadMode() == Status::NewDownload) {
        emit downloadInitialed(i.value());
    } else if (statusIt.value()->downloadMode() == Status::ResumeDownload) {
        emit downlaodResumed(i.value());
    }

    // Initialing `SignalMapper`
    _logger->info(QString("Initialing `SignalMapper`s for `%1`").arg(newDownload->url().toString()));

    _readyReadSignalMapper = new QSignalMapper(this);
    _metaChangedSignalMapper = new QSignalMapper(this);
    _finishedSignalMapper = new QSignalMapper(this);

    // Setup mapping on `SignalMapper`
    _logger->info(QString("Setup mapping on signal mappers for `%1`").arg(newDownload->url().toString()));

    _readyReadSignalMapper->setMapping(i.key(), i.key());
    _metaChangedSignalMapper->setMapping(i.key(), i.key());
    _finishedSignalMapper->setMapping(i.key(), i.key());

    // Connecting signals to the `receivers` via `SignalMapper`
    _logger->info(QString("Connecting signals to receivers via signals mappers for `%1`").arg(newDownload->url().toString()));

    //以下这4个信号，是QNetworkReply的内在的signal， //和map槽关联
    connect(i.key(), SIGNAL(readyRead()), _readyReadSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(metaDataChanged()), _metaChangedSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(finished()), _finishedSignalMapper, SLOT(map()));
    //downloadProgress(bytesReceived, bytesTotal) ==>>> 触发status中的updateFileStatus
    connect(i.key(), SIGNAL(downloadProgress(qint64,qint64)), statusIt.value(), SLOT(updateFileStatus(qint64, qint64)));

    //QSignalMapper用于一组同类object的信号管理
    connect(_readyReadSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(httpReadyRead(QObject*)));
    connect(_metaChangedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(replyMetaDataChanged(QObject*)));
    connect(_finishedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(httpFinished(QObject*)));
}

//网络读数据的内定槽 httpReadyRead，会频繁被调用，下载是一段段下载的，所以准备好就开始读取
void DownLoader::httpReadyRead(QObject *currentReply)
{
    _logger->debug("httpReadyRead") ;
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    QNetworkReply *reply = i.key();
    Download *download = i.value();

    if (download->file()) {
        Status *status = download->status();
        download->file()->write(reply->readAll());
        status->setDownloadStatus(Status::Downloading);

        emit downloadUpdated(download);
    }
}

void DownLoader::httpFinished(QObject *currentReply)
{
    _logger->debug("httpFinished");
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    Download *download = i.value();
    QNetworkReply *reply = i.key();
    Status *status = _statusHash->find(reply->url()).value();

    _logger->info(QString("HTTP request has finished for '%1'").arg(download->url().toString()));


    QVariant possibleRedirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    // We'll deduct if the redirection is valid in the redirectUrl function
    download->setUrlRedirectedTo(possibleRedirectUrl.toUrl());

    if (!download->urlRedirectedTo().isEmpty()) {
        _logger->info(QString("[%1] redirected to %2").arg( download->uuid().toString(), download->urlRedirectedTo().toString()) );
        download->setUrl(download->urlRedirectedTo());
        QString fileName = download->name();
        this->removeFile(download->file());
        this->addDownload(download->ID(), download->url().toString(), download->uuid(), fileName);
    } else {
        /*
         * We weren't redirected anymore
         * so we arrived to the final destination...
         */
        download->urlRedirectedTo().clear();
    }

    download->file()->flush();
    download->file()->close();
    download->setFile(0);

    reply->deleteLater(); //!!!!!

    if(status->downloadStatus() != Status::Paused) {
        _logger->info("HTTP request has finished, I'm done with downloading.");
        status->setDownloadStatus(Status::Finished);
        emit downloadFinished(download->name());
    }

    // Oh let's emit this mother fucker!
    emit downloadUpdated(download);

    _downloadHash->remove(reply);
}

void DownLoader::removeFile(QFile *file)
{
    _logger->info(QString("Removing file: [%1]").arg(file->fileName()));

    const QString fileName = file->fileName();
    if(!file->remove()) {
        _logger->error(QString("Couldn't remove [%1]. Error: %2").arg(file->fileName(), file->errorString()));
        return;
    }
    file = 0;
    emit downloadRemoved(fileName);
}

QUrl DownLoader::redirectUrl(const QUrl &possibleRedirectUrl, const QUrl &oldRedirectUrl) const
{
    QUrl redirectUrl;
    /*
     * Check if the URL is empty and
     * that we aren't being fooled into infinite redirect loop.
     * We could also keep track of how many redirects we have been to
     * and set a limit to it, but we'll leave that for now.
     */
    if (!possibleRedirectUrl.isEmpty() && possibleRedirectUrl != oldRedirectUrl) {
        redirectUrl = possibleRedirectUrl;
    }

    return redirectUrl;
}

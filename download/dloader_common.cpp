#include "dloader_common.h"
#include "util/paths.h"

//静态成员变量初始化
DLoader_common* DLoader_common::mInstance = NULL;


DLoader_common::DLoader_common(QObject *parent) :
    QObject(parent),
    _downloadHash(new QHash<QNetworkReply*, Download*>),
    _logger(new LogMe(this)),
    _statusHash( new QHash<QUrl, Status*>)
{
    _logger->info(QString("Initialing `SignalMapper`s"));
    _readyReadSignalMapper = new QSignalMapper(this);
    _metaChangedSignalMapper = new QSignalMapper(this);
    _finishedSignalMapper = new QSignalMapper(this);


}


DLoader_common::~DLoader_common(){
    delete _logger;
    delete _downloadHash;
    delete _statusHash;

    delete _readyReadSignalMapper;
    delete _metaChangedSignalMapper;
    delete _finishedSignalMapper;
}

DLoader_common* DLoader_common::Instance(){
    if(mInstance == NULL)
        mInstance = new DLoader_common();
    return mInstance;
}

void DLoader_common::free(){
    if(mInstance != NULL)
        delete mInstance;
}

//新任务或者恢复下载，实际上相当于重新初始化任务的下载信息及状态
//那在暂停等操作时，得清除指定任务的网络状态吧(如 reply的释放，hash信息的删除等)！！！
void DLoader_common::doStart(Download* newDownload)
{
    _logger->info(QString("doStart for '%1'").arg(newDownload->url().toString()));
    _logger->info(QString("curSeg:%1, %2").arg(newDownload->getCurSegIdx()).arg(newDownload->getCurSegUrl().toString()));

    _bUserInterupt = false;

    //若所有段已下载完成
    if(newDownload->bSegEnd()/*|| newDownload->url().isEmpty()*/){
        newDownload->status()->setDownloadStatus(Status::WaitTrans);
        slot_httpFinished(newDownload);
        return;
    }


    //这儿的断点续传的思路是，根据已下载的临时文件的大小作为断点，不用用自己记录的下载数据，可以避免数据不一致的麻烦。
    //取当前段url进行下载
    //QNetworkRequest request(newDownload->url().toString());
    QNetworkRequest request(newDownload->getCurSegUrl().toString());
    request.setRawHeader("Range", QByteArray("bytes=SIZE-").replace("SIZE", QVariant(newDownload->file()->size()).toByteArray()));

    //多段url，计算总文件大小是个难题
    newDownload->status()->setFileAlreadyBytes(newDownload->file()->size());

    QNetworkReply *reply = _manager.get(request);
    newDownload->status()->setDownloadStatus(Status::Starting);

    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->insert(reply, newDownload);
    QHash<QUrl, Status*>::iterator statusIt = _statusHash->insert(i.key()->url(), newDownload->status());

    if (statusIt.value()->downloadMode() == Status::NewDownload) {
        emit sg_dlInitialed(i.value());
    } else if (statusIt.value()->downloadMode() == Status::ResumeDownload) {
        emit sg_dlResumed(i.value());
    }

    //批量映射、关联信号槽
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
    connect(_readyReadSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(slot_httpReadyRead(QObject*)));
    connect(_metaChangedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(slot_replyMetaDataChanged(QObject*)));
    connect(_finishedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(slot_httpFinished(QObject*)));
}

// TODO: emit signal when download hash is empty OR no download has been found
void DLoader_common::doPause(const QUuid &uuid)
{
    _logger->info(QString("Pausing download [%1]").arg(uuid.toString()));
    if(_downloadHash->isEmpty()){
        //!!!
        return;
    }

    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->begin();
    while(i != _downloadHash->end()){
        if(i.value()->uuid() == uuid){
            _logger->info(QString("Found download [%1] in hash.").arg(uuid.toString()));


            i.value()->file()->write(i.key()->readAll());
            Status *status = _statusHash->find(i.key()->url()).value();
            status->setDownloadStatus(Status::Paused);

            _logger->info(QString("Emit 'downloadPaused' signal for [%1]").arg(uuid.toString()));
            emit sg_dlPaused(i.value());

            _bUserInterupt = true;
            i.key()->abort();
            //i.key()->close();   //用了close就崩溃，我崩溃..

            //释放
            freeReplyInfo(i.key());


            _logger->debug("pauseDownload network-abort...");
            return;
        }
    }

    _logger->info("had no pauseDownload");
    //未发现！
}

void DLoader_common::freeReplyInfo(QNetworkReply* reply){
    if(reply == NULL)
        return;
    _downloadHash->remove(reply);
    _statusHash->remove(reply->url()); //QNetworkReply获取url
    _readyReadSignalMapper->removeMappings(reply);
    _metaChangedSignalMapper->removeMappings(reply);
    _finishedSignalMapper->removeMappings(reply);
    reply->deleteLater();
}

void DLoader_common::doRemove(const QUuid &uuid)
{
    _logger->info(QString("Start Removing [%1] via downloader engine").arg(uuid.toString()));

    if(_downloadHash->isEmpty()){
        _logger->info(QString("Download hash is empty, emiting `fileReadyToRemove` singal to remove download with UUID: [%1]").arg(uuid.toString()));

        //emit this->sg_downloadDoesNotExistToRemove(uuid);
        return;
    }

    foreach(Download *download, _downloadHash->values()){
        if(download->uuid() == uuid){
            _logger->info(QString("Found download [%1] in hash.").arg(uuid.toString()));

            //QNetworkReply *reply = _downloadHash->key(download);
            //emit doPause(reply->url().toString());

            //先暂停该任务，并释放相关资源
            doPause(uuid);

            //删除文件，并发送信号
            //emit sg_taskReadyToRemove(download);
            removeFile(download);
            return;
        }
    }

    //没有发现
     //emit this->sg_downloadDoesNotExistToRemove(uuid);
}

//对应QNetworkReply中的某状态,
//设置网络文件总大小, >>>每次启动须先读数据库中的大小<<<
void DLoader_common::slot_replyMetaDataChanged(QObject *currentReply)
{
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    QNetworkReply *reply = i.key();
    Status *status = _statusHash->find(reply->url()).value();

    //文件大小计算1次即可，多段的计算比较粗略， 第一段大小乘以段数
    //为避免总大小经常变化,再恢复下载时，最后传入文件总大小
    qint64 size = reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
    if(status->bytesTotal() == 0){
        status->setBytesTotal(size * i.value()->getSegCnt());
    }

    //对于当前段的大小，还是要设置的,便于统计当前段的进度
    status->setBytesSegTotal(size);
}

//对应QNetworkReply中的某状态
//网络读数据的内定槽 httpReadyRead，会频繁被调用，下载是一段段下载的，所以准备好就开始读取
//实际上它与downloadProgress有密切关系，近乎是同步的，但是后者直接更新download中的Status的状态了，
//而该函数可以向该类之外提供数据变化的接口(信号sg_dlUpdated )
void DLoader_common::slot_httpReadyRead(QObject *currentReply)
{
    _logger->debug("httpReadyRead") ;
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    QNetworkReply *reply = i.key();
    Download *download = i.value();

    if (download->file()) {
        Status *status = download->status();
        download->file()->write(reply->readAll());
        status->setDownloadStatus(Status::Downloading);

        emit sg_dlUpdated(download);
    }
}

//对应QNetworkReply中的某状态
//当强制中断网络连接时，也会触发该槽对应的信号
void DLoader_common::slot_httpFinished(QObject *currentReply)
{
    _logger->debug("httpFinished");
    if(typeid(*currentReply) == typeid(Download)){
        //已完成
        emit sg_dlFinished(qobject_cast<Download*>(currentReply));
        return;
    }

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
/*  即便重定向，也不可置 _file为NULL，否则如何下载数据将往哪儿存？？？
        //this->removeFile(download->file());
        if(download->file() != NULL){
            download->file()->close();
            download->file()->remove();
            download->setFile(0);
        }
        freeReplyInfo(reply);
*/
        //重新开始
        this->doStart(download);
        return;

    } else {
        /*
         * We weren't redirected anymore
         * so we arrived to the final destination...
         */
        download->urlRedirectedTo().clear();
    }



    //reply->deleteLater(); //!!!!!

    //若非用户中断的自然完成，则认为当前段已完成。
    if(!_bUserInterupt){
        _logger->info(QString("seg-%1 had completed!").arg(download->getCurSegIdx()));
        download->doNextSeg();

        //继续开始新段下载
        doStart(download);
    }
    else{
        //暂停等
        download->file()->flush();
        download->file()->close();
        download->setFile(0);

        //完全释放
        freeReplyInfo(reply);
    }

    //判断文件大小以确定是否下载完成
//    if(/*status->downloadStatus() != Status::Paused*/download->bFinished()) {
//        _logger->info("HTTP request has finished, I'm done with downloading.");
//        status->setDownloadStatus(Status::WaitTrans);
//        emit sg_dlFinished(download);
//    }

    //?????? 未名原因停止！！，暂不处理，
    //_logger->error("http finished unknown!!!");
    // Oh let's emit this mother fucker!
    //emit sg_dlUpdated(download);

    //_downloadHash->remove(reply);
}

//删除任务中的文件
void DLoader_common::removeFile(Download *download)
{
    _logger->info(QString("Removing file: [%1]").arg(download->file()->fileName()));

    if(!download->file()->remove()) {
        _logger->error(QString("Couldn't remove [%1]. Error: %2").arg(download->file()->fileName(), download->file()->errorString()));
        return;
    }
    download->setFile(0);
    emit sg_dlRemoved(download);
}

QUrl DLoader_common::redirectUrl(const QUrl &possibleRedirectUrl, const QUrl &oldRedirectUrl) const
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

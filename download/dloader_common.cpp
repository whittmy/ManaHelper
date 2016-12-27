#include "dloader_common.h"
#include "util/paths.h"

//静态成员变量初始化
DLoader_common* DLoader_common::mInstance = NULL;

/*
 Usage:

 Step1:
    Download *newDownload = new Download(this);
    connect(newDownload, SIGNAL(sig_onTaskAdded(Download*)), this, SLOT(slot_onTaskAdded(Download*)));

    //当添加完成后，会自动触发slot_onTaskAdded函数
    newDownload->newDownload(ID, url, uuid, fileName);

 Step2:
    void DownLoader::slot_onTaskAdded(Download *download){
        _logger->info("slot_onTaskAdded");
        if(download->getCurSegUrl().isEmpty()){
            _logger->error("empty url");
            return;
        }
        DLoader_common *m_DLoader = DLoader_common::Instance();
        mDloader->doStart(download);
    }
 Step3: signals
    void sg_dlInitialed(const Download *download);
    void sg_dlPaused(const Download *download);
    void sg_dlResumed(const Download *download);
    void sg_dlUpdated(const Download *download);
    void sg_dlRemoved(const Download *download);
    void sg_dlFinished(const Download *download);

 Step4:
    DLoader_common::free();
 */



DLoader_common::DLoader_common(QObject *parent) :
    QObject(parent),
    _downloadHash(new QHash<QNetworkReply*, Download*>),
    _logger(new LogMe(this)),
    _statusHash( new QHash<QUrl, Status*>),
    _redirectHash(new QHash<QUrl, QUrl>)
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
    delete _redirectHash;

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
    _logger->info(QString("doStart for main-url: %1 ").arg(newDownload->url().toString()));
    _logger->info(QString("curSeg:%1=>%2").arg(newDownload->getCurSegIdx()).arg(newDownload->getCurSegUrl().toString()));

    _bUserInterupt = false;

    //若所有段已下载完成,则任务完成
    if(newDownload->bSegEnd()){
        _logger->info("end of seg, task-complated!!");
        newDownload->status()->setDownloadStatus(Status::WaitCombine);
        slot_httpFinished(newDownload);
        return;
    }

    if(!newDownload->bfileValid()){
        _logger->info("file is not valid...");
        exit(0);
    }
    //这儿的断点续传的思路是，根据已下载的临时文件的大小作为断点，不用用自己记录的下载数据，可以避免数据不一致的麻烦。
    //取当前段url进行下载
    //QNetworkRequest request(newDownload->url().toString());

    newDownload->slot_httpError(QNetworkReply::NoError, "");//reset error flag

    QNetworkRequest request(newDownload->getCurSegUrl().toString());
    _logger->info(QString("get-cur-seg_alreadybyte:%1").arg(newDownload->getFileSize()));
    request.setRawHeader("Range", QByteArray("bytes=SIZE-").replace("SIZE", QVariant(newDownload->getFileSize()).toByteArray()));

    //多段url，计算总文件大小是个难题
    newDownload->status()->setFileAlreadyBytes(newDownload->getFileSize()/*newDownload->file()->size()*/);

    QNetworkReply *reply = _manager.get(request);
    newDownload->status()->setDownloadStatus(Status::Starting);

    //将每一个reply-download, reply'url- download'status 关联。
    //目的是根据reply找到download的相关状态，这些reply的url对应download中的分段url(或其重定向)
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->insert(reply, newDownload);
    QHash<QUrl, Status*>::iterator statusIt = _statusHash->insert(i.key()->url(), newDownload->status());

    if (statusIt.value()->downloadMode() == Status::NewDownload) {
        emit sg_dlInitialed(i.value());
        _logger->info("emit sg_dlInitialed");
    } else if (statusIt.value()->downloadMode() == Status::ResumeDownload) {
        emit sg_dlResumed(i.value());
        _logger->info("emit sg_dlResumed");
    }

    //批量映射、关联信号槽
    _readyReadSignalMapper->setMapping(i.key(), i.key());
    _metaChangedSignalMapper->setMapping(i.key(), i.key());
    _finishedSignalMapper->setMapping(i.key(), i.key());

    // Connecting signals to the `receivers` via `SignalMapper`
    //以下这4个信号，是QNetworkReply的内在的signal， //和map槽关联
    connect(i.key(), SIGNAL(readyRead()), _readyReadSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(metaDataChanged()), _metaChangedSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(finished()), _finishedSignalMapper, SLOT(map()));

    //downloadProgress(bytesReceived, bytesTotal) ==>>> 触发status中的updateFileStatus
    connect(i.key(), SIGNAL(downloadProgress(qint64,qint64)), statusIt.value(), SLOT(updateFileStatus(qint64, qint64)));
    //????connect(i.key(), SIGNAL(error(QNetworkReply::NetworkError)), i.value(), SLOT(slot_httpError(QNetworkReply::NetworkError, )));

    //QSignalMapper用于一组同类object的信号管理
    connect(_readyReadSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(slot_httpReadyRead(QObject*)));
    connect(_metaChangedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(slot_replyMetaDataChanged(QObject*)));
    connect(_finishedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(slot_httpFinished(QObject*)));
    _logger->info("end doStart!!");
}

// TODO: emit signal when download hash is empty OR no download has been found
void DLoader_common::doPause(const QUuid &uuid)
{
    _logger->info(QString("doPause [%1]").arg(uuid.toString()));
    if(_downloadHash->isEmpty()){
        //!!!
        _logger->info("_downloadHash is empty, return");
        return;
    }

    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->begin();
    while(i != _downloadHash->end()){
        if(i.value()->uuid() == uuid){
            _logger->info(QString("Found download [%1] in hash.begin to stop it").arg(uuid.toString()));

            i.value()->writeFile(i.key()->readAll());
            Status *status = _statusHash->find(i.key()->url()).value();
            status->setDownloadStatus(Status::Paused);

            _logger->info(QString("Emit 'sg_dlPaused' for [%1]").arg(uuid.toString()));
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
    reply->close();
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

    qint64 size = reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
    if(size == 0)
        return;
    _logger->info(QString("enter - slot_replyMetaDataChanged, size=%1").arg(size));

    Status *status = _statusHash->find(reply->url()).value();
    Download *download = i.value();

    status->setSegInfo(download->getCurSegIdx(), download->getSegCnt());

    //文件总大小为粗略计算(第一段的大小*段数)，仅作显示用,不参与任何计算。
    if(status->bytesTotal() == 0 && download->getCurSegIdx()==0){
        status->setBytesTotal(size * download->getSegCnt());
    }

    //对于当前段的大小，还是要设置的,便于统计当前段的进度
    //进度计算比较粗略，按照 段号-段数以及当前段的进度来计算,详见Status;
    status->setBytesSegTotal(size);
}

//对应QNetworkReply中的某状态
//网络读数据的内定槽 httpReadyRead，会频繁被调用，下载是一段段下载的，所以准备好就开始读取
//实际上它与downloadProgress有密切关系，近乎是同步的，但是后者直接更新download中的Status的状态了，
//而该函数可以向该类之外提供数据变化的接口(信号sg_dlUpdated )
void DLoader_common::slot_httpReadyRead(QObject *currentReply)
{
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    QNetworkReply *reply = i.key();
    Download *download = i.value();

    if (download->bfileValid()) {
        Status *status = download->status();
        download->writeFile(reply->readAll());
        status->setDownloadStatus(Status::Downloading);
        emit sg_dlUpdated(download);
    }
}


//对应QNetworkReply中的某状态
//当强制中断网络连接时，也会触发该槽对应的信号
void DLoader_common::slot_httpFinished(QObject *currentReply)
{
    if(typeid(*currentReply) == typeid(Download)){
        //已完成
        Download *dl = qobject_cast<Download*>(currentReply);
        _logger->info("task-completed for url:"+dl->url().toString());
        emit sg_dlFinished(dl);
        return;
    }

    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    if(i == _downloadHash->end()){
        //here Caution!!!, very important
        //_logger->info("had found no this reply, returned");
        return;
    }

    _logger->debug("slot_httpFinished");

    Download *download = i.value();
    QNetworkReply *reply = i.key();

    //先 释放、关闭 reply!!!!
    freeReplyInfo(reply);

    QVariant possibleRedirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    download->setUrlRedirectedTo(possibleRedirectUrl.toUrl());
    if (!download->urlRedirectedTo().isEmpty()) {
        _logger->info(QString("redirected:[%1]==>>>%2").arg( download->getCurSegUrl().toString(),
                                                            download->urlRedirectedTo().toString()) );
        //更新当前段url
        download->setCurSegUrl(download->urlRedirectedTo());

        //重新开始
        this->doStart(download);
        return;
    }

    /*
     * We weren't redirected anymore
     * so we arrived to the final destination...
     */
    download->urlRedirectedTo().clear();
    _logger->info("have no redirect..");

    //若非用户中断的自然完成，则认为当前段已完成。
    if(!_bUserInterupt && download->errorCode()==QNetworkReply::NoError){
        _logger->info(QString("seg-%1 had completed!").arg(download->getCurSegIdx()));

        download->doNextSeg();
        //i.key()->deleteLater();
        //freeReplyInfo(reply);    //完全释放

        //继续开始新段下载
        doStart(download);
        return;
    }

    //暂停等
    _logger->info("maybe pause!!!");
    download->closeFile();
    download->setFile(0);
    //freeReplyInfo(i.key());


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
    _logger->info(QString("removeFile: [%1]").arg(download->fileName()));

    if(!download->removeFile()) {
        _logger->error(QString("Couldn't remove [%1]. Error: %2").arg(download->fileName(), download->errString()));
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

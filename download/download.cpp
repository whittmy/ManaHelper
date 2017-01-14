﻿/****************************************************************************************
** download.cpp is part of yoDownet
**
** Copyright 2013 Alireza Savand <alireza.savand@gmail.com>
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

#include "download.h"
#include <QFileInfo>
#include <QDir>
#include "util/paths.h"
#include "util/xml_parser_playurl.h"

//“下载任务” 类
Download::Download(QObject *parent):
    QObject(parent),_logger(new LogMe(this))
{
    slot_httpError(QNetworkReply::NoError, "");

    mHttp = new HttpRequestor();
    connect(mHttp, SIGNAL(sig_onFinished(REQ_TYPE, QString)), this, SLOT(slot_onHttpReqFinished(REQ_TYPE, QString)));

    _file = NULL;
    _status = NULL;
}

Download::~Download(){
    delete mHttp;
}

//新建任务，创建该任务的基本信息
//注意下载存放的目标位置都是为临时位置， 最终要转移到设备上
//下载中的文件名是加上".download"来标识，下载完成后，需自动更名。

// 有必要统计下，文件总大小(预估)，以及实际已下载的字节数，以便计算剩余时间。
// 新的任务，要确定Status中的两个数据，分别为：
//setFileAlreadyBytes();
//setBytesTotal();
bool Download::newDownload(int row, const int ID, const QUrl &url, const QUuid &uuid, const QString &fileName, qint64 size)
{
    _logger->info(QString("newDownload: %1").arg(url.toString()));
    _row = row;
    setUuid(uuid);
    setUrl(url); //该url为总url， 下载细节以分段url为准
    setID(ID);

    mCurSegIdx = 0;
    QString fileNewName = fileName;

    if (fileNewName.isEmpty() || fileNewName.isNull()) {
        _logger->info("fileName is not provided, getting file name from URL");
        QFileInfo fileInfo(url.path());
        fileNewName = fileInfo.fileName();
    }

    fileNewName = Paths::filter(fileNewName);

   // fileNewName += ".mp4";      //!!不考虑传入的文件名带扩展名??? 其它类型的资源呢？？？

    this->setName(fileNewName);
    this->setPath("C:\\"); //设置目的路径， 除了最终的转存外，其余使用的都是 缓存路径。
    //++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++

    //缓存文件
    _status = new Status(this);
    _file = NULL;
    bool isOpened = false;

    QString fileWithPath = QString(Paths::cacheDirPath()).append(fileNewName);
    _logger->info(QString("FileNewName: [%1]| FileWithPath: [%2]").arg(fileNewName, fileWithPath));

    if (QFile::exists(fileWithPath)) {
        //已完成 (因为正常是带 .download或分段编号的)
        _logger->info("file is complete, set WaitCombine, and mCurSegIdx is 1");

        this->setFile(new QFile(fileWithPath));
         //设置总大小&已下载数>>
        _status->setBytesTotal(getFileSize());
        _status->setFileAlreadyBytes(getFileSize());
        //<<<
        //下载状态是完成的，等待转码转存
        _status->setDownloadStatus(Status::WaitCombine);

        //已完成的任务， 设定其只有一个段(即便其下载时有多段)，
        //设置段号为1,(1>=cnt)说明已结束
        mCurSegIdx = 1;
    }
    else{
        _logger->info("file is downloading-status");
        //开始识别下载状态！！！
        bool newTask = false;
        QDir dir(Paths::cacheDirPath());
        //按名字逆序排列，获取最后一个片段的状态(片段是一个接一个按顺序下载，一个完成后才进行下一个片段)
        QFileInfoList flist = dir.entryInfoList( QStringList()<< fileNewName+"*",
                                                 QDir::Files, QDir::Name|QDir::Reversed);
        foreach(QFileInfo p, flist){
            _logger->info("filter-file:"+p.fileName());
        }
        _logger->info("begin to handle the cache file");
        qint64 fsize = 0;
        for(int i=0; i<flist.size(); i++){
            _logger->info(QString("file:%1").arg(i));
            QFileInfo fi=flist.at(i);

            //仅判断第一个(也即最后一个) 即可
            QString name = fi.fileName();
            int pos = name.indexOf(QRegExp("_mmh[0-9]{3}"));

            if(name.endsWith(".download")){
                if(i > 0){
                    fsize += fi.size();
                    continue;
                }
                fsize += fi.size();


                //当前段正在下载
                mCurSegIdx =  name.mid(pos+4, 3).toInt();

                this->setFile(new QFile(fi.absoluteFilePath()));
                isOpened = _file->open(QIODevice::Append);

                _status->setDownloadMode(Status::ResumeDownload);
                _logger->info(QString("find the .download file, name=%1，get-segIdx=%2, append-mode").arg(name).arg(mCurSegIdx));
             }
             else if(pos >= 0){
                if(i > 0){
                    fsize += fi.size();
                    continue;
                }
                fsize += fi.size();

                //当前段已下载完成，准备新的开始(不管有没有新的段)
                mCurSegIdx = name.mid(pos+4, 3).toInt()+1;

                this->setFile(new QFile(fileWithPath+QString::asprintf("_mmh%03d.download", mCurSegIdx))); //_mmhXXX.download
                isOpened = _file->open(QIODevice::WriteOnly);

                _status->setDownloadMode(Status::ResumeDownload);
                _logger->info(QString("find the .download file, name=%1，get-segIdx=%2, newfile-mode").arg(name).arg(mCurSegIdx));

             }
            else{
                //没有段下载
                newTask = true;
            }
            //break; 用上面的continue代替了
        }

        //如果还没有开始
        if(newTask || flist.size()==0){
            _logger->info("had no seg-downloaded, we new it: "+ fileWithPath+"_mmh000.download");

            mCurSegIdx = 0;
            this->setFile(new QFile(fileWithPath+"_mmh000.download"));
            isOpened = _file->open(QIODevice::WriteOnly);
            _status->setDownloadMode(Status::NewDownload);
            _status->setBytesTotal(0);
            _status->setFileAlreadyBytes(0);
        }
        else{
            _logger->info("have the cache, set it info");
            //????? _status->setBytesTotal(???);
            _status->setFileAlreadyBytes(fsize);
        }

        //打开失败，
        if (!isOpened) {
            _logger->error(QString("Couldn't open file for '%1', adding new download aborted").arg(fileNewName));
            delete _file;
            _file = 0;
            return false;
        }
        else{
            _logger->info("open file successfully");
        }
        this->setCreated(QDateTime::currentDateTime());

    }


    //预处理url
    preTreatment();

    return true;
}

//对url进行预处理，取url对应的各分段url，不管怎样，最终都将调用 slot_onHttpReqFinished
//只有一个段的，为多段的特殊形式,最终都经历 “合并”这一步骤。
// filename.mp4_mmh000.download  >>> [finish] >>>  filename.mp4_mmh_000
// filename.mp4_mmh001.download  >>> [finish] >>>  filename.mp4_mmh_001
// ....
//                                                                    || >>>> filename.mp4
void Download::preTreatment(){
    _logger->info("preTreatment");
    mSegUrls.clear();

    RequestInfo *info = new RequestInfo();
    if(_url.toString().contains("url=") || _status->downloadStatus()== Status::WaitCombine){
        //parser ==> slot
        info->url = _url.toString();
        _logger->info("begin to addTask of http for :"+info->url);
        mHttp->addTask(info); //请求完，会触发slot_onHttpReqFinished
    }
    else{
        //不牵涉到网络请求解析，直接调用 slot_onHttpReqFinished
        _logger->info("direct to slot_onHttpReqFinished fro url:"+_url.toString());
        mSegUrls.append(_url);
        slot_onHttpReqFinished(UNDEFINED, "");
    }
}

//解析分段url完成，开始发送通知：Download已添加完成
void Download::slot_onHttpReqFinished(REQ_TYPE type, QString rslt){
    _logger->info("slot_onHttpReqFinished enter --rslt:"+rslt);
    if(!rslt.isEmpty()){
        Xml_Parser_Playurl xmlparser(rslt);
        xmlparser.parser();
        if(xmlparser.isValid()){
            QStringList list = xmlparser.getFiles();
            foreach(QString url ,list){
                _logger->info("append seg-url:"+url);
                mSegUrls.append(QUrl(url));
            }
        }
        else{
            _logger->info("req-data is invalid");
        }

    }


    //编号已到结尾的，说明全部已处理完了。
     _logger->info(QString("cursegidx=%1,sum=%2").arg(mCurSegIdx).arg(getSegCnt()));
     if(getSegCnt() == 0)
     {
         _status->setDownloadStatus(Status::Failed);
         if(_file != NULL){
             closeFile(); //清除多余的
             _file->remove();
             setFile(0);
         }
         _logger->info("had  === Status::Failed");
     }
     else if(mCurSegIdx >= getSegCnt()){
        _status->setDownloadStatus(Status::WaitCombine);
        if(_file != NULL){
            closeFile(); //清除多余的
            _file->remove();
            setFile(0);
        }
        _logger->info("had  === Status::WaitCombine");
    }


    //通知，任务已添加成功
    emit sig_onTaskAdded(this);
}

const void Download::closeFile(){
    _logger->info("closeFile");
    if(_file != NULL){
        _file->flush();
        _file->close();
    }
    _logger->info("end closeFile");
}

void Download::setFile(QFile *file)
{
    _logger->info("setFile");
    if(_file != NULL){
        delete _file;
        _file = 0;
    }
    _file = file;
    _logger->info("end setFile");
}

//QFile *Download::file()
//{
//    return _file;
//}

void Download::setUrl(const QUrl &url)
{
    _url = url;
}

QUrl Download::url() const
{
    return _url;
}

void Download::setName(const QString &name)
{
    _name = name;
}

//任务的总文件名
QString Download::name() const
{
    return _name;
}

void Download::setPath(const QString &path)
{
    _path = path;
}

QString Download::path() const
{
    return _path;
}

QString Download::fileAbsolutePath() const
{
    return QString(path() + name());
}

void Download::setUuid(const QUuid &uuid)
{
    _logger->info("Initializing UUID");
    if (uuid.isNull()) {
        _logger->info("Given UUID is null, Generating new one");
        _uuid = QUuid::createUuid();
        return;
    }

    _uuid = uuid;
}

QUuid Download::uuid() const
{
    return _uuid;
}

void Download::setStatus(Status *status)
{
    _status = status;
}

Status *Download::status() const
{
    return _status;
}

void Download::setCreated(const QDateTime &created)
{
    _created = created;
}

QDateTime Download::created() const
{
    return _created;
}
QUrl Download::urlRedirectedTo() const
{
    return _urlRedirectedTo;
}

void Download::setUrlRedirectedTo(const QUrl &urlRedirectedTo)
{
    _urlRedirectedTo = urlRedirectedTo;
}

int Download::ID() const{
    return _ID;
}
void Download::setID(const int id){
    _ID = id;
}


QUrl Download::getCurSegUrl() const{
    if(mCurSegIdx < getSegCnt())
        return mSegUrls.at(mCurSegIdx);
    return QUrl();
}
void Download::setCurSegUrl(QUrl url){
    if(mCurSegIdx < getSegCnt())
        mSegUrls.replace(mCurSegIdx, url);
}

int Download::getCurSegIdx() const{
    return mCurSegIdx;
}

int Download::getSegCnt() const{
    return mSegUrls.size();
}

bool Download::bSegEnd() const{
    return mCurSegIdx >= getSegCnt();
}

void Download::doNextSeg(){
    //1. 对当前已完成的文件正名
    _logger->info("enter doNextSeg--->>>>");
    if(_file->fileName().endsWith(".download")){
        _logger->info("rename -- delete .download ");
        _file->rename(_file->fileName().left(_file->fileName().length()-QString(".download").length()));
        closeFile();
        setFile(0);
        _logger->info("rename ok, and setFile Null");
    }

    //2.递增段号
    mCurSegIdx++;
    if(mCurSegIdx >= getSegCnt()){
        _logger->info("end seg,so return");
        return;
    }

    //同步更新Status的相关数据
    _status->setSegInfo(mCurSegIdx, getSegCnt());
    _status->nextSeg();


    //3.设置File, 以便下载上
    QString fileWithPath =  QString::asprintf("%s_mmh%03d.download",
                                              QString(Paths::cacheDirPath()).append(_name).toStdString().c_str(),
                                              mCurSegIdx);
    _logger->info("begin set new File:"+fileWithPath);
    this->setFile(new QFile(fileWithPath)); //_mmhXXX.download
    if(!_file->open(QIODevice::WriteOnly)){
         _logger->error(QString("Couldn't open file for '%1', adding new download aborted").arg(fileWithPath));
        setFile(0);
    }
    _logger->info("had open the new file, and leave<<<<");
}


void Download::slot_httpError(const QNetworkReply::NetworkError err, const QString str){
    _error = err;
    _lastError = str;
}

QNetworkReply::NetworkError Download::errorCode() const{
    return _error;
}

QString Download::errorStr() const{
    return _lastError;
}

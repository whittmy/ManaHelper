﻿/****************************************************************************************
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
    _logger(new LogMe(this))
{
    mDloader = DLoader_common::Instance();

 }

DownLoader::~DownLoader(){
    mDloader->free();
    delete _logger;
}

//downloader 只认 Download对象
//传给downloader的url是唯一的，变化的。
//对外负责显示，经用户对外部数据的操作，则可以对内部的下载、解析保存一致性。

//下载的开始/恢复动作为共用， 避免解析产生的临时url段失效
void DownLoader::start(const int ID, const QString &url, const QUuid &uuid, const QString &fileName)
{
    _logger->debug("addDownload");
    _logger->info(QString("%1,%2,%3,%4").arg(ID).arg(url).arg(uuid.toString()).arg(fileName));

    //Download 资源释放？？？
    Download *newDownload = new Download(this);
    connect(newDownload, SIGNAL(sig_onTaskAdded(Download*)), this, SLOT(slot_onTaskAdded(Download*)));

    //当添加完成后，会自动触发slot_onTaskAdded函数
    newDownload->newDownload(ID,url,uuid,fileName);


   // mDloader->doStart(newDownload);
}

void DownLoader::slot_onTaskAdded(Download *download){
    _logger->info("slot_onTaskAdded");
    if(download->getCurSegUrl().isEmpty()){
        _logger->error("empty url");
        return;
    }

    mDloader->doStart(download);
}


// TODO: emit signal when download hash is empty OR no download has been found
void DownLoader::pause(const QUuid &uuid)
{
    _logger->info(QString("Pausing download [%1]").arg(uuid.toString()));
    mDloader->doPause(uuid);

}

void DownLoader::remove(const QUuid &uuid)
{
    _logger->info(QString("Start Removing [%1] via downloader engine").arg(uuid.toString()));
    mDloader->doRemove(uuid);

}


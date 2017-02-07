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

#include <QUrl>
#include <QHash>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <download/download.h>
#include "download/status.h"
#include "util/logme.h"
#include "dloader_common.h"


//每个任务的下载器
class DownLoader : public QObject
{
    Q_OBJECT
public:
    explicit DownLoader(QObject *parent = 0);
    ~DownLoader();
    void start(const int ID, const QString &url, const QUuid &uuid, const QString &fileName, qint64 size);
    void pause(const QUuid &uuid);
    void remove(const QUuid &uuid);



signals:
    void downloadInitialed(const Download *download);
    void downloadPaused(const Download *download);
    void downlaodResumed(const Download *download);
    void downloadUpdated(const Download *download);
    void downloadRemoved(const Download *download);
    void downloadFinished(const Download *download);
    void downloadFailed(const Download *download);

public slots:
    void slot_onTaskAdded(const Download *download);

private:

    DLoader_common *mDloader;
    LogMe* _logger;
};

#endif // YODOWNET_H

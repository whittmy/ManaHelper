/****************************************************************************************
** download.h is part of yoDownet
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

#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QFile>
#include <QUuid>
#include <QUrl>
#include <QVector>

#include "util/httprequestor.h"
#include "util/logme.h"
#include "download/status.h"

//任务信息
class Download : public QObject
{
    Q_OBJECT

public:
    explicit Download(QObject *parent = 0);
    ~Download();

    bool newDownload(const int row, const int ID, const QUrl &url, const QUuid &uuid=QUuid(), const QString &fileName=QString(), qint64 size=0);

    void setFile(QFile *file);
    //QFile *file();
    bool bfileValid() const{
        return _file!=0;
    }
    QString fileName() const{  //注意fileName与 name的区别，一个是文件本身名，一个是任务名
        if(_file != NULL)
            return _file->fileName();
        return QString();
    }

    void writeFile(QByteArray arr){
        _file->write(arr);
    }
    qint64 getFileSize() const{
        return _file->size();
    }
    bool removeFile() const{
        if(_file == NULL)
            return true;
        return _file->remove();
    }

    QString errString() const{
        if(_file == NULL)
            return QString();
        return _file->errorString();
    }

    void setUrl(const QUrl &url);
    QUrl url() const;

    void setName(const QString &name);
    QString name() const;

    void setPath(const QString &path);
    QString path() const;

    QString fileAbsolutePath() const;

    void setUuid(const QUuid &uuid=QUuid::createUuid());
    QUuid uuid() const;

    void setStatus(Status *status);
    Status *status() const;

    void setCreated(const QDateTime &created);
    QDateTime created() const;

    QUrl urlRedirectedTo() const;
    void setUrlRedirectedTo(const QUrl &urlRedirectedTo);

    int ID() const;
    void setID(const int id);


public:
    QUrl getCurSegUrl() const;
    void setCurSegUrl(QUrl url);
    int getCurSegIdx() const;
    int getSegCnt() const;
    void doNextSeg(); //含当前段的证明，段号的递增等工作
    bool bSegEnd() const;
    const void closeFile();

    QNetworkReply::NetworkError errorCode() const;
    QString errorStr() const;

    qint64 _row;


signals:
    void sig_onTaskAdded(const Download* download);
public slots:
    void slot_onHttpReqFinished(REQ_TYPE type, QString result);
    void slot_httpError(const QNetworkReply::NetworkError err, const QString str);

private:

    void preTreatment(); //对url进行预处理：1. 分类； 2. 最终分解为url列表
    QVector<QUrl> mSegUrls;  //对url的顺序有严格要求
    int mCurSegIdx;
    HttpRequestor *mHttp;

    int _ID;
    QFile *_file;
    QUrl _url;  //原始URL
    QString _name;
    QString _path;
    QUuid _uuid;
    Status *_status;
    QDateTime _created;

    QUrl _urlRedirectedTo;

    LogMe *_logger;
    QNetworkReply::NetworkError _error;
    QString _lastError;

};

#endif // DOWNLOAD_H

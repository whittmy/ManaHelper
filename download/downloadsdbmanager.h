#ifndef DOWNLOADSDBMANAGER_H
#define DOWNLOADSDBMANAGER_H
#include <QtSql>
#include "util/logme.h"

class DownloadsDBManager :public QObject
{
    Q_OBJECT
public:
    ~DownloadsDBManager();
    static DownloadsDBManager* Instance();
    QSqlDatabase db;
    void createDB();

    bool openDB();
    void closeDB();
    bool isDbValid();

/* 注释掉，和modelDownloads类互为包含，编译有问题
    void setHeaders(modelDownloads *model);
    modelDownloads *queryDownloads(int status,int type,int queue);
*/

    void initStartUpStatus(); //初始化启动状态，即启动时将所有非常规状态(如Idle、Downloading)置为暂停


    int insertDownload(QString filename,QString url,QString loc,QString desc,qint64 cat,QString ref,qint64 queue,qint64 pieces);
    void deleteDownload(qint64 id);
    QSet<QString> getFileNameListDownloading();

    //CRUD OPERATIONS
    QString getFileName(qint64 id);
    void setFileName(qint64 id, QString Filename);

    QString getURL(qint64 id);
    void setURL(qint64 id, QString URL);

    qint64 getDateAdded(qint64 id);
    void setDateAdded(qint64 id, qint64 dateAdded);
    void setDateAdded(qint64 id, QString dateAdded);

    qint64 getQueue(qint64 id);
    void setQueue(qint64 id,qint64 queue);

    qint64 getSize(qint64 id);
    void setSize(qint64 id,qint64 size);

    qint64 getFinishedStatus(qint64 id);
    void setFinishedStatus(qint64 id,qint64 finishedStatus);

    qint64 getStatus(qint64 id);
    void setStatus(qint64 id,qint64 status);

    qint64 getTimeleft(qint64 id);
    void setTimeLeft(qint64 id,qint64 timeleft);

    qint64 getTransferRate(qint64 id);
    void setTransferRate(qint64 id,int transferRate);

    qint64 getLastTry(qint64 id);
    void setLastTry(qint64 id,qint64 lastry);

    QString getDescription(qint64 id);
    void setDescription(qint64 id,QString desc);

    QString getSaveLocation(qint64 id);
    void setSaveLocation(qint64 id,QString saveLocation);

    QString getReferer(qint64 id);
    void setReferer(qint64 id,QString referer);

    qint64 getType(qint64 id);
    void setType(qint64 id,qint64 type);

    qint64 getTimeElapsed(qint64 id);
    void setTimeElapsed(qint64 id,qint64 timeElapsed);

    qint64 getPieces(qint64 id);
    void setPieces(qint64 id,qint64 pieces);

    QString getUuid(qint64 id);
    void setUuid(qint64 id, QString uuid);

    qint64 getProgress(qint64 id);
    void setProgress(qint64 id,qint64 progress);

//    int getID(qint64 id);
//    void setID(qint64 id, qint64 id);
    //CRUD OPERATIONS END

private:
    DownloadsDBManager();
private:
    static DownloadsDBManager  *_instance;
    LogMe *_logger;
    bool _bDbValid;

};

#endif // DOWNLOADSDBMANAGER_H

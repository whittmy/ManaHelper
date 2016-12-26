#ifndef DOWNLOADSDBMANAGER_H
#define DOWNLOADSDBMANAGER_H
#include <QtSql>
#include <download/modeldownloads.h>
#include "util/logme.h"

class DownloadsDBManager :public QObject
{
    Q_OBJECT
public:
    DownloadsDBManager();
    ~DownloadsDBManager();
    QSqlDatabase db;
    void createDB();

    bool openDB();
    void closeDB();
    bool isDbValid();

    /*
    void setHeaders(modelDownloads *model);

    int insertDownload(QString filename,QString url,QString loc,QString desc,int cat,QString ref,int queue,int pieces);
    void deleteDownload(int id);

    modelDownloads *queryDownloads(int status,int type,int queue);

    //CRUD OPERATIONS
    QString getFileName(int id);
    void setFileName(int id, QString Filename);

    QString getURL(int id);
    void setURL(int id, QString URL);

    int getDateAdded(int id);
    void setDateAdded(int id, int dateAdded);
    void setDateAdded(int id, QString dateAdded);

    int getQueue(int id);
    void setQueue(int id,int queue);

    int getSize(int id);
    void setSize(int id,int size);

    int getFinishedStatus(int id);
    void setFinishedStatus(int id,int finishedStatus);

    QString getStatus(int id);
    void setStatus(int id,QString status);

    int getTimeleft(int id);
    void setTimeLeft(int id,int timeleft);

    int getTransferRate(int id);
    void setTransferRate(int id,int transferRate);

    int getLastTry(int id);
    void setLastTry(int id,int lastry);

    QString getDescription(int id);
    void setDescription(int id,QString desc);

    QString getSaveLocation(int id);
    void setSaveLocation(int id,QString saveLocation);

    QString getReferer(int id);
    void setReferer(int id,QString referer);

    int getType(int id);
    void setType(int id,int type);

    int getTimeElapsed(int id);
    void setTimeElapsed(int id,int timeElapsed);

    int getPieces(int id);
    void setPieces(int id,int pieces);
    //CRUD OPERATIONS END
    */
private:

    LogMe *_logger;
    bool _bDbValid;

};

#endif // DOWNLOADSDBMANAGER_H

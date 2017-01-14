#ifndef MODELDOWNLOADS_H
#define MODELDOWNLOADS_H
#include <QSqlTableModel>
#include<QSqlDatabase>
#include"util/logme.h"
#include"download/status.h"
#include "downloadsdbmanager.h"

class modelDownloads : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit modelDownloads(QObject *parent = 0, DownloadsDBManager *dm=0);
    void setFilterCustom(QString key, int value);
    void setFilterCustom(QString key, QString value);
    void setFilterDownloads(int status);

    void setHeaders();
    int insertDownload(QString filename,QString url,QString loc,QString desc,int type,QString ref,int queue,int pieces,QString uuid);
    void deleteDownload(int row);


    void setFilterFinishedStatus(int value);
    void setFilterType(int value);
    void setFilterQueue(int value);
    void refrushModel();

    //modelDownloads(QObject *parent = 0,QSqlDatabase *db);
    //int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    //int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QString getFileName(int row);
    void setFileName(int row, QString Filename, bool submit=true);
    QString getURL(int row);
    void setURL(int row, QString URL, bool submit=true);
    qint64 getDateAdded(int row);
    void setDateAdded(int row, qint64 dateAdded, bool submit=true);
    qint64 getQueue(int row);
    void setQueue(int row,qint64 queue, bool submit=true);
    qint64 getSize(int row);
    void setSize(int row,qint64 size, bool submit=true);
    qint64 getFinishedStatus(int row);
    void setFinishedStatus(int row,qint64 finishedStatus, bool submit=true);
    qint64 getStatusOrg(int row);
    QString getStatus(int row);
    void setStatus(int row, qint64 status, bool submit=true);
    QString getTimeleft(int row);
    void setTimeLeft(int row,QString timeleft, bool submit=true);
    qint64 getTransferRate(int row);
    void setTransferRate(int row,qint64 transferRate, bool submit=true);
    qint64 getLastTry(int row);
    void setLastTry(int row,qint64 lastry, bool submit=true);
    QString getDescription(int row);
    void setDescription(int row,QString desc, bool submit=true);
    QString getSaveLocation(int row);
    void setSaveLocation(int row,QString saveLocation, bool submit=true);
    QString getReferer(int row);
    void setReferer(int row,QString referer, bool submit=true);
    qint64 getType(int row);
    void setType(int row,qint64 type, bool submit=true);
    qint64 getTimeElapsed(int row);
    void setTimeElapsed(int row,qint64 timeElapsed, bool submit=true);
    qint64 getPieces(int row);
    void setPieces(int row,qint64 pieces, bool submit=true);

    QString getUuid(int row);
    void setUuid(int row, QString &uuid, bool submit=true);

    qint64 getID(int row);
    void setID(int row, qint64 ID, bool submit=true);

    qint64 getProgress(int row);
    void setProgress(int row, qint64 progress, bool submit=true);
signals:

public slots:

private:
    LogMe *_logger;
    DownloadsDBManager *_dm;

};

#endif // MODELDOWNLOADS_H

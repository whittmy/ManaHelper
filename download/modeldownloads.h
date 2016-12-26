#ifndef MODELDOWNLOADS_H
#define MODELDOWNLOADS_H
#include <QSqlTableModel>
#include<QSqlDatabase>
#include"util/logme.h"
#include"download/status.h"

class modelDownloads : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit modelDownloads(QObject *parent = 0,QSqlDatabase db=QSqlDatabase());
    void setFilterCustom(QString key, int value);
    void setFilterCustom(QString key, QString value);
    void setFilterDownloads(int status,int type, int queue );

    void setHeaders();
    int insertDownload(QString filename,QString url,QString loc,QString desc,int type,QString ref,int queue,int pieces,QString uuid);
    void deleteDownload(int row);


    void setFilterFinishedStatus(int value);
    void setFilterType(int value);
    void setFilterQueue(int value);

    //modelDownloads(QObject *parent = 0,QSqlDatabase *db);
    //int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    //int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QString getFileName(int row);
    void setFileName(int row, QString Filename, bool submit=true);
    QString getURL(int row);
    void setURL(int row, QString URL, bool submit=true);
    int getDateAdded(int row);
    void setDateAdded(int row, int dateAdded, bool submit=true);
    int getQueue(int row);
    void setQueue(int row,int queue, bool submit=true);
    int getSize(int row);
    void setSize(int row,int size, bool submit=true);
    int getFinishedStatus(int row);
    void setFinishedStatus(int row,int finishedStatus, bool submit=true);
    int getStatus(int row);
    void setStatus(int row, int status, bool submit=true);
    QString getTimeleft(int row);
    void setTimeLeft(int row,QString timeleft, bool submit=true);
    int getTransferRate(int row);
    void setTransferRate(int row,int transferRate, bool submit=true);
    int getLastTry(int row);
    void setLastTry(int row,int lastry, bool submit=true);
    QString getDescription(int row);
    void setDescription(int row,QString desc, bool submit=true);
    QString getSaveLocation(int row);
    void setSaveLocation(int row,QString saveLocation, bool submit=true);
    QString getReferer(int row);
    void setReferer(int row,QString referer, bool submit=true);
    int getType(int row);
    void setType(int row,int type, bool submit=true);
    int getTimeElapsed(int row);
    void setTimeElapsed(int row,int timeElapsed, bool submit=true);
    int getPieces(int row);
    void setPieces(int row,int pieces, bool submit=true);

    QString getUuid(int row);
    void setUuid(int row, QString &uuid, bool submit=true);

    int getID(int row);
    void setID(int row, int ID, bool submit=true);

    int getProgress(int row);
    void setProgress(int row, int progress, bool submit=true);
signals:

public slots:

private:
    LogMe *_logger;

};

#endif // MODELDOWNLOADS_H

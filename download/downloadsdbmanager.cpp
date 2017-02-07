#include "download/downloadsdbmanager.h"
#include "download/modeldownloads.h"
#include <QtSql>
#include <QtSql/QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <download/modeldownloads.h>
#include "downloadconstants.h"
#include "status.h"
#include "util/paths.h"


DownloadsDBManager  *DownloadsDBManager:: _instance = NULL;
DownloadsDBManager* DownloadsDBManager::Instance(){
    if(_instance == NULL)
        _instance = new DownloadsDBManager();
    return _instance;
}

DownloadsDBManager::DownloadsDBManager():_logger(new LogMe(this))
{
    //添加数据库并打开
    db =  QSqlDatabase::addDatabase("QSQLITE");
    _bDbValid = false;
    if(openDB()){
        //判断数据库中的数据表是否存在
        QSqlQuery query(db);
        if(query.exec(QString("select count(*) cnt from sqlite_master where type='table' and name='downloadsTable'"))){
            query.first(); //!!!!!!
            _logger->debug(QString("get table count = %1").arg(query.value(0).toLongLong()));
            _bDbValid = query.value(0).toBool();
            query.clear();
        }
    }
}

DownloadsDBManager::~DownloadsDBManager()
{
    if(db.isOpen())
        db.close();
    db.removeDatabase("QSQLITE");
}

bool DownloadsDBManager::isDbValid(){
    _logger->debug(_bDbValid?"isDbValid":"db not valid");
    return _bDbValid;
}

//如果数据库未打开，则创建并打开
bool DownloadsDBManager::openDB()
{
    //_logger->debug("openDB");

    if(!db.isOpen()){
    // Find QSLite driver
    //if(db.driverName().compare("QSQLITE")!=0)
    //db = QSqlDatabase::addDatabase("QSQLITE");
#ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("downloadsDB");
    path = QDir::toNativeSeparators(path); //转化为适合操作系统的的路径分隔符
    db.setDatabaseName(path);
#else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName(Paths::dbPath());
#endif

    // Open databasee
    return db.open();
    }
    else return true;
}

//创建数据表
void DownloadsDBManager::createDB(){
    _logger->debug("createDB");

    if (this->openDB()) {
        QSqlQuery query(db); //获取db的查询接口
        QString createDBquery = "CREATE TABLE IF NOT EXISTS downloadsTable("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "filename VARCHAR(255) NOT NULL,"
                "url VARCHAR(1024) NOT NULL,"
                "size BIGINT,"
                "progress BIGINT,"
                "transferRate BIGINT,"
                "elapsedTime BIGINT,"
                "timeleft varchar(30),"
                "saveTo varchar(1024),"
                "queue BIGINT,"
                "status BIGINT,"
                "dateAdded BIGINT,"
                "finished BIGINT,"
                "lastTry BIGINT,"
                "description text,"
                "referer varchar(1024),"
                "type BIGINT,"
                "pieces BIGINT,"
                "uuid varchar(100)"
                ")";
        qDebug()<< "sql:" << createDBquery;
        if (query.exec(createDBquery)){ //查询
            _logger->debug("DB created Successfully");
        } else {
            _logger->error("Cannot Create database" + query.lastError().text());
            QMessageBox::critical(0, qApp->tr("Cannot Create database"),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        _logger->error("cannot open database");
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "This program needs SQLite support. Please read "
                                       "the Qt SQL driver documentation for information how "
                                       "to build it.\n\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

//关闭
void DownloadsDBManager::closeDB( ){
    _logger->debug("closeDB");
    db.close();
}


/*
modelDownloads *DownloadsDBManager::queryDownloads(int status,int type,int queue){
    //QSqlDatabase db =  QSqlDatabase::addDatabase("QSQLITE");

    if (!this->openDB()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "This program needs SQLite support. Please read "
                                       "the Qt SQL driver documentation for information how "
                                       "to build it.\n\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }

    modelDownloads *model = new modelDownloads(0, db);
     //>>>>>>>>>>>>>>>>>  下面这些工作在model里都有做， 构造函数和setFilterDownloads都做完了    >>>>>>>>>>>>>>>

    model->setTable("downloadsTable");
    model->setEditStrategy(modelDownloads::OnManualSubmit);
    QString filters1="",filters2="",filters3="";
    if(status!=-1)
        filters1.append("finished="+QString::number(status));
    if(type!=-1)
        filters2.append("type="+QString::number(type));
    if(queue!=-1)
        filters3.append("queue="+QString::number(queue));
    QString filters="";
    if(filters1!=""){
        filters.append(filters1);
    }
    if(filters2!=""){
        if(filters!=""){
            filters.append(" AND ").append(filters2);
        }else{
            filters.append(filters2);
        }
    }
    if(filters3!=""){
        if(filters!=""){
            filters.append(" AND ").append(filters3);
        }else{
            filters.append(filters3);
        }
    }
    model->setFilter(filters);
    model->select();

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //model->data(model->index(1,1)).toString().append("bhaskar");
    //model->data(model->index(0,3)).toDateTime().toString();
    QDateTime d;
    for(int col=0;col<model->columnCount();col++){ //时间信息整型改为QDateTime
        model->setData(model->index(col,3),d.fromMSecsSinceEpoch(model->data(model->index(col,3)).toLongLong()).toString());
        model->setData(model->index(col,10),d.fromMSecsSinceEpoch(model->data(model->index(col,10)).toLongLong()).toString());
    }
    //更新model中表的列名
    setHeaders(model);
    return model;
}
*/

//为毛不让model自己去操作？？
//执行后会有 关闭数据库
int DownloadsDBManager::insertDownload(QString filename,QString url,QString loc,QString desc,
                                       qint64 cat=0,QString ref="",qint64 queue=0,qint64 pieces=10){
    qint64 dateAdded = QDateTime::currentMSecsSinceEpoch();
    qint64 size = 0; // make zero size by default
    qint64 finished=0; // set status to unfinished
    QString status = "";
    qint64 timeleft=0;// trivial data set to zero
    qint64 transferRate=0;//trivial data set to zero
    qint64 lastTry= QDateTime::currentMSecsSinceEpoch(); // TODO :: it should be string
    qint64 elapsedTime =0;
    //All data collected ....Now insert the download

    //QSqlDatabase db =  QSqlDatabase::addDatabase("QSQLITE");
    if (openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT max(id) from downloadsTable;");
        query.exec();
        query.first();
        QString id = query.value(0).toString();
        QString insertDownloadquery = "INSERT INTO downloadsTable VALUES("
                +QString::number(id.toLongLong() +1) +","
                "'"+filename+"',"
                "'"+url+"',"
                +QString::number(dateAdded)+","
                +QString::number(queue)+","
                +QString::number(size)+","
                +QString::number(finished)+","
                "'"+status+"',"
                +QString::number(timeleft)+","
                +QString::number(transferRate)+","
                +QString::number(lastTry)+","
                "'"+desc+"',"
                "'"+loc+"',"
                "'"+ref+"',"
                +QString::number(cat)+","
                +QString::number(elapsedTime)+","
                +QString::number(pieces)+
                  ");";
        if (query.exec(insertDownloadquery)){
            //qDebug() << "Download Added Successfully";
            this->closeDB();
            return(query.lastInsertId().toLongLong());
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot Insert Download...Something went wrong.."),
                                  query.lastError().text()+"\n id == "+id, QMessageBox::Cancel);

        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    this->closeDB();
    return -1;
}

//删除编号为id的记录
//这里是直接通过query进行查询
void DownloadsDBManager::deleteDownload(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("DELETE FROM downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
            QMessageBox::information(0, qApp->tr("Download Deleted."),
                                  "Successfully removed the download from the list", QMessageBox::Cancel);
            //TODO
            //REMOVE FROM FILESYSTEM
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot delete the queue of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}



QSet<QString> DownloadsDBManager::getFileNameListDownloading(){
    QSet<QString> files;
    if(this->openDB()){
        QSqlQuery query(db);
        query.prepare("SELECT filename from downloadsTable WHERE status !=" +QString::number(Status::Finished)+ ";");
        if(query.exec()){
            while(query.next()){
                QString name = query.value(0).toString();
                files.insert(Paths::filter(name)); //处理
            }
        }
    }
    else{
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    return files;
}

//下面根据获取数据是根据列id进行检索的，不是row
//START CRUD OPERATIONS////
QString DownloadsDBManager::getFileName(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT filename from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            QString filename = query.value(0).toString();
            return filename;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get Filename."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    //this->closeDB();
    return "unknown";
}

void DownloadsDBManager::setFileName(qint64 id, QString Filename){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET filename = '"+Filename+"' WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the filename of the file."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

QString DownloadsDBManager::getURL(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT url from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            QString url = query.value(0).toString();
            return url;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get url."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return "unknown";
}

void DownloadsDBManager::setURL(qint64 id, QString URL){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET url = '"+URL+"' WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the url of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getDateAdded(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT dateAdded from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 dateAdded = query.value(0).toLongLong();
            return dateAdded;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the date when the download was added."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return 0;
}

void DownloadsDBManager::setDateAdded(qint64 id, qint64 dateAdded){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET dateAdded = "+QString::number(dateAdded)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the date when the download was added."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getQueue(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT queue from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 queue = query.value(0).toLongLong();
            return queue;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the queue number."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return -1;
}

void DownloadsDBManager::setQueue(qint64 id,qint64 queue){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET queue = "+QString::number(queue)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the queue of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getSize(qint64 id){
    if (this->openDB()) {
        _logger->info(QString("dm-getsize, id=%1").arg(id));
        QSqlQuery query(db);
        query.prepare("SELECT size from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            if(query.next()){
                return query.value(0).toLongLong();
            }

        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the size of the file."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return 0;
}

void DownloadsDBManager::setSize(qint64 id,qint64 size){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET size = "+QString::number(size)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the size of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getFinishedStatus(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT finished from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 fin = query.value(0).toLongLong();
            return fin;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the finished status."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return -1;
}

void DownloadsDBManager::setFinishedStatus(qint64 id,qint64 finishedStatus){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET finished = "+QString::number(finishedStatus)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the finished status of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getStatus(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT status from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 status = query.value(0).toLongLong();
            return status;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get status."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return -1;
}

void DownloadsDBManager::setStatus(qint64 id, qint64 status){
    qDebug() << "setStatus:" << id << ", " << status;
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET status = "+QString::number(status)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the status of the download."),
                                  query.lastError().text()+query.lastQuery(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getTimeleft(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT timeleft from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 timeleft = query.value(0).toLongLong();
            return timeleft;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the time left."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return -1;
}

void DownloadsDBManager::setTimeLeft(qint64 id,qint64 timeleft){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET timeleft = "+QString::number(timeleft)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the time left for the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getTransferRate(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT transferRate from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 rate = query.value(0).toLongLong();
            return rate;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get transfer rate."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return 0;
}

void DownloadsDBManager::setTransferRate(qint64 id,int transferRate){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET transferRate = "+QString::number(transferRate)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the transfer rate of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}


qint64 DownloadsDBManager::getProgress(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT progress from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 progress = query.value(0).toLongLong();
            return progress;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the progress."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return 0;
}

void DownloadsDBManager::setProgress(qint64 id,qint64 progress){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET progress = "+QString::number(progress)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the progress of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}


qint64 DownloadsDBManager::getLastTry(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT lastTry from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 last = query.value(0).toLongLong();
            return last;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the last try date."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return 0;
}

void DownloadsDBManager::setLastTry(qint64 id,qint64 lastry){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET lastTry = "+QString::number(lastry)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the date of last try of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

QString DownloadsDBManager::getDescription(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT description from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            QString desc = query.value(0).toString();
            return desc;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get description."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return "unknown";
}

void DownloadsDBManager::setDescription(qint64 id,QString desc){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET description = "+desc+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the description of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

QString DownloadsDBManager::getSaveLocation(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT saveTo from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            QString saveto = query.value(0).toString();
            return saveto;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get saved location."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return "";
}

void DownloadsDBManager::setSaveLocation(qint64 id,QString saveLocation){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET saveTo = '"+saveLocation+"' WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the save location of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

QString DownloadsDBManager::getReferer(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT referer from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            QString ref = query.value(0).toString();
            return ref;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get referer."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return "unknown";
}

void DownloadsDBManager::setReferer(qint64 id,QString referer){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET referer = "+referer+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the referer of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getType(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT type from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 type = query.value(0).toLongLong();
            return type;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the type of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return 0;
}

void DownloadsDBManager::setType(qint64 id,qint64 type){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET type = "+QString::number(type)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the type of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getTimeElapsed(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT elapsedTime from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 elapsed = query.value(0).toLongLong();
            return elapsed;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the time elapsed."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return 0;
}

void DownloadsDBManager::setTimeElapsed(qint64 id,qint64 timeElapsed){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET elapsedTime = "+QString::number(timeElapsed)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the elapsed time of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

qint64 DownloadsDBManager::getPieces(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT pieces from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            qint64 p = query.value(0).toLongLong();
            return p;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the size of the file."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return 0;
}


void DownloadsDBManager::setPieces(qint64 id,qint64 pieces){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET pieces = "+QString::number(pieces)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the number of pieces of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
}

QString DownloadsDBManager::getUuid(qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT uuid from downloadsTable WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            query.first();
            QString ref = query.value(0).toString();
            return ref;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get referer."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return "unknown";
}

void DownloadsDBManager::setUuid(qint64 id, QString uuid){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET Uuid = "+uuid+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the referer of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



void DownloadsDBManager::initStartUpStatus(){
    if (this->openDB()) {
        QSqlQuery query(db);
        QString sql ="UPDATE downloadsTable SET status = "+QString::number(Status::Paused)+"  WHERE status =" + QString::number(Status::Downloading)
                        +" or status="+ QString::number(Status::Idle) + ";";
        //qDebug() << sql;
        query.prepare(sql);
        if (query.exec()){
            //success
            sql = "UPDATE downloadsTable SET transferRate=-1";
            query.prepare(sql);
            if(query.exec()){
                sql = "delete from downloadsTable where status="+QString::number(Status::Finished);
                query.prepare(sql);
                query.exec();
            }
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot initStartUpStatus."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}




qint64 DownloadsDBManager::getID(QString uuid){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("SELECT ID from downloadsTable WHERE uuid ='" +uuid+ "';");
        if (query.exec()){
            query.first();
            qint64 p = query.value(0).toLongLong();
            return p;
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot get the ID of the file."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ///this->closeDB();
    return 0;
}

/*
void DownloadsDBManager::setID(qint64 id, qint64 id){
    if (this->openDB()) {
        QSqlQuery query(db);
        query.prepare("UPDATE downloadsTable SET ID = "+QString::number(ID)+" WHERE id =" +QString::number(id)+ ";");
        if (query.exec()){
            //success
        } else {
            QMessageBox::critical(0, qApp->tr("Cannot set the number of pieces of the download."),
                                  query.lastError().text(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
*/

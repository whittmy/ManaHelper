#include "download/modeldownloads.h"
#include<QtCore>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlError>
#include "download/downloadconstants.h"
#include "downloadsdbmanager.h"

modelDownloads::modelDownloads(QObject *parent, DownloadsDBManager *dm)
:QSqlTableModel(parent, dm->db),
_logger(new LogMe(this))
{
    _dm = dm;

    //设置表名
    setTable("downloadsTable");

    //设置按ID逆序排列，即最后添加的位于最顶部，解决添加新任务后，老是针对第一条记录进行下载的问题(插入记录时以行号0为依据进行读写数据)。
    setSort(DownloadConstants::Attributes::ID, Qt::DescendingOrder);

    //设置编辑值的策略
    //0:所有变化立即更新数据库
    //1:行的数据变化，只有选择不同行时才更新数据库
    //2:数据变化缓存在模型， 直到submitAll()或revertAll()
    setEditStrategy(modelDownloads::OnManualSubmit);

    //select * from table，还原为最真实的状态
    //获取所有数据
    select();

    //设置各列的标题名
    setHeaders();
}

void modelDownloads::refrushModel()
{
    beginResetModel();
    endResetModel();

}

//int modelDownloads::rowCount(const QModelIndex &parent) const
//{
//    return QSqlTableModel::rowCount(parent);
//}

//int modelDownloads::columnCount(const QModelIndex &parent ) const{
//    return QSqlTableModel::columnCount(parent);
//}



//data为重载函数，获取的数据即为view端显示的数据，显示可以与实际不同，在这儿处理下
//data写的如果有问题，
QVariant modelDownloads::data(const QModelIndex &index, int role) const  {
    //qDebug() << "role:"<<role;
    //return QSqlTableModel::data(index, role);

    ////itemData以及会触发该data函数，
    //QVariant value  = itemData(index).value(col-DownloadConstants::Attributes::ID);
    //QVariant value = index.data();

    if (!index.isValid() || rowCount()==0)
        return QVariant();

    //调用父函数
    QVariant value = QSqlTableModel::data(index, role);
    if(!value.isValid() || value.isNull())
        return QVariant();

    int row = index.row();
    int col = index.column();

    /*
    if(role == Qt::TextAlignmentRole){
//        if (col == DownloadConstants::Attributes::AddedDate ||
//               col == DownloadConstants::Attributes::Size ||
//               col == DownloadConstants::Attributes::Progress ||
//                col == DownloadConstants::Attributes::Speed ||
//                col == DownloadConstants::Attributes::Status)
//        {

//            // + Qt::AlignVCenter;
//        }
        qDebug() << "TextAlignmentRole";
       return Qt::AlignCenter;
    }


    else if(role == Qt::TextAlignmentRole){
        //_logger->debug("data-TextAlignmentRole");
        if (row == 1 && col == 1) //change text alignment only for cell(1,1)
        {
            return Qt::AlignRight + Qt::AlignVCenter;
        }
    }
    else if(role == Qt::CheckStateRole){
        //_logger->debug("data-CheckStateRole");
        if (row == 1 && col == 0) //add a checkbox to cell(1,0)
        {
            return Qt::Checked;
        }
    }
    else

    */
    //_logger->debug("role="+QString::number(role));
    if(role == Qt::FontRole){
        //_logger->debug("data-FontRole");
        if (row == 0 && col == 0) //change font only for cell(0,0)
        {
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
    }
    else if(role == Qt::BackgroundRole){
        //_logger->debug("data-BackgroundRole");
        if (col == 2)  //change background only for cell(1,2)
        {
            QBrush redBackground(Qt::red);
            return redBackground;
        }
    }
    else if(role == Qt::DisplayRole){
        //_logger->debug(QString("data-DisplayRole,row=%1,col=%2").arg(row).arg(col));

        QString unit;
        int size = 0;
        int speedInt = 0;

        int status;

        if(col == DownloadConstants::Attributes::Size){
            //_logger->debug("data-size");
            size = value.toLongLong();
            unit = "";
            if(size < 1024){
                unit = tr("bytes");
            }else if(size < 1024*1024){
                size /= 1024;
                unit = tr("KB");
            }else{
                size /= 1024*1024;
                unit = tr("MB");
            }
            return QString("%1 %2").arg(size).arg(unit);
        }
        else if(col == DownloadConstants::Attributes::Progress){
            //_logger->debug("data-Progress");
            return QString("%1%2").arg(value.toString()).arg("%");
        }
        else if(col == DownloadConstants::Attributes::Speed){
            //_logger->debug("data-speed");
            speedInt = value.toLongLong();
            if(speedInt < 0)
                return "";

            unit = "";
            if(speedInt < 1024){
                unit = tr("bytes/sec");
            }else if(speedInt < 1024*1024){
                speedInt /= 1024;
                unit = tr("KB/sec");
            }else{
                speedInt /= 1024*1024;
                unit = tr("MB/sec");
            }
            return QString("%1 %2").arg(speedInt).arg(unit);
        }
        else if(col == DownloadConstants::Attributes::RemainingTime){
            return value.toString();
        }
        else if(col == DownloadConstants::Attributes::ElapseTime){
            return QVariant();
        }
        else if(col == DownloadConstants::Attributes::AddedDate
                || col == DownloadConstants::Attributes::LastTryDate){
            //!!! 注意时间戳的数字超int界限，所以取数据要 toLongLong，当然存时也要一致避免出错.调了很久
            //另外也可以设置字段为时间。

            qint64 sec = 1000 * value.toLongLong();
           // _logger->debug(QString("data-times %1").arg(sec));
            //sec = QDateTime::currentMSecsSinceEpoch();
            //_logger->debug(QString("cur-sec 1%").arg(sec));

            QDateTime date = QDateTime::fromMSecsSinceEpoch(sec);  //将时间戳转时间
            return date.toLocalTime().toString("yyyy-MM-dd hh:mm:ss");

        }
        else if(col == DownloadConstants::Attributes::Status){
            //_logger->debug("data-status");
            status = value.toLongLong();
            return Status::transDownLoadString(status);
        }
    }

    return value;
}


///////////////////////////////////
/// \brief modelDownloads::setFilterCustom
/// \param key
/// \param value
/// 设置过滤条件， "keystr=value", setFilter()
/// 并查询，获取数据
void modelDownloads::setFilterCustom(QString key, QString value){
    _logger->debug("setFilterCustom-String");
    QString filter = key + "=" + value;
    setFilter(filter);
    select();
}

void modelDownloads::setFilterCustom(QString key, int value){
    _logger->debug("setFilterCustom-int");
    QString filter = key + " = " + QString::number(value);
    setFilter(filter);
    select();
}

//筛选完成/未完成的记录
void modelDownloads::setFilterFinishedStatus(int value){
    _logger->debug("setFinishedStatus");
    setFilterCustom("finished",value);
}
//筛选指定类型的记录
void modelDownloads::setFilterType(int value){
    _logger->debug("setType");
    setFilterCustom("type",value);
}
//筛选queue的值
void modelDownloads::setFilterQueue(int value){
    _logger->debug("setQueue");
    setFilterCustom("queue",value);
}
//筛选下载的记录，根据 完成状态-类别-queue， “-1”代表忽略
void modelDownloads::setFilterDownloads(int status=-1){
    //_logger->debug(QString("setFilterDownloads:%1").arg(status));
    QString filters1="",filters2="";
    if(status == -1)
        filters1.append("status < "+QString::number(Status::DownloadStatus::Finished));
    else
        filters1.append("status = "+QString::number(Status::DownloadStatus::Finished));

    QString filters="";
    if(filters1!=""){
        filters.append(filters1);
        //qDebug() << filters1;
    }

    //三个filter字符串 and 操作
    setFilter(filters);
    select();
}


//设置各列的标题
void modelDownloads::setHeaders(){
    //setHeaderData,设置列标题， 当model用于view显示时，便可看到效果
    _logger->debug("setHeaders");
    setHeaderData(DownloadConstants::Attributes::ID, Qt::Horizontal, QObject::tr("ID")); //auto increment
    setHeaderData(DownloadConstants::Attributes::FileName, Qt::Horizontal, QObject::tr("File Name"));
    setHeaderData(DownloadConstants::Attributes::URL, Qt::Horizontal, QObject::tr("URL"));
    setHeaderData(DownloadConstants::Attributes::Size, Qt::Horizontal, QObject::tr("Size"));
    setHeaderData(DownloadConstants::Attributes::Progress, Qt::Horizontal, QObject::tr("Progress"));
    setHeaderData(DownloadConstants::Attributes::Speed, Qt::Horizontal, QObject::tr("Transfer Rate"));
    setHeaderData(DownloadConstants::Attributes::ElapseTime, Qt::Horizontal, QObject::tr("Elapsed Time"));
    setHeaderData(DownloadConstants::Attributes::RemainingTime, Qt::Horizontal, QObject::tr("Time Left"));
    setHeaderData(DownloadConstants::Attributes::SavePath, Qt::Horizontal, QObject::tr("Save to"));
    setHeaderData(DownloadConstants::Attributes::Queue, Qt::Horizontal, QObject::tr("Queue"));
    setHeaderData(DownloadConstants::Attributes::Status, Qt::Horizontal, QObject::tr("Status"));
    setHeaderData(DownloadConstants::Attributes::AddedDate, Qt::Horizontal, QObject::tr("Date Added"));
    setHeaderData(DownloadConstants::Attributes::Downloaded, Qt::Horizontal, QObject::tr("Finished"));
    setHeaderData(DownloadConstants::Attributes::LastTryDate, Qt::Horizontal, QObject::tr("Last Try Date"));
    setHeaderData(DownloadConstants::Attributes::Description, Qt::Horizontal, QObject::tr("Description"));
    setHeaderData(DownloadConstants::Attributes::Referer, Qt::Horizontal, QObject::tr("Referer"));
    setHeaderData(DownloadConstants::Attributes::Type, Qt::Horizontal, QObject::tr("Type"));
    setHeaderData(DownloadConstants::Attributes::Pieces, Qt::Horizontal, QObject::tr("Pieces"));
    setHeaderData(DownloadConstants::Attributes::Uuid, Qt::Horizontal, QObject::tr("uuid"));
    //removeColumn(12);


}

//插入下载记录, 并返回该插入记录的行号,若失败返回-1
int modelDownloads::insertDownload(QString filename, //若filename为空，则取url的部分
                                   QString url,
                                   QString loc,
                                   QString desc,
                                   int type=0,
                                   QString ref="",
                                   int queue=0,
                                   int pieces=10,
                                   QString uuid=""){
    _logger->debug(QString("insertDownload:%1,%2,%3,%4,%5,%6,%7,%8,%9")
                   .arg(filename).arg(url).arg(loc).arg(desc)
                   .arg(type).arg(ref).arg(queue).arg(pieces).arg(uuid));
    qint64 dateAdded = QDateTime::currentMSecsSinceEpoch() / 1000;
    qint64 lastTry= dateAdded;

    int size = 0; // make zero size by default
    int finished=0; // set status to unfinished
    int status = 0;
    int transferRate=0;
    int elapsedTime =0;
    int newrow = 0;
    if(!insertRow(newrow)){ //在newrow之前插入记录， 该记录的编号为newrow，即0
        _logger->error("rowfailed to insert!");
        QMessageBox::critical(0,"failed","rowfailed to insert",QMessageBox::Ok);
        return -1;
    }

    if(filename==NULL || filename.isEmpty()){
        filename = QUrl(url).fileName();
    }

    //index包含(row,col), 设置index记录的列对应的值
    setFileName(newrow, filename ,false);
    setSize(newrow,size ,false);
    setURL(newrow, url ,false);
    setProgress(newrow, 0 ,false);
    setTransferRate(newrow, transferRate ,false);
    setTimeElapsed(newrow, elapsedTime ,false);

    setDateAdded(newrow, dateAdded ,false);
    setLastTry(newrow, lastTry ,false);

    setSaveLocation(newrow, loc ,false);
    setQueue(newrow, queue ,false);
    setStatus(newrow, status ,false);
    setFinishedStatus(newrow, finished ,false);
    setDescription(newrow, desc ,false);
    setReferer(newrow, ref ,false);
    setType(newrow, type ,false);
    setPieces(newrow, pieces ,false);
    setUuid(newrow, uuid ,false);

    if(!submitAll()){ //手动提交
        QSqlError err = lastError();
        _logger->debug("failed to insert-"+err.text());
        QMessageBox::critical(0,"failed","failed to insert-"+ err.text(),QMessageBox::Ok);
        return -1;
    }

    return newrow; //返回ID
}

//删除指定行
void modelDownloads::deleteDownload(int row){
    _logger->debug(QString("deleteDownload:row=%1").arg(row));
    if(!removeRow(row)){ //删除函数
        _logger->debug("failed to delete");
        QMessageBox::critical(0,"failed","failed to delete" + QString::number(row) + lastError().text(),QMessageBox::Ok);
    }else {
        if(!submitAll()){ //提交更新
            _logger->debug("failed to submit delete");
            QMessageBox::critical(0,"failed","failed to submit delete-" + lastError().text() + QString::number(row),QMessageBox::Ok);
        }
        else{
            _logger->debug("delete successful");
        }
    }
}

//item支持拖拽
Qt::ItemFlags modelDownloads::flags(const QModelIndex &index) const
{
   // _logger->debug("flags");

    //获取指定item的flags， 默认ItemIsEnabled|ItemIsSelectable
    Qt::ItemFlags defaultFlags = QSqlTableModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}



//START CRUD OPERATIONS////
// 以下为设置/获取各列的数据
QString modelDownloads::getFileName(int row){
    _logger->debug("getFileName-row="+row);
    return data(index(row,DownloadConstants::Attributes::FileName)).toString();
}

void modelDownloads::setFileName(int row, QString Filename, bool submit){
    _logger->debug(QString("setFileName:%1,%2").arg(row).arg(Filename));
    setData(index(row,DownloadConstants::Attributes::FileName),Filename);
    if(submit) submitAll();
}

QString modelDownloads::getURL(int row){
    _logger->debug(QString("getUrl:%1").arg(row));
    return data(index(row,DownloadConstants::Attributes::URL)).toString();
}

void modelDownloads::setURL(int row, QString URL, bool submit){
    _logger->debug(QString("setUrl:%1,%2").arg(row).arg(URL));
    setData(index(row,DownloadConstants::Attributes::URL),URL);
    if(submit) submitAll();
}

qint64 modelDownloads::getDateAdded(int row){
    _logger->debug(QString("getDateAdded:%1").arg(row));
    return data(index(row,DownloadConstants::Attributes::AddedDate)).toLongLong();
}

void modelDownloads::setDateAdded(int row, qint64 dateAdded, bool submit){
    _logger->debug(QString("setDateAdded:%1,%2").arg(row).arg(dateAdded));
    setData(index(row,DownloadConstants::Attributes::AddedDate),dateAdded);
   if(submit)  submitAll();
}

qint64 modelDownloads::getQueue(int row){
    _logger->debug("getQueue,"+row);
    return data(index(row,DownloadConstants::Attributes::Queue)).toLongLong();
}

void modelDownloads::setQueue(int row,qint64 queue, bool submit){
    _logger->debug(QString("setQueue,%1,%2").arg(row).arg(queue));
    setData(index(row,DownloadConstants::Attributes::Queue),queue);
    if(submit) submitAll();
}

qint64 modelDownloads::getSize(int row){
    _logger->debug(QString("getSize,%1").arg(row));
    //return data(index(row,DownloadConstants::Attributes::Size)).toLongLong();
    return _dm->getSize(data(index(row,DownloadConstants::Attributes::ID)).toLongLong());
}

void modelDownloads::setSize(int row,qint64 size, bool submit){
    _logger->debug(QString("setSize,%1,%2").arg(row).arg(size));
    setData(index(row,DownloadConstants::Attributes::Size),size);
    if(submit) submitAll();
}

qint64 modelDownloads::getFinishedStatus(int row){
    _logger->debug("getFinishedStatus,"+row);
    return data(index(row,DownloadConstants::Attributes::Downloaded)).toLongLong();
}

void modelDownloads::setFinishedStatus(int row,qint64 finishedStatus, bool submit){
    _logger->debug(QString("setFinishedStatus,%1,%2").arg(row).arg(finishedStatus));
    setData(index(row,DownloadConstants::Attributes::Downloaded),finishedStatus);
    if(submit) submitAll();
}

QString modelDownloads::getStatus(int row){
    _logger->debug("getStatus,"+QString::number(row));
    return data(index(row,DownloadConstants::Attributes::Status)).toString();
}

qint64 modelDownloads::getStatusOrg(int row){
    qint64 id = data(index(row, DownloadConstants::Attributes::ID)).toLongLong();
    return  _dm->getStatus(id);
}

void modelDownloads::setStatus(int row, qint64 status, bool submit){
    _logger->debug(QString("setStatus,%1,%2").arg(row).arg(status));
    setData(index(row,DownloadConstants::Attributes::Status),status);
    if(submit) submitAll();
}

QString modelDownloads::getTimeleft(int row){
    _logger->debug("getTimeleft,"+QString::number(row));
    return data(index(row,DownloadConstants::Attributes::RemainingTime)).toString();
}

void modelDownloads::setTimeLeft(int row, QString timeleft, bool submit){
    _logger->debug(QString("setTimeLeft,%1,%2").arg(row).arg(timeleft));
    setData(index(row,DownloadConstants::Attributes::RemainingTime),timeleft);
    if(submit) submitAll();
}

qint64 modelDownloads::getTransferRate(int row){
    _logger->debug("getTransferRate,"+row);
    //return data(index(row,DownloadConstants::Attributes::Speed)).toLongLong();
    return _dm->getTransferRate(data(index(row,DownloadConstants::Attributes::ID)).toLongLong());
}

void modelDownloads::setTransferRate(int row,qint64 transferRate, bool submit){
    _logger->debug(QString("setTransferRate,%1,%2").arg(row).arg(transferRate));
    setData(index(row,DownloadConstants::Attributes::Speed),transferRate);
    if(submit) submitAll();
}

qint64 modelDownloads::getLastTry(int row){
    _logger->debug("getLastTry,"+row);
    return data(index(row,DownloadConstants::Attributes::LastTryDate)).toLongLong();
}

void modelDownloads::setLastTry(int row,qint64 lastry, bool submit){
    _logger->debug(QString("setLastTry,%1,%2").arg(row).arg(lastry));
    setData(index(row,DownloadConstants::Attributes::LastTryDate),lastry);
    if(submit) submitAll();
}

QString modelDownloads::getDescription(int row){
    _logger->debug("getDescription,"+row);
    return data(index(row,DownloadConstants::Attributes::Description)).toString();
}

void modelDownloads::setDescription(int row,QString desc, bool submit){
    _logger->debug(QString("setDescription,%1,%2").arg(row).arg(desc));
    setData(index(row,DownloadConstants::Attributes::Description),desc);
    if(submit) submitAll();
}

QString modelDownloads::getSaveLocation(int row){
    _logger->debug("getSaveLocation,"+row);
    return data(index(row,DownloadConstants::Attributes::SavePath)).toString();
}

void modelDownloads::setSaveLocation(int row,QString saveLocation, bool submit){
    _logger->debug(QString("setSaveLocation,%1,%2").arg(row).arg(saveLocation));
    setData(index(row,DownloadConstants::Attributes::SavePath),saveLocation);
    if(submit) submitAll();
}

QString modelDownloads::getReferer(int row){
    _logger->debug("getReferer,"+row);
    return data(index(row,DownloadConstants::Attributes::Referer)).toString();
}

void modelDownloads::setReferer(int row,QString referer, bool submit){
    _logger->debug(QString("setReferer,%1,%2").arg(row).arg(referer));
    setData(index(row,DownloadConstants::Attributes::Referer),referer);
    if(submit) submitAll();
}

qint64 modelDownloads::getType(int row){
    _logger->debug("getType,"+row);
    return data(index(row,DownloadConstants::Attributes::Type)).toLongLong();
}

void modelDownloads::setType(int row,qint64 type, bool submit){
    _logger->debug(QString("setType,%1,%2").arg(row).arg(type));
    setData(index(row,DownloadConstants::Attributes::Type),type);
    if(submit) submitAll();
}

qint64 modelDownloads::getTimeElapsed(int row){
    _logger->debug("getTimeElapsed,"+row);
    return data(index(row,DownloadConstants::Attributes::ElapseTime)).toLongLong();
}

void modelDownloads::setTimeElapsed(int row,qint64 timeElapsed, bool submit){
    _logger->debug(QString("setTimeElapsed,%1,%2").arg(row).arg(timeElapsed));
    setData(index(row,DownloadConstants::Attributes::ElapseTime),timeElapsed);
    if(submit) submitAll();
}

qint64 modelDownloads::getPieces(int row){
    _logger->debug("getPieces,"+row);
    return data(index(row,DownloadConstants::Attributes::Pieces)).toLongLong();
}

void modelDownloads::setPieces(int row,qint64 pieces, bool submit){
    _logger->debug(QString("setPieces,%1,%2").arg(row).arg(pieces));
    setData(index(row,DownloadConstants::Attributes::Pieces),pieces);
    if(submit) submitAll();
}

QString modelDownloads::getUuid(int row){
    _logger->debug("getUuid,"+row);
    return data(index(row,DownloadConstants::Attributes::Uuid)).toString();
}

void modelDownloads::setUuid(int row, QString &uuid, bool submit){
    _logger->debug(QString("setUuid,%1,%2").arg(row).arg(uuid));
    setData(index(row,DownloadConstants::Attributes::Uuid), uuid);
    if(submit) submitAll();
}


qint64 modelDownloads::getID(int row){
    _logger->debug(QString("getID-row=%1").arg(row));
    return data(index(row, DownloadConstants::Attributes::ID)).toLongLong();
}

void modelDownloads::setID(int row, qint64 ID, bool submit){
    _logger->debug(QString("setID,%1,%2").arg(row).arg(ID));
    setData(index(row,DownloadConstants::Attributes::ID), ID);
    if(submit)  submitAll();
}


qint64 modelDownloads::getProgress(int row){
    _logger->debug("getProgress "+row);
    return data(index(row, DownloadConstants::Attributes::Progress)).toLongLong();
}

void modelDownloads::setProgress(int row, qint64 progress, bool submit){
    _logger->debug(QString("setProgress,%1,%2").arg(row).arg(progress));
    setData(index(row, DownloadConstants::Attributes::Progress), progress);
    if(submit) submitAll();
}

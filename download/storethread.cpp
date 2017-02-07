#include "storethread.h"
#include<QDebug>
#include<QMutex>
#include<QMutexLocker>
#include <QFile>



StoreThread::StoreThread(QObject *parent) :
    QThread(parent)
{
    _srcPath = _destPath = "";
    _bComplete = false;
    _id = -1;

    qDebug() << "new StoreThread----";
}

bool StoreThread::bComplete(){
    return _bComplete;
}

qint64 StoreThread::getID(){
    return _id;
}

void StoreThread::setCopyInfo(qint64 id, QString srcPath, QString destPath){
    qDebug() << "setCopyInfo:" << id << ", "<<srcPath << "," <<destPath;
    _id = id;
    _srcPath = srcPath;
    _destPath = destPath;
}

QString StoreThread::getSrcPath(){
    return _srcPath;
}

void StoreThread::run()
{
    qDebug()<< "store-thread run....";

    QMutexLocker locker(&qm);
    if(_srcPath.isEmpty() || _srcPath.isEmpty()){
        return;
    }

    if(QFile(_destPath).exists()){
        qDebug()<<"dest file had existed!, begin to delete it";
        QFile(_destPath).remove();
    }

    QFile f(_srcPath);
    qDebug() << "begin to copy: " << _srcPath <<" to " << _destPath;
    if(f.copy(_srcPath , _destPath)){
        _bComplete = true;
//        //拷贝完成，先设置状态
//        _dbMan->setStatus(id, Status::Finished);

//        //清除缓存
//        f.remove();

//        switchTaskStatus(id, Status::Finished);
    }
    else{
        _bComplete = false;
    }
    emit sig_storerlst();
    emit sig_storerlst(this);
    //QThread::sleep(1);

}

﻿#include "codec.h"
#include <QDir>
#include <QDebug>
#include <QProcess>
#include <QTextCodec>

Codec::Codec() :QObject(NULL)
{

}

Codec::~Codec()
{

}


//filename不含扩展名！！！！
void Codec::setFileInfo(QString srcpath, QString filename){
    mSrcPath = srcpath.endsWith("\\")?srcpath : (srcpath+"\\");
    mFileName = filename;
}

bool Codec::concat(){
    //qDebug() << "concat";
    //1. 创建索引文件
    mIdxFilePath = mSrcPath + mFileName + ".txt";
    //qDebug() << mIdxFilePath;

    QFile f(mIdxFilePath);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }

    //qDebug() << "write into file " << mIdxFilePath;
    QTextStream in(&f);
    QDir dir(mSrcPath);
    QFileInfoList flist = dir.entryInfoList( QStringList()<< mFileName+"*.mp4", QDir::Files, QDir::Name);
    foreach(QFileInfo fi, flist){
        QString str = QDir::toNativeSeparators(fi.absoluteFilePath());
        mSegList << str;
        in << QString("file '%1'\n").arg(str);
    }
    f.close();


    //2.执行ffmpeg
     QProcess *p = new QProcess(this);
     connect(p, SIGNAL(readyRead()), this, SLOT(on_read()));
     connect(p,SIGNAL(finished(int)),this,SLOT(onFinished(int)));
    QString command = "ffmpeg.exe";
    //command = "qrc:/other/bin/ffmpeg.exe";

    QStringList args;
    //args << "-loglevel" << "quiet" ;
    args << "-f" << "concat" ;
    args << "-safe" << "-1" << "-y";

    //下面这句中的 mIdxFilePath 如果用QString("'%1'").arg(mIdxFilePath)，会出错，并提示中文乱码(感觉是没有问题的，但实际是错的)
    args << "-i" << mIdxFilePath << "-c"<<"copy";

    args << "-bsf:a";
    args << "aac_adtstoasc";
    args <<  mSrcPath+mFileName+".mp4";

    p->start(command, args);
    p->execute(command, args);
    p->waitForFinished();
    qDebug()<<QString::fromUtf8(p->readAllStandardError());//获取输出

    return true;
}

void Codec::onFinished(int v){
    qDebug()<<"--------- onFinished -------------";
    //清除
    //removeTmp();
}

void Codec::on_read(){
    qDebug() << "-------- on_read ------------";
    QProcess *pProces = (QProcess *)sender();
    QString result = pProces->readAll();
    qDebug() << result;
}

QString Codec::getLastErr(){
    return mLastErr;
}

bool Codec::removeTmp(){
    //删除索引文件
    QFile f(mIdxFilePath);
    if(f.exists()){
        f.remove();

        //删除分段文件
        foreach (QString str, mSegList) {
            QFile f(str);
            f.remove();
        }
    }

    return true;
}
#include "codec.h"
#include <QDir>
#include <QDebug>
#include <QProcess>
#include <QTextCodec>

/*  Usage:
    Codec c;
    c.setFileInfo(srcpath, filename);
    c.concat();
*/


//concat为 阻断执行， concat()合并完成后，该函数才结束
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

//成功返回目标文件的路径
QString Codec::concat(){
    //qDebug() << "concat";
    //1. 创建索引文件
    mIdxFilePath = mSrcPath + "idx_" + mFileName + ".txt";
    //qDebug() << mIdxFilePath;

    QFile f(mIdxFilePath);
    if(!f.exists() || f.size() <= 0){
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
            return "";
        }

        //qDebug() << "write into file " << mIdxFilePath;
        QTextStream in(&f);
        QDir dir(mSrcPath);
        QFileInfoList flist = dir.entryInfoList( QStringList()<< mFileName+"*", QDir::Files, QDir::Name);
        foreach(QFileInfo fi, flist){
            QString str = QDir::toNativeSeparators(fi.absoluteFilePath());
            mSegList << str;
            in << QString("file '%1'\n").arg(str);
        }
        f.close();
    }



    //2.执行ffmpeg
    QString outfile = mSrcPath+mFileName+".mp4";
     QProcess *p = new QProcess(this);
     connect(p, SIGNAL(readyRead()), this, SLOT(on_read()));
     connect(p,SIGNAL(finished(int)),this,SLOT(onFinished(int)));
    QString command = "ffmpeg.exe";
    //command = "qrc:/other/bin/ffmpeg.exe";

    QStringList args;
  //  args << "-loglevel" << "quiet" ;
    args << "-f" << "concat" ;
    args << "-safe" << "-1" << "-y";

    //下面这句中的 mIdxFilePath 如果用QString("'%1'").arg(mIdxFilePath)，会出错，并提示中文乱码(感觉是没有问题的，但实际是错的)
    args << "-i" << mIdxFilePath << "-c"<<"copy";

    args << "-bsf:a";
    args << "aac_adtstoasc";
    args <<  outfile;

    p->start(command, args);
    p->execute(command, args);
    p->waitForFinished();
    qDebug()<<QString::fromUtf8(p->readAllStandardError());//获取输出

    QFile ff(outfile);
    if(ff.exists() && ff.size()>0){
        return outfile;
    }
    return "";
}

void Codec::onFinished(int v){
    qDebug()<<"--------- onFinished -------------";
    //清除
    removeTmp();
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
        qDebug() << "remove idxfile:" << mIdxFilePath;
        f.remove();

        //删除分段文件
        foreach (QString str, mSegList) {
            qDebug() << "remove tmp :" << str;
            QFile(str).remove();
        }
    }

    return true;
}

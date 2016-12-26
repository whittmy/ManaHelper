#include "download/mainwindow.h"
#include <QApplication>
#include <QtPlugin>
#include <QFile>

#include "util/xml_parser_playurl.h"
#include "util/codec.h"



static QString strPidFile;

void writePidFile()
{
    QFile file(strPidFile);
    if (!file.open(QIODevice::WriteOnly))
    {
        // << "Cannot write the pid file\n";
        exit(1);
    }
    file.write(QByteArray::number(100));
}


#include "webbrowser/browserapplication.h"
#include <qtwebenginewidgetsglobal.h>

int main(int argc, char *argv[])
{
    /*
    QApplication app(argc, argv);
    //---- 设置应用信息  QSettings需先设置这些， 在浏览器模块部分，这些代码都包含了，省略 >>>>>>>>
    app.setOrganizationName("LanMeng");
    app.setOrganizationDomain("lemoon.com");
    app.setApplicationName("LanMeng Manager Helper");

    app.addLibraryPath(".");
    app.setApplicationDisplayName("Manager Helper");
    app.setApplicationName("Manager Helper");
    app.setApplicationVersion("1.0");
    app.setDesktopSettingsAware(true);
    app.setWindowIcon(QIcon(":icons/images/icon.png"));
    */
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //if (!strPidFile.isEmpty())
    //        writePidFile();


//    QFile f("C:\\Users\\Administrator\\Desktop\\url.php.xml");
//    UrlDataParser p(f);
//    p.parser();
//    qDebug()<<p.getFiles();


//       Codec cd;
//       cd.setFileInfo("D:\\WorkSpace\\python\\you-get",  QStringLiteral("北上广依然相信爱情第8集"));
//       cd.concat();


//    QString fileNewName = "url.php";
//    QDir dir("c:\\qt_test\\");
//    //按名字逆序排列，获取最后一个片段的状态(片段是一个接一个按顺序下载，一个完成后才进行下一个片段)
//    QFileInfoList flist = dir.entryInfoList( QStringList()<< fileNewName+"*",
//                                             QDir::Files, QDir::Name|QDir::Reversed);
//    foreach(QFileInfo p, flist){
//        qDebug()<<"filter-file:"+p.fileName();
//    }


//    QString name = "url.php_mmh011";
//    int pos = name.indexOf(QRegExp("_mmh[0-9]{3}"));
//    int mCurSegIdx = name.mid(pos+4, 3).toInt()+1;
//    qDebug()<<QString::asprintf("_mmh%03d.download", mCurSegIdx);



    Q_INIT_RESOURCE(data);
    BrowserApplication application(argc, argv);
    if (!application.isTheOnlyBrowser())
        return 0;

    application.newMainWindow();
    return application.exec();


//    MainWindow w;
//    w.resize(800, 600);
//    w.move(200,100);
//    w.show();
    //return app.exec();
}




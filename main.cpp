#include "mainwindow.h"
#include <QApplication>
#include <QtPlugin>
#include <QFile>

#include "datareq/xml_parser_playurl.h"
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



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //---- 设置应用信息  QSettings需先设置这些 >>>>>>>>
    app.setOrganizationName("LanMeng");
    app.setOrganizationDomain("lemoon.com");
    app.setApplicationName("LanMeng Manager Helper");

    app.addLibraryPath(".");
    app.setApplicationDisplayName("Manager Helper");
    app.setApplicationName("Manager Helper");
    app.setApplicationVersion("1.0");
    app.setDesktopSettingsAware(true);
    app.setWindowIcon(QIcon(":icons/images/icon.png"));
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

    MainWindow w;
    w.resize(800, 600);
    w.move(200,100);
    w.show();
    return app.exec();
}




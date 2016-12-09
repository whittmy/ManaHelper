#include "mainwindow.h"
#include <QApplication>
#include <QtPlugin>
#include <QFile>
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

    MainWindow w;
    w.resize(800, 600);
    w.move(200,100);
    w.show();
    return app.exec();
}




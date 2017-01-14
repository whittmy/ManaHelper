#include "download/downloadui.h"
#include <QApplication>
#include <QtPlugin>
#include <QFile>

#include "util/xml_parser_playurl.h"
#include "util/codec.h"
#include "util/paths.h"

#include "download/downloadui.h"



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

//#pragma comment(lib,"Qt5Widgets.lib")
//#pragma comment(lib,"Qt5WebKitWidgets.lib")

int main(int argc, char *argv[])
{
    /* */
//    QApplication app(argc, argv);
//    //---- 设置应用信息  QSettings需先设置这些， 在浏览器模块部分，这些代码都包含了，省略 >>>>>>>>
//    app.setOrganizationName("LanMeng");
//    app.setOrganizationDomain("lemoon.com");
//    app.setApplicationName("LanMeng Manager Helper");

//    app.addLibraryPath(".");
//    app.setApplicationDisplayName("Manager Helper");
//    app.setApplicationName("Manager Helper");
//    app.setApplicationVersion("1.0");
//    app.setDesktopSettingsAware(true);
//    app.setWindowIcon(QIcon(":icons/images/icon.png"));

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //if (!strPidFile.isEmpty())
    //        writePidFile();

    Q_INIT_RESOURCE(data);
    BrowserApplication application(argc, argv);
    if (!application.isTheOnlyBrowser())
        return 0;

    application.newMainWindow();

    return application.exec();

//    DownLoadUI w;
//    w.resize(800, 600);
//    w.move(200,100);
//    w.show();
//    return app.exec();
}




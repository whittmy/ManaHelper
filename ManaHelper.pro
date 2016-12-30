#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27
#
#-------------------------------------------------

QT       += widgets core gui
QT	 +=sql
QT	 +=network
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# browser >>
QT       += webenginewidgets  printsupport
qtHaveModule(uitools):!embedded: QT += uitools
else: DEFINES += QT_NO_UITOOLS
#<<




TARGET = ManaHelper
TEMPLATE = app
LIBS += -luser32      ##解决RegisterDeviceNotification 链接出错问题




SOURCES += \
    webbrowser/autosave.cpp \
    webbrowser/downloadmgr.cpp \
    webbrowser/bookmarks.cpp \
    webbrowser/browserapplication.cpp \
    webbrowser/browsermainwindow.cpp \
    webbrowser/chasewidget.cpp \
    webbrowser/edittableview.cpp \
    webbrowser/edittreeview.cpp \
    webbrowser/featurepermissionbar.cpp\
    webbrowser/history.cpp \
    webbrowser/modelmenu.cpp \
    webbrowser/searchlineedit.cpp \
    webbrowser/settings.cpp \
    webbrowser/squeezelabel.cpp \
    webbrowser/tabwidget.cpp \
    webbrowser/toolbarsearch.cpp \
    webbrowser/urllineedit.cpp \
    webbrowser/webview.cpp \
    webbrowser/xbel.cpp \
    download/modeldownloads.cpp \
    download/downloadsdbmanager.cpp \
    download/optionsdialog.cpp \
    download/newdownloadinfodialog.cpp \
    download/downloadpropertydialog.cpp \
    download/downloadingprogressdialog.cpp \
    download/downloadfinisheddialog.cpp \
    download/autosaver.cpp \
    download/download.cpp \
    download/downloadholder.cpp \
    download/status.cpp \
    download/devmanagerdialog.cpp \
    download/upgradetipdialog.cpp \
    download/dloader_common.cpp \
    download/downloader.cpp \
    util/logme.cpp   \
    util/paths.cpp    \
    util/devdetector.cpp    \
    util/mytreeview.cpp \
    util/codec.cpp  \
    util/siteparser.cpp \
    systemtrayicon.cpp \
    util/httprequestor.cpp \
    util/xml_parser_upgrade.cpp \
    util/xml_parser_playurl.cpp \
    main.cpp \
    download/downloadui.cpp




HEADERS  += \
    #----- browser -------
    webbrowser/downloadmgr.h \
    webbrowser/autosave.h \
    webbrowser/bookmarks.h \
    webbrowser/browserapplication.h \
    webbrowser/browsermainwindow.h \
    webbrowser/chasewidget.h \
    webbrowser/edittableview.h \
    webbrowser/edittreeview.h \
    webbrowser/featurepermissionbar.h\
    webbrowser/history.h \
    webbrowser/modelmenu.h \
    webbrowser/searchlineedit.h \
    webbrowser/settings.h \
    webbrowser/squeezelabel.h \
    webbrowser/tabwidget.h \
    webbrowser/toolbarsearch.h \
    webbrowser/urllineedit.h \
    webbrowser/webview.h \
    webbrowser/xbel.h   \
    download/modeldownloads.h \
    download/downloadsdbmanager.h \
    download/optionsdialog.h \
    download/newdownloadinfodialog.h \
    download/downloadpropertydialog.h \
    download/downloadingprogressdialog.h \
    download/downloadfinisheddialog.h \
    download/autosaver.h \
    download/download.h \
    download/downloadconstants.h \
    download/downloadholder.h \
    download/status.h \
    download/devmanagerdialog.h \
    download/upgradetipdialog.h \
    download/downloader.h \
    download/dloader_common.h \
    util/paths.h    \
    util/devdetector.h    \
    util/mytreeview.h \
    util/codec.h    \
    util/logme.h \
    util/siteparser.h   \
    util/httprequestor.h \
    util/appendix.h  \
    util/xml_parser_playurl.h \
    util/xml_parser_upgrade.h \
    systemtrayicon.h \
    download/downloadui.h

UI_DIR= UI

FORMS    += \
    #---------- browser ------
    webbrowser/addbookmarkdialog.ui \
    webbrowser/bookmarks.ui \
    webbrowser/cookies.ui \
    webbrowser/cookiesexceptions.ui \
    webbrowser/downloaditem.ui \
    webbrowser/downloads.ui \
    webbrowser/history.ui \
    webbrowser/passworddialog.ui \
    webbrowser/proxy.ui \
    webbrowser/settings.ui  \
    download/optionsdialog.ui \
    download/newdownloadinfodialog.ui \
    download/downloadpropertydialog.ui \
    download/downloadingprogressdialog.ui \
    download/downloadfinisheddialog.ui \
    download/proxy.ui \
    download/passworddialog.ui \
    download/devmanagerdialog.ui \
    download/upgradetipdialog.ui \
    download/downloadui.ui

# browser-res
RESOURCES += data/data.qrc htmls/htmls.qrc

#
RESOURCES += images.qrc


# browser >>>
contains(DEFINES, QWEBENGINEPAGE_SETNETWORKACCESSMANAGER) {
    HEADERS += webbrowser/cookiejar.h     webbrowser/networkaccessmgr.h
    SOURCES += webbrowser/cookiejar.cpp webbrowser/networkaccessmgr.cpp
}

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

win32 {
   RC_FILE = browser.rc
}

mac {
    ICON = browser.icns
    QMAKE_INFO_PLIST = Info_mac.plist
    TARGET = Browser
}
EXAMPLE_FILES = Info_mac.plist browser.icns browser.ico browser.rc
# install
target.path = $$[QT_INSTALL_EXAMPLES]/webenginewidgets/browser
INSTALLS += target
# <<<



DISTFILES += \
    ManaHelper \
    images/media-playback-pause.png \
    images/restart.png.license \
    README.md

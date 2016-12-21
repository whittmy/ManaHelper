#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27
#
#-------------------------------------------------

QT       += widgets core gui
QT	 +=sql
QT	 +=network
QT       += xml
QT       += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ManaHelper
TEMPLATE = app
LIBS += -luser32      ##解决RegisterDeviceNotification 链接出错问题




SOURCES += main.cpp\
        mainwindow.cpp \
    backend/modeldownloads.cpp \
    backend/downloadsdbmanager.cpp \
    backend/logme.cpp   \
    dialogs/optionsdialog.cpp \
    dialogs/newdownloadinfodialog.cpp \
    dialogs/downloadpropertydialog.cpp \
    dialogs/downloadingprogressdialog.cpp \
    dialogs/downloadfinisheddialog.cpp \
    dialogs/adddownloaddialog.cpp \
    systemtrayicon.cpp \
    backend/networkaccessmanager.cpp \
    backend/autosaver.cpp \
    #backend/downloads.cpp   \
    download/download.cpp \
    download/downloadholder.cpp \
    #download/downloadtablemodel.cpp \
    download/status.cpp \
    util/paths.cpp    \
    util/devdetector.cpp    \
    util/mytreeview.cpp \
    util/codec.cpp  \
    download/downloader.cpp \
    datareq/httprequestor.cpp \
    dialogs/devmanagerdialog.cpp \
    dialogs/upgradetipdialog.cpp \
    download/dloader_common.cpp \
    datareq/xml_parser_upgrade.cpp \
    datareq/xml_parser_playurl.cpp


HEADERS  += mainwindow.h \
    backend/modeldownloads.h \
    backend/downloadsdbmanager.h \
    backend/logme.h \
    dialogs/optionsdialog.h \
    dialogs/newdownloadinfodialog.h \
    dialogs/downloadpropertydialog.h \
    dialogs/downloadingprogressdialog.h \
    dialogs/downloadfinisheddialog.h \
    dialogs/adddownloaddialog.h \
    systemtrayicon.h \
    backend/networkaccessmanager.h \
    backend/autosaver.h \
    backend/ui_proxy.h \
    backend/ui_passworddialog.h \
    #backend/downloads.h \
    download/download.h \
    download/downloadconstants.h \
    download/downloadholder.h \
    #download/downloadtablemodel.h \
    download/status.h \
    util/paths.h    \
    util/devdetector.h    \
    util/mytreeview.h \
    util/codec.h    \
    download/downloader.h \
    datareq/httprequestor.h \
    datareq/appendix.h  \
    dialogs/devmanagerdialog.h \
    dialogs/upgradetipdialog.h \
    download/dloader_common.h \
    datareq/xml_parser_playurl.h \
    datareq/xml_parser_upgrade.h

FORMS    += mainwindow.ui \
    dialogs/optionsdialog.ui \
    dialogs/newdownloadinfodialog.ui \
    dialogs/downloadpropertydialog.ui \
    dialogs/downloadingprogressdialog.ui \
    dialogs/downloadfinisheddialog.ui \
    dialogs/adddownloaddialog.ui \
    backend/proxy.ui \
    backend/passworddialog.ui \
    dialogs/devmanagerdialog.ui \
    dialogs/upgradetipdialog.ui

RESOURCES += images.qrc

DISTFILES += \
    ManaHelper \
    images/media-playback-pause.png \
    images/restart.png.license \
    README.md

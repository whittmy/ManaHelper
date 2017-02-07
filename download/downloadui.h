#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTreeWidgetItem>
#include <QSystemTrayIcon>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QUdpSocket>
#include <QtCore>
#include <QTimer>
#include <QSettings>
#include <QDir>
#include <QMessageBox>
#include <QClipboard>
#include <QFileDialog>
#include "ui_downloadui.h"
#include "download/newdownloadinfodialog.h"
#include "download/optionsdialog.h"
#include "systemtrayicon.h"
#include "download/downloadpropertydialog.h"
#include "download/adddownloaddialog_abandon.h"
#include "download/downloadsdbmanager.h"
#include "download/downloader.h"
#include "util/logme.h"
#include "util/devdetector.h"
#include <QSignalMapper>

#include "util/appendix.h"

namespace Ui {
class DownLoadUI;
}
class DownLoadUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DownLoadUI(QWidget *parent = 0);
    ~DownLoadUI();

public:
    SystemTrayIcon *TrayIcon;
    int CreateSystemTrayIcon();
    QMenu *TrayIconMenu;
    int AddUrlToAddDialog(QString);
    int StartListeningForAddUrl();
    AddDownloadDialog_abandon *adddownloaddialog;
    QUdpSocket *udpSocket;
    QItemSelectionModel *selectionModel;
    //QStandardItemModel *model;
    modelDownloads *model;
    QSortFilterProxyModel *proxyModel;
    DownloadsDBManager *_dbMan;
    void clearCacheData();
    void doCombine(qint64 id);
    void doStore(qint64 id);

    void doStart(qint64 id);

    void openAddTaskDlg(QString title, QString url);
    void setColumWidth();

    void clearCacheByName(QString fileName);
    void clearCacheOnStart();

    void initWindowInfo();
public slots:

    int UpdateInterface();
    int slotDownloadCompleted(const Download*);

    // 添加slots，运行中老是提示这些slot为定义
    //删除  moc_mainwindow.cpp文件，重新运行就ok了
    //DownLoader-relative slot
    void slotUpdateUrlsTable(const Download*);
    void slotDownloadResumed(const Download*);
    void slotDownloadRemoved(const Download*);
    void slotDownloadInited(const Download*);
    void slotDownloadFailed(const Download*);
    void slotTimerOut();

    void slotStoreRslt(QObject* obj);
private slots:
    void on_actionAdd_New_triggered();
    void on_actionQuit_triggered();
    void on_actionOptions_triggered();
    void on_categoriesTree_itemSelectionChanged();
    int TrayIconActivated(QSystemTrayIcon::ActivationReason);
    int ShowHideInterface();
    int ReadUrlAndProcess();

    void on_actionProperties_triggered();
    void on_actionDownload_Now_triggered();
    void on_actionRemove_triggered();
    void on_actionHide_Categories_triggered();
    void on_categoriesTree_customContextMenuRequested(const QPoint &pos);
    void on_dockWidgetContents_customContextMenuRequested(const QPoint &pos);
    void on_actionTo_text_file_triggered();
    void on_actionFrom_text_file_triggered();
    void on_actionDelete_All_Completed_triggered();
    void on_actionAbout_triggered();

    void on_actionPause_Download_triggered();

    void switchTaskStatus(qint64 id, int will_status);
    void on_DownloadsTable_clicked(const QModelIndex &index);

protected:


private:
    void checkFirstRun();
    void setDefaultSettings();
    void readSettings();
    void writeSettings();
    void _updateInterfaceByStatus(int status);
    void resetBtnStatus();
    void trayMsg(QString msg, QString filename);
private:
    Ui::DownLoadUI *ui;
    DownLoader* mDownLoader;
    LogMe* _logger;

    qint64 mLastProgress;
    qint64 mLastSpeed;

    QTimer *mTimer;

    QSignalMapper *_storeSignalMapper;
};

#endif // MAINWINDOW_H

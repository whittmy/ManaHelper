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
#include "download/newdownloadinfodialog.h"
#include "download/optionsdialog.h"
#include "systemtrayicon.h"
#include "download/downloadpropertydialog.h"
//#include "download/downloads.h"
#include "download/adddownloaddialog.h"
#include "download/downloadsdbmanager.h"
#include "download/downloader.h"
#include "util/logme.h"
#include "util/devdetector.h"

#include "util/appendix.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    SystemTrayIcon *TrayIcon;
    int CreateSystemTrayIcon();
    QMenu *TrayIconMenu;
    int AddUrlToAddDialog(QString);
    int StartListeningForAddUrl();
    AddDownloadDialog *adddownloaddialog;
    QUdpSocket *udpSocket;
    QItemSelectionModel *selectionModel;
    //QStandardItemModel *model;
    modelDownloads *model;
    QSortFilterProxyModel *proxyModel;
    DownloadsDBManager *dbMan;

public slots:

    int UpdateInterface();
    int ADownloadCompleted(QString);

    // 添加slots，运行中老是提示这些slot为定义
    //删除  moc_mainwindow.cpp文件，重新运行就ok了
    //DownLoader-relative slot
    void updateUrlsTable(const Download*);
    void submitUrlViewChanges();
    void onDownloadResumed(const Download*);
    void onDownloadRemoved(const QString &);
    void onDownloadDoesNotExistToRemove(const QUuid &);
    void onDownloadInited(const Download*);

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
    //void on_DownloadsTable_clicked(const QModelIndex &index);
    void on_actionRemove_triggered();
    void on_actionHide_Categories_triggered();
    void on_categoriesTree_customContextMenuRequested(const QPoint &pos);
    void on_dockWidgetContents_customContextMenuRequested(const QPoint &pos);
    void on_actionTo_text_file_triggered();
    void on_actionFrom_text_file_triggered();
    void on_actionDelete_All_Completed_triggered();
    void on_actionAbout_triggered();

    void on_actionStop_Download_triggered();

protected:


private:
    void checkFirstRun();
    void setDefaultSettings();
    void readSettings();
    void writeSettings();

    void doUpdateChk();
    static void ReqUgradeResult(REQ_TYPE type, QString str); //回调 静态

private:
    Ui::MainWindow *ui;
    DownLoader* mDownLoader;
    LogMe* _logger;
};

#endif // MAINWINDOW_H

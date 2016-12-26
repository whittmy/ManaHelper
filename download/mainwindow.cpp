﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "download/downloadconstants.h"
#include <QDesktopWidget>
#include "download/devmanagerdialog.h"

//upgrade check >>>>
#include "util/httprequestor.h"
#include "util/xml_parser_upgrade.h"
#include "download/upgradetipdialog.h"

extern QString gUrlArr[];
//<<<<


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _logger(new LogMe(this)),
   mDownLoader(new DownLoader())
{
    ui->setupUi(this);


    MainWindow::dbMan = new DownloadsDBManager();
    checkFirstRun();
    readSettings();
    model = new modelDownloads(this,dbMan->db);

    //////////////////////////////////////////////
    //启动时暂停所有任务状态。!!!
    //////////////////////////////////////////////




    //设定右侧下载列表QTableView 的数据模型
    ui->DownloadsTable->setModel(model);

    //设定左侧分类QTreeWidget的当前index
    ui->categoriesTree->setCurrentIndex(ui->categoriesTree->indexAt(QPoint(0,0)));

    //创建托盘图标(及右键菜单定义)
    CreateSystemTrayIcon();

    //监听本地 url ??????
    StartListeningForAddUrl();

    ///hide some columns
//    ui->DownloadsTable->hideColumn(0); //filename
//    ui->DownloadsTable->hideColumn(4); //status
//    ui->DownloadsTable->hideColumn(6); //transfer rate
//    ui->DownloadsTable->hideColumn(14);
    ui->DownloadsTable->resizeColumnsToContents();

    //signal-slot of DownLoader
    connect(mDownLoader, SIGNAL(downloadInitialed(const Download*)), this, SLOT(onDownloadInited(const Download*)));
    connect(mDownLoader, SIGNAL(downloadInitialed(const Download*)), this, SLOT(updateUrlsTable(const Download*)));
    connect(mDownLoader, SIGNAL(downloadPaused(const Download*)), this, SLOT(submitUrlViewChanges()));
    connect(mDownLoader, SIGNAL(downlaodResumed(const Download*)), this, SLOT(updateUrlsTable(const Download*)));
    connect(mDownLoader, SIGNAL(downlaodResumed(const Download*)), this, SLOT(onDownloadResumed(const Download*)));
    connect(mDownLoader, SIGNAL(downloadUpdated(const Download*)), this, SLOT(updateUrlsTable(const Download*)));
    connect(mDownLoader, SIGNAL(downloadRemoved(QString)), this, SLOT(onDownloadRemoved(QString)));
    connect(mDownLoader, SIGNAL(downloadDoesNotExistToRemove(QUuid)), this, SLOT(onDownloadDoesNotExistToRemove(QUuid)));
    connect(mDownLoader, SIGNAL(downloadFinished(QString)), this, SLOT(ADownloadCompleted(QString)));




    //升级检查 软件/设备
    doUpdateChk();

}


MainWindow::~MainWindow()
{
    delete ui;
    delete _logger;
    delete mDownLoader;
}





void MainWindow::doUpdateChk(){
//    HttpRequestor* request = HttpRequestor::Instance();
//    RequestInfo* info = new RequestInfo();
//    info->url = gUrlArr[UPGRADE_SELF];
//    info->reqType = UPGRADE_SELF;
//    info->callback = &MainWindow::ReqUgradeResult;
//    request->addTask(info);
}

void MainWindow::ReqUgradeResult(REQ_TYPE type, QString str){
    qDebug() << "----------- ReqUgradeResult ----------";

    Xml_Parser_Upgrade *dp = new Xml_Parser_Upgrade(str);
    dp->parser();
    if(dp->isValid()){
        qDebug() << dp->getUrl() << dp->getMd5() << dp->getDescription();

        //弹框提示
        UpgradeTipDialog *dlg = new UpgradeTipDialog();
        dlg->setModal(true);
        dlg->setData(type, dp);



        dlg->show();
    }


    //delete dlg;
}



//action_Add
// setUrl, setLocalModel
void MainWindow::on_actionAdd_New_triggered()
{
    _logger->debug("on_actionAdd_New_triggered");
    //Get Url from clipboard
    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *pMime = clipboard->mimeData();
    //QMessageBox::information(this,"Clipboard",clipboard->text(),QMessageBox::Ok);
    if(pMime->hasUrls()) { //若可以返回url列表
          QUrl url;
          foreach(url, pMime->urls()) //若多url，则针对每个url都弹出一个‘添加对话框’。
          {
              // do something with the url
              _logger->info(QString("open dlg for url:%").arg(url.toDisplayString()));
              AddDownloadDialog *addDownloadUi = new AddDownloadDialog(this);
              addDownloadUi->setUrl(url.toDisplayString()); //返回可读的url串，QUrl为数据结构
              addDownloadUi->setLocalModel(model); //设置 modelDownloads
              addDownloadUi->setDownLoader(mDownLoader);
              addDownloadUi->show();
          }
      }else{
        // 若单一url(也未必是url)
          AddDownloadDialog *addDownloadUi = new AddDownloadDialog(this);
          QUrl rl = QUrl::fromUserInput(clipboard->text());
          addDownloadUi->setUrl(rl.toDisplayString());
          _logger->info(QString("open dlg for single url:%").arg(rl.toDisplayString()));
          addDownloadUi->setLocalModel(model);
          addDownloadUi->setDownLoader(mDownLoader);
          addDownloadUi->show();
      }
}

//退出按钮，选择确认
void MainWindow::on_actionQuit_triggered()
{
    _logger->debug("on_actionQuit_triggered");
    int reply = QMessageBox::warning(this,"Confirm","Are you sure you want to quit?",QMessageBox::Yes,QMessageBox::No);
    if(reply==QMessageBox::Yes){
        writeSettings();
        qApp->quit();
    }
}

//两个事儿， 托盘图标 及其 菜单定义
int MainWindow::CreateSystemTrayIcon(){
    _logger->debug("CreateSystemTrayIcon");
    QAction *ShowHideAction = new QAction("Show/Hide Interface",this);
    connect(ShowHideAction, SIGNAL(triggered()), this, SLOT(ShowHideInterface()));
    QAction *QuitAction = new QAction("Quit",this);
    connect(QuitAction, SIGNAL(triggered()), this, SLOT(on_actionQuit_triggered()));

    TrayIconMenu = new QMenu();
    TrayIconMenu->addAction(ui->actionAdd_New);
    TrayIconMenu->addAction(ui->actionPause_All);
    TrayIconMenu->addSeparator();
    TrayIconMenu->addAction(ui->actionOptions);
    TrayIconMenu->addSeparator();
    TrayIconMenu->addAction(ShowHideAction);
    TrayIconMenu->addAction(QuitAction);
    ////////Bug Workaround///
    QSet<QWidget*> beforeWidgets = QApplication::topLevelWidgets().toSet();
    //////
    TrayIcon = new SystemTrayIcon(this);
    TrayIcon->setParent(this);
    TrayIcon->setIcon(QIcon(":/icons/images/icon.png"));
    TrayIcon->setContextMenu(TrayIconMenu);
    TrayIcon->setVisible(true);
    ///////Bug Workaround https://bugreports.qt-project.org/browse/QTBUG-30079 ////
    QSet<QWidget*> postWidgets = QApplication::topLevelWidgets().toSet();
    postWidgets -= beforeWidgets;
    if( !postWidgets.isEmpty() )
    {
         QWidget* sysWidget = (*postWidgets.begin());
         sysWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::SplashScreen );
         sysWidget->show();
    }
    ///////
    TrayIcon->setToolTip(qApp->applicationName());
    connect(TrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(TrayIconActivated(QSystemTrayIcon::ActivationReason)));
   // TrayIcon->showMessage("Welcome to Download Manager","This is a nice download manager",QSystemTrayIcon::Information,5000);
    return 0;
}

//显示/隐藏主界面
int MainWindow::ShowHideInterface(){
    _logger->debug("ShowHideInterface");
    if(isHidden()){
        show();
    }else{
        hide();
    }
    return 0;
}

//托盘图标的处理方式(槽)
int MainWindow::TrayIconActivated(QSystemTrayIcon::ActivationReason reason){
    _logger->debug(QString("TrayIconActivated,reason=%1").arg(reason));
    switch (reason){
        case QSystemTrayIcon::Trigger: //click
            if(isHidden()){
                if(TrayIcon->blinking){ //闪烁与否
                    TrayIcon->setBlink(false);
                    TrayIcon->setIcon(QIcon(":/icons/images/icon.png"));
                }
                show();
            }else{
                hide();
            }
            break;
        case QSystemTrayIcon::DoubleClick:
            break;
        case QSystemTrayIcon::MiddleClick:
            break;
        default:
            ;
    }
    return 0;
}


//读取窗口大小，并设置窗口大小位置
void MainWindow::readSettings()
{
    _logger->debug("readSettings");
    QSettings settings(this);
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);

}

//保存窗口相关参数
void MainWindow::writeSettings(){
    _logger->debug("writeSettings");
    QSettings settings(this);
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

//设置项的默认参数设置
void MainWindow::setDefaultSettings(){
    _logger->debug("setDefaultSettings");
    QSettings settings(this);

    //general start
    settings.setValue("maxRunningDownloads",4);
    settings.setValue("ConnectionsPerDownload",4);
    settings.setValue("showDownloadsCompleteDialog",true);
    settings.setValue("EnableSounds",true);
    //general end

    //saveto start
    QDir defaultLocation = QDir::home();
    defaultLocation.cd("Downloads");
    settings.setValue("generalDirectory",defaultLocation.path());

    defaultLocation.cd("Compressed");
    settings.setValue("compressedDirectory",defaultLocation.path());

    defaultLocation.cd("..");
    defaultLocation.cd("Documents");

    settings.setValue("documentDirectory",defaultLocation.path());

    defaultLocation.cd("..");
    defaultLocation.cd("Music");

    settings.setValue("musicDirectory",defaultLocation.path());

    defaultLocation.cd("..");
    defaultLocation.cd("Programs");

    settings.setValue("programDirectory",defaultLocation.path());

    defaultLocation.cd("..");
    defaultLocation.cd("Video");

    settings.setValue("videoDirectory",defaultLocation.path());
    //saveto end

    //categories start
    QString compressedExtensions= "zip rar r0* r1* arj gz sit sitx sea ace bz2 7z tar";
    settings.setValue("CompressedFileExtensions",compressedExtensions);
    settings.setValue("DocumentsFileExtensions","doc pdf ppt pps odt");
    settings.setValue("MusicFileExtensions","mp3 wav wma mpa ram ra aac aif m4a");
    settings.setValue("ProgramsExtensions","exe msi deb bin rpm run ");
    settings.setValue("VideoFileExtensions","avi mpg mpe mpeg asf wmv mov qt rm mp4 flv m4v webm ogv ogg");
    //categories end

    //network start
    settings.beginGroup(QLatin1String("proxy"));
    settings.setValue(QLatin1String("enabled"), false);
    settings.setValue(QLatin1String("type"), 0);
    settings.setValue(QLatin1String("hostName"),"");
    settings.setValue(QLatin1String("port"), 0);
    settings.setValue(QLatin1String("userName"), "");
    settings.setValue(QLatin1String("password"), "");
    settings.endGroup();
    //network end
}


//首次运行会 创建一系列目录， QDir::home()/Downloads/xx
//!!!!
void MainWindow::checkFirstRun(){
    _logger->debug("checkFirstRun");
    //关于QSettings, window系统默认存注册表,  HKEY_CURRENT_USER\Software\orgname\appname
    QSettings settings(this);

    //如果首次运行，firstRun为true
    bool firstRun = settings.value("firstRun",true).toBool();
    if(firstRun || !dbMan->isDbValid()){
        QDir defaultLocation = QDir::home();
        if(!defaultLocation.cd("Downloads")){
            defaultLocation.mkdir("Downloads");
            defaultLocation.cd("Downloads");
        }

        if(!defaultLocation.exists("Compressed")){
            defaultLocation.mkdir("Compressed");
        }

        if(!defaultLocation.exists("Documents")){
            defaultLocation.mkdir("Documents");
        }

        if(!defaultLocation.exists("Music")){
            defaultLocation.mkdir("Music");
        }

        if(!defaultLocation.exists("Programs")){
            defaultLocation.mkdir("Programs");
        }
        if(!defaultLocation.exists("Video")){
            defaultLocation.mkdir("Video");
        }
        //设置默认值
        setDefaultSettings();

        //生成并打开数据库
        dbMan->createDB();

        settings.setValue("firstRun",false);
    }
}

//选项对话框(非模态，可以同时打开多个)
void MainWindow::on_actionOptions_triggered()
{
    _logger->debug("on_actionOptions_triggered");
    OptionsDialog *optionsUi = new OptionsDialog;
    optionsUi->show();
}

void MainWindow::on_actionStop_Download_triggered(){
    _logger->debug("on_actionStop_Download_triggered");
    selectionModel= ui->DownloadsTable->selectionModel();//QItemSelectionModel, 返回当前选择的model
    QModelIndexList indexes = selectionModel->selectedRows(); //获取当前选择行的的model’index的列表， QModelIndexList
    foreach (QModelIndex index, indexes) { //遍历, 取最后一个？？
         int row = index.row(); // row-index: int type
         QUuid uuid = QUuid(model->getUuid(row));
         mDownLoader->pause(uuid);
     }
}


//左侧分类item选中变化联动实现，实际就是操作model的过程，数据变化带动
void MainWindow::on_categoriesTree_itemSelectionChanged(){
    _logger->debug("on_categoriesTree_itemSelectionChanged");
    int statusCat=-1; //parent-cata-idx
    int typeCat=-1; // child-cata-idx
    int queueCat=-1; //queque-cata-idx
    QTreeWidgetItem *currentCol = ui->categoriesTree->currentItem(); //获取当前选中的item
    QTreeWidgetItem *currentColP = ui->categoriesTree->currentItem()->parent(); //当前item的父item(组),若顶层则为NULL
    if(currentColP){ //父存在，则当前选中子item
        //parent exist, so user is in subcategory
        QString parentCat = currentColP->text(ui->categoriesTree->currentColumn()); //获取某item指定列(当前)的字符串
        if(parentCat.compare("All downloads")==0){
             statusCat=-1;//any
        }else if(parentCat.compare("Unfinished")==0){
            statusCat=0;//only unfinished
        }else if(parentCat.compare("Finished")==0){
            statusCat = 1;
        }else if(parentCat.compare("Queues")==0){
            statusCat = 0;//unfinished
        }

        QString childCat = currentCol->text(ui->categoriesTree->currentColumn());
        typeCat =-1;//any
        queueCat =-1;
        if(childCat.compare("Compressed")==0){
            typeCat =1;//1 for compressed
        }else if(childCat.compare("Documents")==0){
            typeCat =2;//2 for documents
        }
        else if(childCat.compare("Music")==0){
            typeCat =3;//3 for music
        }
        else if(childCat.compare("Programs")==0){
            typeCat =4;//4 for programs
        }
        else if(childCat.compare("Video")==0){
            typeCat =5;//5 for video
        }
        else if(childCat.compare("Main Queue")==0){
            queueCat=0;//0 for main queue
            statusCat = 0;//unfinished
        }
        else if(childCat.compare("Queue #1")==0){
            queueCat=1;//1 for queue 1
            statusCat = 0;//unfinished
        }
        else if(childCat.compare("Queue #2")==0){
            queueCat=2;//2 for queue 2
            statusCat = 0;//unfinished
        }
        else if(childCat.compare("Queue #3")==0){
            queueCat=3;//3 for queue 3
            statusCat = 0;//unfinished
        }
        //依据各选择类过滤符合的条目
        model->setFilterDownloads(statusCat,typeCat,queueCat);
    }else {
        //user selected a parent category
        QString parentCat = currentCol->text(ui->categoriesTree->currentColumn());
        if(parentCat.compare("All downloads")==0){
             statusCat=-1;//any
        }else if(parentCat.compare("Unfinished")==0){
            statusCat=0;//only unfinished
        }else if(parentCat.compare("Finished")==0){
            statusCat = 1;
        }else if(parentCat.compare("Queues")==0){
            statusCat = 0;//unfinished
        }
        model->setFilterDownloads(statusCat,typeCat,queueCat);
    }
//    ui->DownloadsTable->hideColumn(0);
//    ui->DownloadsTable->hideColumn(4);
//    ui->DownloadsTable->hideColumn(6);
//    ui->DownloadsTable->hideColumn(14);

    //model变化带动view变化
    //重新调整各列的大小，依据 hint
    ui->DownloadsTable->resizeColumnsToContents();
}

//这在启动时执行，监听待添加的url，
//感觉该函数类似于一个客户端。>>>>>>>>
int MainWindow::StartListeningForAddUrl(){
    _logger->debug("StartListeningForAddUrl");
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::LocalHost,45454);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(ReadUrlAndProcess()));
    return 0;
}

int MainWindow::ReadUrlAndProcess(){
    _logger->debug("ReadUrlAndProcess");
    QByteArray datagram;
    while(udpSocket->hasPendingDatagrams()){
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
//      qDebug(QString(datagram.data()).toAscii().data());
    }
    AddUrlToAddDialog(QString(datagram.data()));
    return 0;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<

//弹出对话框设置url下载信息，非模态
int MainWindow::AddUrlToAddDialog(QString Url){
    _logger->debug("AddUrlToAddDialog");
    NewDownloadInfoDialog *newDownloadUi = new NewDownloadInfoDialog(0,Url);
    newDownloadUi->setLocalModel(model);
    newDownloadUi->show();
    return 0;
}

// 主要依据选中的条目，更新界面上工具栏的按钮状态。
int MainWindow::UpdateInterface(){
    _logger->debug("UpdateInterface");
    ui->DownloadsTable->resizeColumnsToContents();
    selectionModel= ui->DownloadsTable->selectionModel();//QItemSelectionModel, 返回当前选择的model
    QModelIndexList indexes = selectionModel->selectedRows(); //获取当前选择行的的model’index的列表， QModelIndexList
    QModelIndex index;
    int row = -1;
    foreach (index, indexes) { //遍历, 取最后一个？？
        row = index.row(); // row-index: int type
    }

    //QModelIndex， model->index(row, column)获取指定行、列的modelindex， 用model->data(modelindex)便可获取其值。
    //int finished = model->data(model->index(row,DownloadConstants::Attributes::Downloaded)).toInt();
    int finished = model->getFinishedStatus(row);
    _logger->info("finished="+finished);
    if(finished==0){
        ui->actionDownload_Now->setEnabled(true); //如果未完成，立即下载按钮 激活
    }else if(finished ==1){
        ui->actionDownload_Now->setEnabled(false); //若干下载完成，则 下载、停止按钮 禁止。
        ui->actionStop_Download->setEnabled(false);
    }

    // index-7 代表下载状态，
    //QString value = model->data(model->index(row,7)).toString();
    QString value = model->getStatus(row);
    _logger->info("status="+value);
    if(value.contains("running")){
        ui->actionDownload_Now->setEnabled(false);
        ui->actionStop_Download->setEnabled(true);
    }else if(value.contains("paused")){
       ui->actionDownload_Now->setEnabled(true);
        ui->actionStop_Download->setEnabled(false);
    }else if(value.contains("error")){
        ui->actionDownload_Now->setEnabled(true);
         ui->actionStop_Download->setEnabled(false);
    }else if(value.contains("completed")){
        ui->actionDownload_Now->setEnabled(false);
         ui->actionStop_Download->setEnabled(false);
    }else if(value.contains("added")){
        ui->actionDownload_Now->setEnabled(false);
        ui->actionStop_Download->setEnabled(true);
    }

    //update the downloadsTableView
    //this->on_categoriesTree_itemSelectionChanged();
    return 0;
}

//条目属性按钮动作-弹出详细信息
void MainWindow::on_actionProperties_triggered()
{
    _logger->debug("on_actionProperties_triggered");
    // 1. 获取QTableView的QSelectModel
    // 2. 依据 QSelectModel 获取被选记录的列表QModelIndexList
    // 3. 确定所选记录的QModelIndex
    // 4. 获取行号  QModelIndex.row();
    // 5. 传入model和行号，对选中的每行弹出详细信息的对话框
    selectionModel= ui->DownloadsTable->selectionModel();
    QModelIndexList indexes = selectionModel->selectedRows();
    QModelIndex index;
    int row = -1;
    foreach (index, indexes) {
        row = index.row();
        _logger->info("open DownloadPropertyDialog for row:"+row);
        DownloadPropertyDialog *dpd = new DownloadPropertyDialog();
        dpd->setLocalModel(model);
        dpd->setIndex(row);
        dpd->show();
     }
}

//下载按钮，多选的记录就都开始下载
void MainWindow::on_actionDownload_Now_triggered()
{
    _logger->debug("on_actionDownload_Now_triggered");
    //TODO
    selectionModel= ui->DownloadsTable->selectionModel();
    QModelIndexList indexes = selectionModel->selectedRows();
    QModelIndex index;
    int row = -1;
    foreach (index, indexes) {
        row = index.row();
        int ID = model->getID(row);
        QString url = model->getURL(row);
        QString filename = model->getFileName(row);
        QString uuid = model->getUuid(row);

        //开始下载
        mDownLoader->start(ID, url, uuid, filename);
    }
}

//槽：下载完成
int MainWindow::ADownloadCompleted(QString message){
    _logger->debug("ADownloadCompleted");
    TrayIcon->showMessage("Download Completed",message,QSystemTrayIcon::Information,5000);
    if(isHidden()){
        if(!TrayIcon->blinking)
            TrayIcon->setBlink(true);
    }
    return 0;
}

//删除按钮
//model中要删除指定的记录
void MainWindow::on_actionRemove_triggered()
{
    _logger->debug("on_actionRemove_triggered");
    selectionModel= ui->DownloadsTable->selectionModel();
    QModelIndexList indexes = selectionModel->selectedRows();
    QModelIndex index;
    int row = -1;
    int reply = QMessageBox::question(this,"Confirm","Do you really want to delete these " +QString::number(indexes.count()) +" download(s)?",QMessageBox::Yes , QMessageBox::No);
    if(reply == QMessageBox::Yes){
        foreach (index, indexes) { //循环遍历
            row = index.row();
            model->deleteDownload(row);
        }
    }
}

// 大小字符串
QString formatSize(qulonglong size, bool persec){
    QString rval;

    if(size < 1024)
        rval = QString("%L1 B").arg(size);
    else if(size < 1024*1024)
        rval = QString("%L1 KB").arg(size/1024);
    else if(size < 1024*1024*1024)
        rval = QString("%L1 MB").arg(double(size)/1024.0/1024.0, 0, 'f', 1);
    else
        rval = QString("%L1 GB").arg(double(size)/1024.0/1024.0/1024.0, 0, 'f', 1);

    if(persec) rval += "/s";
    return rval;
}

//时间字符串
QString formatTime(qulonglong inval)
{
    QString result;
    qulonglong days,hrs,mins,secs;
    days = inval/(60*60*24);
    inval %= 60*60*24;

    hrs = inval/(60*60);
    inval %= 60*60;

    mins = inval/60;
    secs = inval%60;

    if(days)
        result = QString("%1d ").arg(days);
    if(hrs)
        result += QString("%1h ").arg(hrs);
    if(mins)
        result += QString("%1m ").arg(mins);
    if(secs)
        result += QString("%1s").arg(secs);

    return result;
}

// view菜单中 显示/隐藏左侧的分类
// 左侧的分类界面实际为 QDockWidget， 显示隐藏分别为 showNormal()/close()
// 并更新菜单项的文字信息
void MainWindow::on_actionHide_Categories_triggered()
{
    _logger->debug("on_actionHide_Categories_triggered");
    if(ui->actionHide_Categories->text().compare("Hide Categories")==0){
        ui->dockCategories->close();
        ui->actionHide_Categories->setText("Show Categories");
    }else{
        ui->dockCategories->showNormal();
        ui->actionHide_Categories->setText("Hide Categories");
    }
}

//左侧分类信息 categoriesTree控件的右键菜单的事件
//没有效果！！！！！
void MainWindow::on_categoriesTree_customContextMenuRequested(const QPoint &pos)
{
    _logger->debug("on_categoriesTree_customContextMenuRequested");
    int x = pos.x();
    int y= pos.y();
    qDebug()<<x<<","<<y;
    QMessageBox::information(this,"pos",QString::number(x) + " " +QString::number(y),QMessageBox::Ok);
}

//左侧分类的dockbar的邮件菜单
void MainWindow::on_dockWidgetContents_customContextMenuRequested(const QPoint &pos)
{
    _logger->debug("on_dockWidgetContents_customContextMenuRequested");
    int x = pos.x();
    int y= pos.y();
    QMessageBox::information(this,"pos22",QString::number(x) + " " +QString::number(y),QMessageBox::Ok);

}

//导出动作, 数据没有问题，但是就是没有写入到文件里。 需要flush一下才行。
void MainWindow::on_actionTo_text_file_triggered()
{
    _logger->debug("on_actionTo_text_file_triggered");
    //export
    QFileDialog filedialog(this);
    filedialog.setWindowTitle("Select the folder where you want to export.");
    //filedialog.setOption(QFileDialog::ShowDirsOnly);
    filedialog.setFileMode(QFileDialog::Directory);
    if(filedialog.exec()){
        QStringList seldir = filedialog.selectedFiles();
        QDir::setCurrent(seldir.first()); //list中的第一个

        //======>>>>>>>>>>>
        //导出 每行的列2的数据到一个 export.txt中
        // model->data(model->index(i,2));
        QFile f;
        f.setFileName("export.txt");
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&f);
        for(int i=0;i<model->rowCount();i++){
            qDebug() << model->data(model->index(i,2)).toString();
            out << model->data(model->index(i,2)).toString() << "\n";
        }
        out.flush();
        f.close();

        QMessageBox::information(this,"Exported Successfully","The current download list was successfully exported to \n"+seldir.first()+QDir::separator()+"export.txt",QMessageBox::Ok);
    }
    else return;
}

//导入动作，依据每个url弹出添加下载任务的对话框
void MainWindow::on_actionFrom_text_file_triggered()
{
    _logger->debug("on_actionFrom_text_file_triggered");
    //import
    QFileDialog filedialog(this);
    filedialog.setWindowTitle("Select the .txt file containing urls.");
    filedialog.setNameFilter(tr("Text (*.txt)"));;
    if(filedialog.exec()){ //打开目录对话框
        QStringList selfile = filedialog.selectedFiles().first().split(QDir::separator()); //用路径分隔符 分隔

        QFile f;
        f.setFileName(selfile.last());
        //QMessageBox::information(this,"file",selfile.last(),QMessageBox::Ok);
        selfile.removeLast();//删除路径中的文件名
        QDir d = QDir(selfile.join(QDir::separator())); //再拼接成路径
        d.setCurrent(d.absolutePath());//设置当前路径
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) //打开当前目录下的之前那个文件
            return;

        QTextStream in(&f); //f已被读打开
        QString url;
        int count=0;
        url=in.readLine();
        while(!url.isNull()){ //循环读取
            AddUrlToAddDialog(url); //打开对话框，添加url， 非模态对话框，同时打开多个
            count++;
            url = in.readLine();
        }
        f.close();
        QMessageBox::information(this,"Imported Successfully","Found " + QString::number(count)+" urls ",QMessageBox::Ok);
    }
    else return;
}

//清除所有完成的任务
void MainWindow::on_actionDelete_All_Completed_triggered()
{
    _logger->debug("on_actionDelete_All_Completed_triggered");
    int reply = QMessageBox::warning(this,"Confirm","Are you sure you want to DELETE the completed downloads from the list?\nNote:Actual files will not be deleted in this process.",QMessageBox::Yes,QMessageBox::No);
    if(reply==QMessageBox::Yes){
        int count=0;
        for(int i=0;i < model->rowCount();i++){ //遍历记录
            if(model->getFinishedStatus(i)==1){ //若完成，则从model中删除记录
                model->removeRow(i);
                count++;
            }
        }
        QMessageBox::information(this,"Removed Completed Downloads","Successfully removed "+ QString::number(count)+" downloads.",QMessageBox::Ok);
    }
}

//关于
void MainWindow::on_actionAbout_triggered()
{
   // About123 *about =new About123();
    //about->show();

    DevManagerDialog *dlg = new DevManagerDialog(this);
    dlg->show();
}


void MainWindow::onDownloadInited(const Download* download){
    _logger->debug("onDownloadInited");

}

//DownLoader - slots, 主要是ui上状态更新
void MainWindow::updateUrlsTable(const Download *download){
    _logger->debug("updateUrlsTable");

    //刷新之前记录选择状态，以备恢复，避免刷新中选择不了条目
    //step1
    selectionModel = ui->DownloadsTable->selectionModel();
    QModelIndexList selected = selectionModel->selectedIndexes();

    //更新数据
    for(int i=0; (i < model->rowCount()) && (model->getID(i) == download->ID()); i++){
        QString left = download->status()->remainingTime();
        qint64 speed = download->status()->downloadRate();
        Status::DownloadStatus status = download->status()->downloadStatus();
        if(status != Status::DownloadStatus::Downloading){
            speed = -1;
            left = "";
        }

        model->setStatus(i, status);
        model->setTimeLeft(i, left);
        model->setProgress(i, download->status()->progress());
        model->setTransferRate(i, speed);
        model->setSize(i, download->status()->bytesTotal());
    }

    //step2
    if(!selected.isEmpty()){
        _logger->debug("reset1");
        int i = 0;
        foreach(const QModelIndex&index, selected){
            _logger->debug(QString("reset %1").arg(i++));
            selectionModel->select(index,QItemSelectionModel::Select);
        }
    }
    _logger->debug("end updateUrlsTable");
}

void MainWindow::submitUrlViewChanges()
{

}


void MainWindow::onDownloadRemoved(const QString &fileName)
{
    _logger->debug("onDownloadRemoved, fileName="+fileName);
}

void MainWindow::onDownloadResumed(const Download *download)
{
    _logger->debug("onDownloadResumed");
}

void MainWindow::onDownloadDoesNotExistToRemove(const QUuid &uuid)
{
    _logger->debug("onDownloadDoesNotExistToRemove");
}



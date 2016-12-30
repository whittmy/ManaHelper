#include "downloadui.h"
#include "download/downloadconstants.h"
#include <QDesktopWidget>
#include "download/devmanagerdialog.h"
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include "util/paths.h"

#include "util/codec.h"


DownLoadUI::DownLoadUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DownLoadUI),
    _logger(new LogMe(this)),
    mDownLoader(new DownLoader())
{
    ui->setupUi(this);

    _dbMan = new DownloadsDBManager();
    checkFirstRun();
    readSettings();
    model = new modelDownloads(this,_dbMan);

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

    //hide some columns
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::ID);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::URL);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::Referer);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::Uuid);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::Pieces);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::ElapseTime);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::RemainingTime);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::LastTryDate);
    ui->DownloadsTable->resizeColumnsToContents();

    //signal-slot of DownLoader
    connect(mDownLoader, SIGNAL(downloadInitialed(const Download*)), this, SLOT(slotDownloadInited(const Download*)));
    connect(mDownLoader, SIGNAL(downloadInitialed(const Download*)), this, SLOT(slotUpdateUrlsTable(const Download*)));
    connect(mDownLoader, SIGNAL(downloadPaused(const Download*)), this, SLOT(UpdateInterface()));
    connect(mDownLoader, SIGNAL(downlaodResumed(const Download*)), this, SLOT(slotUpdateUrlsTable(const Download*)));
    connect(mDownLoader, SIGNAL(downlaodResumed(const Download*)), this, SLOT(slotDownloadResumed(const Download*)));
    connect(mDownLoader, SIGNAL(downloadUpdated(const Download*)), this, SLOT(slotUpdateUrlsTable(const Download*)));
    connect(mDownLoader, SIGNAL(downloadRemoved(const Download*)), this, SLOT(slotDownloadRemoved(const Download*)));
    connect(mDownLoader, SIGNAL(downloadFinished(const Download*)), this, SLOT(slotDownloadCompleted(const Download*)));
    connect(mDownLoader, SIGNAL(downloadFailed(const Download*)), this, SLOT(slotDownloadFailed(const Download*)));





    clearCacheData();

}

DownLoadUI::~DownLoadUI()
{
    delete ui;
    delete _logger;
    delete mDownLoader;
    //delete _timer;
}

//清缓存是必须做的，
//两个方面：1.清理所有已完成任务的缓存数据；2.遍历缓存缓存目录，查找所有残留的文件
void DownLoadUI::clearCacheData(){
    _logger->info("------------DownLoadUI::clearCacheData-------------");
}

//action_Add
// setUrl, setLocalModel
void DownLoadUI::on_actionAdd_New_triggered()
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
              openAddTaskDlg("", url.toDisplayString());
          }
      }else{
        // 若单一url(也未必是url)
          openAddTaskDlg("", QUrl::fromUserInput(clipboard->text()).toDisplayString());
      }
}

void DownLoadUI::openAddTaskDlg(QString title, QString url){
    NewDownloadInfoDialog *newDownloadUi = new NewDownloadInfoDialog(this, title, url);
    newDownloadUi->setLocalModel(model);
    newDownloadUi->setDownLoader(mDownLoader);
    newDownloadUi->show();
}

//退出按钮，选择确认
void DownLoadUI::on_actionQuit_triggered()
{
    _logger->debug("on_actionQuit_triggered");
    int reply = QMessageBox::warning(this,"Confirm","Are you sure you want to quit?",QMessageBox::Yes,QMessageBox::No);
    if(reply==QMessageBox::Yes){
        writeSettings();
        qApp->quit();
    }
}

//两个事儿， 托盘图标 及其 菜单定义
int DownLoadUI::CreateSystemTrayIcon(){
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
int DownLoadUI::ShowHideInterface(){
    _logger->debug("ShowHideInterface");
    if(isHidden()){
        show();
    }else{
        hide();
    }
    return 0;
}

//托盘图标的处理方式(槽)
int DownLoadUI::TrayIconActivated(QSystemTrayIcon::ActivationReason reason){
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
void DownLoadUI::readSettings()
{
    _logger->debug("readSettings");
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);

}

//保存窗口相关参数
void DownLoadUI::writeSettings(){
    _logger->debug("writeSettings");
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

//设置项的默认参数设置
void DownLoadUI::setDefaultSettings(){
    _logger->debug("setDefaultSettings");
    QSettings settings;

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
void DownLoadUI::checkFirstRun(){
    _logger->debug("checkFirstRun");
    //关于QSettings, window系统默认存注册表,  HKEY_CURRENT_USER\Software\orgname\appname
    QSettings settings;

    //如果首次运行，firstRun为true
    bool firstRun = settings.value("firstRun",true).toBool();
    if(firstRun || !_dbMan->isDbValid()){
        _logger->debug("-=-=-= is first run -=-=-");
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
        _dbMan->createDB();

        settings.setValue("firstRun",false);
    }
}

//选项对话框(非模态，可以同时打开多个)
void DownLoadUI::on_actionOptions_triggered()
{
    _logger->debug("on_actionOptions_triggered");
    OptionsDialog *optionsUi = new OptionsDialog;
    optionsUi->show();
}

void DownLoadUI::on_actionStop_Download_triggered(){
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
void DownLoadUI::on_categoriesTree_itemSelectionChanged(){
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
int DownLoadUI::StartListeningForAddUrl(){
    _logger->debug("StartListeningForAddUrl");
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::LocalHost,45454);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(ReadUrlAndProcess()));
    return 0;
}

int DownLoadUI::ReadUrlAndProcess(){
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
int DownLoadUI::AddUrlToAddDialog(QString Url){
    _logger->debug("AddUrlToAddDialog");
    NewDownloadInfoDialog *newDownloadUi = new NewDownloadInfoDialog(0, "", Url);
    newDownloadUi->setLocalModel(model);
    newDownloadUi->show();
    return 0;
}

// 主要依据选中的条目，更新界面上工具栏的按钮状态。
int DownLoadUI::UpdateInterface(){
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
    qint64 value = model->getStatusOrg(row);
    _logger->info(QString("status=%1").arg(Status::transDownLoadString(value)));

    switch(value){
    case Status::Downloading:
        ui->actionDownload_Now->setEnabled(false);
        ui->actionStop_Download->setEnabled(true);
        break;


    case Status::Idle:
        break;
    case Status::Failed:
        ui->actionDownload_Now->setEnabled(true);
        ui->actionStop_Download->setEnabled(false);
        break;
    case Status::Paused:
        ui->actionDownload_Now->setEnabled(true);
        ui->actionStop_Download->setEnabled(false);
        break;

    case Status::WaitCombine:
        break;
    case Status::WaitTrans:
        break;
    case Status::WaitStore:
        break;

    case Status::Finished:
        ui->actionDownload_Now->setEnabled(false);
         ui->actionStop_Download->setEnabled(false);
        break;

    }

    //update the downloadsTableView
    //this->on_categoriesTree_itemSelectionChanged();
    return 0;
}

//条目属性按钮动作-弹出详细信息
void DownLoadUI::on_actionProperties_triggered()
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
void DownLoadUI::on_actionDownload_Now_triggered()
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
        qint64 size = model->getSize(row);
        Status::DownloadStatus s = (Status::DownloadStatus)model->getStatusOrg(row);

        _logger->info(QString("cur status:%1").arg(Status::transDownLoadString(s)));

        switch(s){
        case Status::Downloading:
        case Status::Finished:
            _logger->info(QString("ignore operation"));
            return;

        case Status::Idle:
        case Status::Failed:
        case Status::Paused:
            //开始下载
            mDownLoader->start(row, ID, url, uuid, filename, size);
            return;

        case Status::WaitCombine:
            doCombine(row, filename);
            return;
        case Status::WaitTrans:
            break;
        case Status::WaitStore:
            doStore(row, filename);
            return;
        }
    }
}


//槽：下载完成
int DownLoadUI::slotDownloadCompleted(const Download *download){
    _logger->debug("ADownloadCompleted");
    //更新状态
    model->setStatus(download->_row, Status::WaitCombine);
    slotUpdateUrlsTable(download);

    TrayIcon->showMessage("Download Completed",download->name(),QSystemTrayIcon::Information,5000);
    if(isHidden()){
        if(!TrayIcon->blinking)
            TrayIcon->setBlink(true);
    }

    return 0;
}


void DownLoadUI::doStore(int row, QString filename){
    _logger->info("doStore");
    if(model->getStatusOrg(row) != Status::WaitStore)
        return;

    //获取任务的相关信息
    QString destPath = model->getSaveLocation(row);
    if(!QFile(destPath).exists()){
        QMessageBox::warning(this, "device error", "please check your device!");
        return;
    }

    if(!destPath.endsWith("\\") && !destPath.endsWith("/")){
        destPath = destPath + "/";
    }

    QString srcFilePath = Paths::cacheDirPath() + filename + ".mp4";
    QString destFilePath = destPath + filename + ".mp4";

    //开始拷贝到目的地,先判断设备
    QFile f(srcFilePath);
    if(f.copy(srcFilePath, destFilePath)){
        //拷贝完成，先设置状态
        model->setStatus(row, Status::Finished);

        //清除缓存
        f.remove();
    }
}

//合并文件,并更新任务状态
//目前是按照 mp4扩展名输出的。
void DownLoadUI::doCombine(int row, QString filename){
    _logger->info("doCombine- " + QString::number(model->getStatusOrg(row)));
    if(model->getStatusOrg(row) != Status::WaitCombine)
        return;

    QDir dir(Paths::cacheDirPath());
    //按名字排列，获取最后一个片段的状态(片段是一个接一个按顺序下载，一个完成后才进行下一个片段)
    QFileInfoList flist = dir.entryInfoList( QStringList()<< filename+"*",
                                             QDir::Files, QDir::Name);
    QString srcFilePath;
    int size = flist.size(); //获取段数
    if(size == 1){
        QFileInfo fi =  flist.at(0);
//        int dotpos = fi.fileName().lastIndexOf(".");
//        QString ext = fi.fileName().right(fi.fileName().length() - dotpos); // 如 .mp4

//        QFile f(fi.absoluteFilePath());
//        if(f.rename(QString("%1%2").arg(filename).arg(ext))){
//            //改名成功，更新任务状态
//            model->setStatus(row, Status::WaitStore, true);

//            srcFilePath = fi.absolutePath() + filename + ".mp4";
//        }
        QString newName = filename + ".mp4";
        QFile f(fi.absoluteFilePath());
        if(f.exists()){
            _logger->info("begin " + fi.absoluteFilePath() + " to " + newName);
        }
        if(f.rename(Paths::cacheDirPath() + newName)){ //目标文件名要带路径
            //改名成功，更新任务状态
            _logger->info("rename to "+newName);
            srcFilePath = Paths::cacheDirPath() + newName;
        }
    }
    else if(size > 1){
        //合并文件
        Codec cd;
        cd.setFileInfo(Paths::cacheDirPath(),  filename);
        srcFilePath = cd.concat();
    }

    //设置状态
    if(!srcFilePath.isEmpty()){
        _logger->info("combined to file:"+srcFilePath);
        model->setStatus(row, Status::WaitStore, true);
    }
}

//删除按钮
//model中要删除指定的记录
void DownLoadUI::on_actionRemove_triggered()
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
void DownLoadUI::on_actionHide_Categories_triggered()
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
void DownLoadUI::on_categoriesTree_customContextMenuRequested(const QPoint &pos)
{
    _logger->debug("on_categoriesTree_customContextMenuRequested");
    int x = pos.x();
    int y= pos.y();
    qDebug()<<x<<","<<y;
    QMessageBox::information(this,"pos",QString::number(x) + " " +QString::number(y),QMessageBox::Ok);
}

//左侧分类的dockbar的邮件菜单
void DownLoadUI::on_dockWidgetContents_customContextMenuRequested(const QPoint &pos)
{
    _logger->debug("on_dockWidgetContents_customContextMenuRequested");
    int x = pos.x();
    int y= pos.y();
    QMessageBox::information(this,"pos22",QString::number(x) + " " +QString::number(y),QMessageBox::Ok);

}

//导出动作, 数据没有问题，但是就是没有写入到文件里。 需要flush一下才行。
void DownLoadUI::on_actionTo_text_file_triggered()
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
void DownLoadUI::on_actionFrom_text_file_triggered()
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
void DownLoadUI::on_actionDelete_All_Completed_triggered()
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
void DownLoadUI::on_actionAbout_triggered()
{
   // About123 *about =new About123();
    //about->show();

    DevManagerDialog *dlg = new DevManagerDialog(this);
    dlg->show();
}


void DownLoadUI::slotDownloadInited(const Download* download){
    _logger->debug("onDownloadInited");

}

//DownLoader - slots, 主要是ui上状态更新
void DownLoadUI::slotUpdateUrlsTable(const Download *download){
    _logger->debug("updateUrlsTable1");
    if(download == NULL)
        return;

    if((mLastProgress == download->status()->progress()&& download->status()->progress() != 100)
            && mLastSpeed == download->status()->downloadRate())
        return;

     mLastProgress = download->status()->progress();

    _logger->debug("updateUrlsTable2");

    //刷新之前记录选择状态，以备恢复，避免刷新中选择不了条目
    //step1
    selectionModel = ui->DownloadsTable->selectionModel();
    QModelIndexList selected = selectionModel->selectedIndexes();

    //更新数据
    for(int i=0; (i < model->rowCount()) && (model->getID(i) == download->ID()); i++){
        QString left = download->status()->remainingTime();
        qint64 speed = download->status()->downloadRate();
        Status::DownloadStatus status = download->status()->downloadStatus();

        model->setStatus(i, status);
        model->setTimeLeft(i, left);
        model->setProgress(i, download->status()->progress());
        model->setTransferRate(i, speed);
        model->setSize(i, download->status()->bytesTotal());
    }

    //step2
    if(!selected.isEmpty()){
        //_logger->debug("reset1");
        int i = 0;
        foreach(const QModelIndex&index, selected){
            //_logger->debug(QString("reset %1").arg(i++));
            selectionModel->select(index,QItemSelectionModel::Select);
        }
    }
    _logger->debug("end updateUrlsTable");

}


void DownLoadUI::slotDownloadRemoved(const Download* download)
{
    _logger->debug("onDownloadRemoved, fileName="+ download->name());
}

void DownLoadUI::slotDownloadResumed(const Download *download)
{
    _logger->debug("onDownloadResumed");
}


void DownLoadUI::slotDownloadFailed(const Download* download){
    //更新状态
    model->setStatus(download->_row, Status::Failed);
    slotUpdateUrlsTable(download);

    TrayIcon->showMessage("Download Failed",download->name(),QSystemTrayIcon::Information,5000);
    if(isHidden()){
        if(!TrayIcon->blinking)
            TrayIcon->setBlink(true);
    }

}

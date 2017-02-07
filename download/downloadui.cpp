#include "downloadui.h"
#include "download/downloadconstants.h"
#include <QDesktopWidget>
#include "download/devmanagerdialog.h"
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include <QDesktopWidget>

#include "util/paths.h"

#include "util/codec.h"
#include "storethread.h"



DownLoadUI::DownLoadUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DownLoadUI),
    _logger(new LogMe(this)),
    mDownLoader(new DownLoader()),
    _storeSignalMapper(new QSignalMapper(this))
{
    ui->setupUi(this);

    //隐藏菜单
    ui->menuBar->hide();

    mTimer = new QTimer();

    //设置定时器每个多少毫秒发送一个timeout()信号
    mTimer->setInterval(1000);


    _dbMan = DownloadsDBManager::Instance();
    checkFirstRun();
    readSettings();
    model = new modelDownloads(this,_dbMan);

    //////////////////////////////////////////////
    //启动时暂停所有下载中(downloading/idle)的任务状态。!!!
    //且清除 已完成的任务(现阶段避免累计过大数据量，假设用户不原因自己删除)
    _dbMan->initStartUpStatus();
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
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::Queue);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::Downloaded);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::Description);
    ui->DownloadsTable->hideColumn(DownloadConstants::Attributes::Type);

    ui->DownloadsTable->horizontalHeader()->setSectionsClickable(false);
    ui->DownloadsTable->horizontalHeader()->setSectionsMovable(false);
    ui->DownloadsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //ui->DownloadsTable->horizontalHeader()->setStretchLastSection(false);//关键
    setColumWidth();
    //ui->DownloadsTable->resizeColumnsToContents();

    //signal-slot of DownLoader
    connect(mDownLoader, SIGNAL(downloadInitialed(const Download*)), this, SLOT(slotDownloadInited(const Download*)));
    connect(mDownLoader, SIGNAL(downloadPaused(const Download*)), this, SLOT(UpdateInterface()));
    connect(mDownLoader, SIGNAL(downlaodResumed(const Download*)), this, SLOT(slotDownloadResumed(const Download*)));
    connect(mDownLoader, SIGNAL(downloadRemoved(const Download*)), this, SLOT(slotDownloadRemoved(const Download*)));
    connect(mDownLoader, SIGNAL(downloadFinished(const Download*)), this, SLOT(slotDownloadCompleted(const Download*)));
    connect(mDownLoader, SIGNAL(downloadFailed(const Download*)), this, SLOT(slotDownloadFailed(const Download*)));

    connect(mTimer, SIGNAL(timeout()), this, SLOT(slotTimerOut()));


    clearCacheData();

    //启动定时器
    mTimer->start();

    //设置窗口界面默认的一些状态
    initWindowInfo();
}


void DownLoadUI::initWindowInfo(){
    int w = 1180;
    int h = 580;
    //setWindowFlags(Qt::WindowMinimizeButtonHint); // 设置禁止最大化
    setFixedSize(w, h); // 禁止改变窗口大小。

    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width()-w)/2, (desktop->height()-h)/2-30);
}

void DownLoadUI::resetBtnStatus(){
    _logger->info("resetBtnStatus");
    ui->actionAdd_New->setEnabled(false);
    ui->actionProperties->setEnabled(false);
    ui->actionQuit->setEnabled(false);
    ui->actionDownload_Now->setEnabled(false);
    ui->actionRemove->setEnabled(false);
    ui->actionRedownload->setEnabled(false);
    ui->actionPause_Download->setEnabled(false);
}

void DownLoadUI::setColumWidth(){
    ui->DownloadsTable->setColumnWidth(DownloadConstants::Attributes::FileName, 250);
    ui->DownloadsTable->setColumnWidth(DownloadConstants::Attributes::Size, 95);
    ui->DownloadsTable->setColumnWidth(DownloadConstants::Attributes::Progress, 90);
    ui->DownloadsTable->setColumnWidth(DownloadConstants::Attributes::Speed, 110);
    ui->DownloadsTable->setColumnWidth(DownloadConstants::Attributes::Status, 95);
    ui->DownloadsTable->setColumnWidth(DownloadConstants::Attributes::SavePath, 170);
}

void DownLoadUI::slotTimerOut(){
    //刷新之前记录选择状态，以备恢复，避免刷新中选择不了条目
    //step1
    selectionModel = ui->DownloadsTable->selectionModel();
    QModelIndexList selected = selectionModel->selectedIndexes();

    QTreeWidgetItem *currentCol = ui->categoriesTree->currentItem(); //获取当前选中的item
    //user selected a parent category
    QString parentCat = currentCol->text(ui->categoriesTree->currentColumn());
    int statusCat;
    if(parentCat.compare(tr("ui_Unfinished"))==0){
        statusCat= -1 ;//only unfinished
    }else if(parentCat.compare(tr("ui_Finished"))==0){
        statusCat = 0;
    }
    model->setFilterDownloads(statusCat);


   // model->refrushModel();

    //step2
    if(!selected.isEmpty()){
        //_logger->debug("reset1");
        int i = 0;
        foreach(const QModelIndex&index, selected){
            //_logger->debug(QString("reset %1").arg(i++));
            selectionModel->select(index,QItemSelectionModel::Select);
        }
    }

    //ui->DownloadsTable->resizeColumnsToContents();
}

DownLoadUI::~DownLoadUI()
{
    _logger->info("-------------------    ~DownLoadUI --------------");

    delete ui;
    delete _logger;
    delete mDownLoader;
    delete mTimer;
}

//注意内定slot的格式(const QModelIndex &index, 一点儿异样都允许)
void DownLoadUI::on_DownloadsTable_clicked(const QModelIndex &index){
    _logger->info("slotDownloadTabitemClicked row:" + QString::number(index.row()));

    resetBtnStatus();
    _updateInterfaceByStatus(model->getStatusOrg(index.row()));
}

//清缓存是必须做的，
//两个方面：1.清理所有已完成任务的缓存数据；2.遍历缓存缓存目录，查找所有残留的文件
void DownLoadUI::clearCacheData(){
    _logger->info("------------DownLoadUI::clearCacheData-------------");
    clearCacheOnStart();
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
    int reply = QMessageBox::warning(this,tr("ui_Confirm"),tr("ui_Are you sure you want to quit?"),QMessageBox::Yes,QMessageBox::No);
    if(reply==QMessageBox::Yes){
        writeSettings();
        qApp->quit();
    }
}

//两个事儿， 托盘图标 及其 菜单定义
int DownLoadUI::CreateSystemTrayIcon(){
    _logger->debug("CreateSystemTrayIcon");
    QAction *ShowHideAction = new QAction(tr("ui_Show/Hide Interface"),this);
    connect(ShowHideAction, SIGNAL(triggered()), this, SLOT(ShowHideInterface()));
    QAction *QuitAction = new QAction(tr("ui_Quit"),this);
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
//    _logger->debug("on_actionOptions_triggered");
//    OptionsDialog *optionsUi = new OptionsDialog;
//    optionsUi->show();
}

void DownLoadUI::on_actionPause_Download_triggered(){
    _logger->debug("on_actionPause_Download_triggered");
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
    resetBtnStatus();
    int statusCat=-1; //parent-cata-idx

    QTreeWidgetItem *currentCol = ui->categoriesTree->currentItem(); //获取当前选中的item
    //user selected a parent category
    QString parentCat = currentCol->text(ui->categoriesTree->currentColumn());

    if(parentCat.compare(tr("ui_Unfinished"))==0){
        statusCat= -1 ;//only unfinished
    }else if(parentCat.compare(tr("ui_Finished"))==0){
        statusCat = 0;
    }
    model->setFilterDownloads(statusCat);


    setColumWidth();
    //model变化带动view变化
    //重新调整各列的大小，依据 hint
    //ui->DownloadsTable->resizeColumnsToContents();
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
void DownLoadUI::_updateInterfaceByStatus(int status){
    ui->actionRemove->setEnabled(true);

    switch(status){
    case Status::Downloading:
        ui->actionDownload_Now->setEnabled(false);
        ui->actionPause_Download->setEnabled(true);
        break;


    //case Status::Idle:
    case Status::Failed:
        ui->actionDownload_Now->setEnabled(true);
        ui->actionPause_Download->setEnabled(false);
        break;

    case Status::Paused:
        ui->actionDownload_Now->setEnabled(true);
        ui->actionPause_Download->setEnabled(false);
        break;

    case Status::WaitCombine:
    case Status::WaitTrans:
    case Status::WaitStore:
        ui->actionDownload_Now->setEnabled(true);
        ui->actionPause_Download->setEnabled(false);
        break;

    case Status::Finished:
        ui->actionDownload_Now->setEnabled(false);
        ui->actionPause_Download->setEnabled(false);
        break;

    }
}

int DownLoadUI::UpdateInterface(){
    _logger->debug("UpdateInterface");
    //ui->DownloadsTable->resizeColumnsToContents();
    selectionModel= ui->DownloadsTable->selectionModel();//QItemSelectionModel, 返回当前选择的model
    QModelIndexList indexes = selectionModel->selectedRows(); //获取当前选择行的的model’index的列表， QModelIndexList
    QModelIndex index;
    int row = -1;
    foreach (index, indexes) { //遍历, 取最后一个？？
        row = index.row(); // row-index: int type
    }

    if(row == -1)
        return 0;
    //QModelIndex， model->index(row, column)获取指定行、列的modelindex， 用model->data(modelindex)便可获取其值。
    //int finished = model->data(model->index(row,DownloadConstants::Attributes::Downloaded)).toInt();

    // index-7 代表下载状态，
    //QString value = model->data(model->index(row,7)).toString();
    qint64 value = model->getStatusOrg(row);
    _logger->info(QString("status=%1").arg(Status::transDownLoadString(value)));

    _updateInterfaceByStatus(value);

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
        qint64 ID = model->getID(row);
//        QString url = model->getURL(row);
//        QString filename = model->getFileName(row);
//        QString uuid = model->getUuid(row);
//        qint64 size = model->getSize(row);
        Status::DownloadStatus s = (Status::DownloadStatus)model->getStatusOrg(row);

        _logger->info(QString("cur status:%1").arg(Status::transDownLoadString(s)));

        switch(s){
        case Status::Downloading:
        case Status::Finished:
            _logger->info(QString("ignore operation"));
            return;

       // case Status::Idle:
        case Status::Failed:
        case Status::Paused:
            //开始下载
            //mDownLoader->start(ID, url, uuid, filename, size);
            doStart(ID);
            return;

        //顺序执行
        case Status::WaitCombine:
            doCombine(ID);
            return;
        case Status::WaitTrans:
        case Status::WaitStore:
            doStore(ID);
            return;
        }
    }
}

void DownLoadUI::switchTaskStatus(qint64 id, int will_status){
    if(will_status == Status::WaitCombine){
        doCombine(id);
    }
    else if(will_status == Status::WaitStore){
        doStore(id);
    }
    else if(will_status == Status::Finished){
        trayMsg(tr("ui_Download Completed"), _dbMan->getFileName(id));
    }
    else if(will_status == Status::Failed){
        trayMsg(tr("ui_Download Failed"), _dbMan->getFileName(id));
    }
}

//槽：下载完成
int DownLoadUI::slotDownloadCompleted(const Download *download){
    _logger->debug("slotDownloadCompleted");
    //更新状态
    _dbMan->setStatus(download->ID(), Status::WaitCombine);

    //slotUpdateUrlsTable(download);

    if(download->bfileValid()){
        ((Download*)download)->closeFile();
        ((Download*)download)->setFile(0);
    }
    switchTaskStatus(download->ID(), Status::WaitCombine);

    /*
    QString name = Paths::filter(download->name());

    //begin to combine
    if(download->getSegCnt() == 1){
        QDir dir(Paths::mvCachePath());
        QFileInfoList flist = dir.entryInfoList( QStringList()<< name+"*",
                                                 QDir::Files, QDir::Name|QDir::Reversed);
        foreach(QFileInfo p, flist){
            QFile(p.absoluteFilePath()).rename(Paths::mvCachePath() + name + ".mp4"); //rename 一定要全路径
            _dbMan->setStatus(download->ID(), Status::WaitStore);
            break;
        }
    }
    else{
        Codec c;
        c.setFileInfo(Paths::mvCachePath(), name);
        if(!c.concat().isEmpty())
            _dbMan->setStatus(download->ID(), Status::WaitStore);
    }

    if(_dbMan->getStatus(download->ID()) == Status::WaitStore){
        switchTaskStatus(download->ID(), Status::WaitStore);
    }
    else{
        _logger->error("doCombine failed!");
    }
    */

    return 0;
}

//trayMsg("Download Completed", download->name());

void DownLoadUI::trayMsg(QString msg, QString filename){
    TrayIcon->showMessage(msg, filename, QSystemTrayIcon::Information, 5000);
    if(isHidden()){
        if(!TrayIcon->blinking)
            TrayIcon->setBlink(true);
    }
}

void DownLoadUI::doStore(qint64 id){
    _logger->info("doStore====" + QString::number(id)+", "+_dbMan->getFileName(id));
    if(_dbMan->getStatus(id) != Status::WaitStore)
        return;
    QString filename = Paths::filter(_dbMan->getFileName(id));

    //获取任务的相关信息
    QString destPath = QDir::toNativeSeparators(DevDetector::getDevPath() + _dbMan->getSaveLocation(id));
    if(!QDir(destPath).exists()){
        //QMessageBox::warning(this, "device error", "please check your device!");
        _logger->error("doStore failed for without device!!,"+destPath);
        return;
    }

    if(!destPath.endsWith("\\") && !destPath.endsWith("/")){
        destPath = destPath + "/";
    }

    QString srcFilePath = Paths::mvCachePath() + filename + ".mp4";
    QString destFilePath = destPath + filename + ".mp4";

    StoreThread* pthread = new StoreThread();
    pthread->setCopyInfo(id, srcFilePath, destFilePath);

    connect(pthread, SIGNAL(sig_storerlst()), _storeSignalMapper, SLOT(map()));
    _storeSignalMapper->setMapping(pthread, pthread);
    connect(_storeSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(slotStoreRslt(QObject*)));

    pthread ->start();
//    //开始拷贝到目的地,先判断设备
//    QFile f(srcFilePath);
//    if(f.copy(srcFilePath, destFilePath)){
//        //拷贝完成，先设置状态
//        _dbMan->setStatus(id, Status::Finished);

//        //清除缓存
//        f.remove();

//        switchTaskStatus(id, Status::Finished);
//    }
}

void DownLoadUI::slotStoreRslt(QObject *obj){
    qDebug() << "slotStoreRslt(*obj)" ;
    if(obj == NULL)
        return;

    StoreThread *pThread = (StoreThread *) obj;
    if(pThread->bComplete()){
        //拷贝完成，先设置状态
        _dbMan->setStatus(pThread->getID(), Status::Finished);

        //清除缓存
        QFile(pThread->getSrcPath()).remove();
        switchTaskStatus(pThread->getID(), Status::Finished);

        _logger->info("slotStoreRslt  ok");
    }
    else {
        _logger->info("slotStoreRslt  failed");
    }

}

void DownLoadUI::doStart(qint64 id){
    _logger->info("doStart-" + QString::number(id) + ", " + _dbMan->getFileName(id));
    Status::DownloadStatus status =  (Status::DownloadStatus)_dbMan->getStatus(id);
    if(status == Status::Downloading
            || status == Status::Finished){
        _logger->info("the task is downloading/finished status, we dont start it");
        return;
    }

    QString url = _dbMan->getURL(id);
    QString filename =  _dbMan->getFileName(id);
    QString uuid = _dbMan->getUuid(id);
    qint64 size = _dbMan->getSize(id);

    //开始下载
    mDownLoader->start(id, url, uuid, filename, size);
}


//合并文件,并更新任务状态
//目前是按照 mp4扩展名输出的。
void DownLoadUI::doCombine(qint64 id){
    _logger->info("doCombine- " + QString::number(id)+", "+_dbMan->getFileName(id));
    if(_dbMan->getStatus(id) != Status::WaitCombine)
        return;

    QString filename = Paths::filter(_dbMan->getFileName(id));
    QDir dir(Paths::mvCachePath());
    //按名字排列，获取最后一个片段的状态(片段是一个接一个按顺序下载，一个完成后才进行下一个片段)
    QFileInfoList flist = dir.entryInfoList( QStringList()<< filename+"*",
                                             QDir::Files, QDir::Name);
   QString srcFilePath;
    int size = flist.size(); //获取段数
    qDebug() << "filter the cache for " << filename+"*, and get cache cnt:" << size;
    if(size == 1){
        _logger->info(" go combine switch for single-cache!!");
        QFileInfo fi =  flist.at(0);
        QString newName = Paths::mvCachePath() + filename + ".mp4";
        QFile f(fi.absoluteFilePath());
        if(f.exists()){
            _logger->info("rename begin " + fi.absoluteFilePath() + " to " + newName);
            if(f.fileName().compare(filename+".mp4", Qt::CaseInsensitive) == 0){
                _logger->info("same as destname");
                srcFilePath =  newName;
            }
            else if(f.rename( newName)){ //目标文件名要带路径
                //改名成功，更新任务状态
                _logger->info("successfull rename to "+newName);
                srcFilePath =  newName;
            }
            else{
                _logger->error("doCombine-rename failed:"+newName);
            }
        }
        else{
            _dbMan->setStatus(id, Status::Failed);
            switchTaskStatus(id, Status::Failed);
            return;
        }
    }
    else if(size > 1){
        _logger->info(" go combine switch for multi-cache!!");
        //合并文件
        Codec cd;
        cd.setFileInfo(Paths::mvCachePath(),  filename);
        srcFilePath = cd.concat();
    }

    //设置状态
    if(!srcFilePath.isEmpty()){
        _logger->info("combined sucessfully:"+srcFilePath);
        _dbMan->setStatus(id, Status::WaitStore);
        switchTaskStatus(id, Status::WaitStore);
    }
    else{
        _logger->error("doCombine failed!!!");
    }
}

//删除按钮
//model中要删除指定的记录, 要删暂停！！！！！！
void DownLoadUI::on_actionRemove_triggered()
{
    _logger->debug("on_actionRemove_triggered");
    selectionModel= ui->DownloadsTable->selectionModel();
    QModelIndexList indexes = selectionModel->selectedRows(DownloadConstants::Attributes::ID);//DownloadConstants::Attributes::FileName
    int row = -1;
    int reply = QMessageBox::question(this,tr("ui_Confirm"),tr("ui_Do you really want to delete these ") +QString::number(indexes.count()) +tr("ui_ download(s)?"),QMessageBox::Yes , QMessageBox::No);
    if(reply == QMessageBox::Yes){
        //顺序遍历会出问题的
//        foreach (QModelIndex index, indexes) { //循环遍历
//            row = index.row();
//            qDebug() << "del row: " <<row << ",data=" << model->data(index);
//            model->deleteDownload(row);
//        }

        //需要逆向遍历，否则删除前面后，就直接影响行的变化，导致出错。
        QList<QModelIndex>::iterator iter = indexes.end();
        iter --;
        while(iter >= indexes.begin()){
            row = (*iter).row();
            QString name = Paths::filter(model->getFileName(row));
            QString uuid = model->getUuid(row);


            //1. pause it,
            mDownLoader->pause(uuid);
            qDebug() << "del row: " <<row << ",name=" << name << ", uuid=" << uuid;

            //2. delete
            model->deleteDownload(row);

            //3. clear cache
            clearCacheByName(name); //过滤
            iter --;
        }
    }
}

void DownLoadUI::clearCacheOnStart(){
    _logger->info("enter clearCacheOnStart");
    //获取所有下载中的文件名
    QSet<QString> names = _dbMan->getFileNameListDownloading();
    qDebug() << names;

    //遍历缓存目录， 删除不在“下载中”中的文件
    QDir dir(Paths::mvCachePath());
    QFileInfoList flist = dir.entryInfoList(QDir::Files);
    foreach(QFileInfo p, flist){
        QString filename = p.fileName();
        int pos = filename.lastIndexOf("_mmh");
        if(pos != -1){
            filename = filename.mid(0, pos);
        }
        else{
            pos = filename.lastIndexOf(".mp4");
            if(pos != -1)
                filename = filename.mid(0, pos);
        }
        if(!names.contains(filename)){
            _logger->info("delete cache file:" + filename);
            QFile(p.absoluteFilePath()).remove();
        }
    }

}

void DownLoadUI::clearCacheByName(QString fileName){
    _logger->info("into clearCacheByName: "+ fileName);
    QString cachePath = Paths::mvCachePath();
    QDir dir(cachePath);
    //按名字逆序排列，获取最后一个片段的状态(片段是一个接一个按顺序下载，一个完成后才进行下一个片段)
    QFileInfoList flist = dir.entryInfoList( QStringList()<< fileName+"*",
                                             QDir::Files, QDir::Name|QDir::Reversed);
    foreach(QFileInfo p, flist){
        _logger->info("remove file "+p.fileName());
        QFile(p.absoluteFilePath()).remove();
    }

    QString idxfilepath = cachePath + "idx_" + fileName + ".txt";
    if(QDir(idxfilepath).exists())
        QFile(idxfilepath).remove();
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
    if(ui->actionHide_Categories->text().compare(tr("ui_Hide Categories"))==0){
        ui->dockCategories->close();
        ui->actionHide_Categories->setText(tr("ui_Show Categories"));
    }else{
        ui->dockCategories->showNormal();
        ui->actionHide_Categories->setText(tr("ui_Hide Categories"));
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
    QMessageBox::information(this,tr("ui_pos"),QString::number(x) + " " +QString::number(y),QMessageBox::Ok);
}

//左侧分类的dockbar的邮件菜单
void DownLoadUI::on_dockWidgetContents_customContextMenuRequested(const QPoint &pos)
{
    _logger->debug("on_dockWidgetContents_customContextMenuRequested");
    int x = pos.x();
    int y= pos.y();
    QMessageBox::information(this,tr("ui_pos22"),QString::number(x) + " " +QString::number(y),QMessageBox::Ok);

}

//导出动作, 数据没有问题，但是就是没有写入到文件里。 需要flush一下才行。
void DownLoadUI::on_actionTo_text_file_triggered()
{
    _logger->debug("on_actionTo_text_file_triggered");
    //export
    QFileDialog filedialog(this);
    filedialog.setWindowTitle(tr("ui_Select the folder where you want to export."));
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

        QMessageBox::information(this,tr("ui_Exported Successfully"),tr("ui_The current download list was successfully exported to \n")+seldir.first()+QDir::separator()+"export.txt",QMessageBox::Ok);
    }
    else return;
}

//导入动作，依据每个url弹出添加下载任务的对话框
void DownLoadUI::on_actionFrom_text_file_triggered()
{
    _logger->debug("on_actionFrom_text_file_triggered");
    //import
    QFileDialog filedialog(this);
    filedialog.setWindowTitle(tr("ui_Select the .txt file containing urls."));
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
        QMessageBox::information(this,tr("ui_Imported Successfully"),"Found " + QString::number(count)+" urls ",QMessageBox::Ok);
    }
    else return;
}

//清除所有完成的任务
void DownLoadUI::on_actionDelete_All_Completed_triggered()
{
    _logger->debug("on_actionDelete_All_Completed_triggered");
    int reply = QMessageBox::warning(this,tr("ui_Confirm"),tr("ui_Are you sure you want to DELETE the completed downloads from the list?\nNote:Actual files will not be deleted in this process."),QMessageBox::Yes,QMessageBox::No);
    if(reply==QMessageBox::Yes){
        int count=0;
        for(int i=0;i < model->rowCount();i++){ //遍历记录
            if(model->getFinishedStatus(i)==1){ //若完成，则从model中删除记录
                model->removeRow(i);
                count++;
            }
        }
        QMessageBox::information(this,tr("ui_Removed Completed Downloads"),tr("ui_Successfully removed ")+ QString::number(count)+tr("ui_ downloads."),QMessageBox::Ok);
    }
}

//关于
void DownLoadUI::on_actionAbout_triggered()
{
    DevManagerDialog *dlg = new DevManagerDialog(this);
    dlg->show();
}


void DownLoadUI::slotDownloadInited(const Download* download){
    _logger->debug("onDownloadInited");

}

//DownLoader - slots, 主要是ui上状态更新
void DownLoadUI::slotUpdateUrlsTable(const Download *download){
    return;
    /*
    _logger->debug("updateUrlsTable1");

    if(download == NULL)
        return;

    qint64 speed = download->status()->downloadRate();
    qint64 progress = download->status()->progress();
    _logger->info(QString("speed=%1,lastspeed=%2,progress=%3,lastprog=%4").arg(speed).arg(download->status()->getLastSpeed()).arg(progress).arg(download->status()->getLastProgress()));

    if((download->status()->getLastProgress() == progress && progress != 100)
            && download->status()->getLastSpeed() == speed)
        return;

    download->status()->setLastProgress(progress);
    download->status()->setLastSpeed(speed);

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
*/
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
    _dbMan->setStatus(download->ID(), Status::Failed);
    //model->setStatus(download->_row, Status::Failed);  //根据row来更新数据是不靠谱的，原因是行会随着操作变化
    //slotUpdateUrlsTable(download);

    trayMsg(tr("ui_Download Failed"), download->name());
}

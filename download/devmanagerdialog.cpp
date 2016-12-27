#include "devmanagerdialog.h"
#include "ui_devmanagerdialog.h"
#include <QTreeView>
#include <QDirModel>
#include <QDebug>
#include "util/devdetector.h"

QString getDriver(){
    return DevDetector::getDevPath();
}

DevManagerDialog::DevManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DevManagerDialog),
    _logger(new LogMe(this))
{
    ui->setupUi(this);

    _treeView_dir = new MyTreeView(this);
    _treeView_dir->setObjectName(QStringLiteral("treeView_dir"));
    _treeView_dir->setGeometry(QRect(10, 20, 210, 431));

    initResource();

//    QStringList filters;
//    filters<<QString("*.jpeg")<<QString("*.jpg")<<QString("*.png")<<QString("*.tiff")<<QString("*.gif")<<QString("*.bmp");

    MyTreeModel *model = new MyTreeModel (_treeView_dir);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("directory"));// <<QStringLiteral("info"));
    _treeView_dir->setModel(model);
    addTopItemsForTreeView(model, QDir(getDriver()));


    connect(_treeView_dir, SIGNAL(expanded(QModelIndex &)), this, SLOT(treeviewExpanded(QModelIndex &)));
    connect(_treeView_dir, SIGNAL(folded(QModelIndex &)), this, SLOT(treeviewFolded(QModelIndex &)));
    connect(_treeView_dir, SIGNAL(clicked(QModelIndex &)), this, SLOT(treeviewClicked(QModelIndex &)));


    //qlistview
    QStandardItemModel *listmodel = new QStandardItemModel(ui->listView_files);
    listmodel->setHorizontalHeaderLabels(QStringList()<<"sel"<<"filename"<<"size");
    ui->listView_files->setModel(listmodel);
}




QString getFullPathByIndex(QModelIndex &index){
    //路径处理是一大难题，先用 /组合，然后再转成目标系统的路径
    QModelIndex i = index;
    QString path;
    while(i.isValid())
    {
        QString s = i.data().toString();
        path = QString("%1/%2").arg(s).arg(path);
        i = i.parent();
    }

    if(path.startsWith("/")){
        path = path.remove(0,1);
        //qDebug() << "driver: " << getDriver() + path;
    }
    path = QDir::toNativeSeparators(getDriver() + path);
    qDebug()<<  path;

    return path;
}


void DevManagerDialog::treeviewExpanded(QModelIndex &index){
    _logger->info("treeviewExpanded");

    QString path = getFullPathByIndex(index);
    QStandardItem *curItem = ((MyTreeModel*)_treeView_dir->model())->itemFromIndex(index);

    addChildItemsForTreeView(curItem, QDir(path));
}

void DevManagerDialog::treeviewFolded(QModelIndex &index){
    _logger->info("treeviewFolded");
}

void DevManagerDialog::treeviewClicked(QModelIndex &index){
    QString path = getFullPathByIndex(index);

    _logger->info("treeviewClicked:" + path);

    addTopItemsForListView((QStandardItemModel*)ui->listView_files->model(), QDir(path), true);

}



void DevManagerDialog::initResource(){
    m_publicIconMap[0] = QIcon(QStringLiteral(":/files/images/fold.png"));

    m_publicIconMap[1] = QIcon(QStringLiteral(":/files/images/music.png"));
    m_publicIconMap[2] = QIcon(QStringLiteral(":/files/images/video.png"));
    m_publicIconMap[3] = QIcon(QStringLiteral(":/files/images/image.png"));
    m_publicIconMap[4] = QIcon(QStringLiteral(":/files/images/file.png"));


    mExtMap.insert(".mp4", 2);mExtMap.insert(".flv", 2);mExtMap.insert(".wmv", 2);
    mExtMap.insert(".rmvb", 2);mExtMap.insert(".3gp", 2);mExtMap.insert(".mov", 2);

    mExtMap.insert(".mp3", 1);mExtMap.insert(".aac", 1);mExtMap.insert(".wma", 1);
    mExtMap.insert(".wav", 1);mExtMap.insert(".mid", 1);mExtMap.insert(".ogg", 1);

    mExtMap.insert(".jpg", 3);mExtMap.insert(".jpeg", 3);mExtMap.insert(".bmp", 3);
    mExtMap.insert(".png", 3);mExtMap.insert(".gif", 3);
}

void DevManagerDialog::addTopItemsForListView(QStandardItemModel *model, QDir dir, bool bchecked){
    model->removeRows(0, model->rowCount());

    dir.setFilter(QDir::Files );
    QFileInfoList list = dir.entryInfoList();
    int file_count = list.count();
    if(file_count <= 0)
    {
        return;
    }

    foreach(QFileInfo fi, list){
        QString filename = fi.fileName();
        QString ext = filename.right(filename.length()- filename.lastIndexOf(".")).toLower();

        int i = 0;
        QMap<QString,int>::iterator iter = mExtMap.find(ext);
        if(iter == mExtMap.end())
            i = 4;
        else
            i = iter.value();

        //添加子项
        QStandardItem* itemChild = new QStandardItem(
                    m_publicIconMap[i], fi.fileName());
        itemChild->setEditable(false);
        if(bchecked)
            itemChild->setCheckable(true);
         model->appendRow(itemChild);
        //以下作用同appendRow]
        //model->setItem(0,0,itemChild);
        //model->setItem(0,itemChild);
    }
    _treeView_dir->resizeColumnToContents (0);
}

void DevManagerDialog::addTopItemsForTreeView(QStandardItemModel *model, QDir dir, bool bchecked){
    model->removeRows(0, model->rowCount());

    dir.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
    QFileInfoList list = dir.entryInfoList();
    int file_count = list.count();
    if(file_count <= 0)
    {
        return;
    }

    foreach(QFileInfo fi, list){
        _logger->info(fi.fileName());

        //添加子项
        QStandardItem* itemChild = new QStandardItem(
                    m_publicIconMap[0], fi.fileName());
        itemChild->setEditable(false);
        if(bchecked)
            itemChild->setCheckable(true);
         model->appendRow(itemChild);
        //以下作用同appendRow]
        //model->setItem(0,0,itemChild);
        //model->setItem(0,itemChild);
    }
    _treeView_dir->resizeColumnToContents (0);
}

void DevManagerDialog::addChildItemsForTreeView(QStandardItem* parent, QDir dir, bool bchecked){
    parent->removeRows(0, parent->rowCount());

    dir.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
    QFileInfoList list = dir.entryInfoList();
    int file_count = list.count();
    if(file_count <= 0)
    {
        return;
    }

    foreach(QFileInfo fi, list){
        _logger->info(fi.fileName());

        //添加子项
        QStandardItem* itemChild = new QStandardItem(
                    m_publicIconMap[0], fi.fileName());
        itemChild->setEditable(false);
        if(bchecked)
            itemChild->setCheckable(true);

        parent->appendRow(itemChild);
        //setChild效果同上
        //item->setChild(0,itemChild);
    }

    _treeView_dir->resizeColumnToContents (0);
}




DevManagerDialog::~DevManagerDialog()
{
    delete ui;
}

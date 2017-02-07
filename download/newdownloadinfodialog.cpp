#include "download/newdownloadinfodialog.h"
#include "download/downloadsdbmanager.h"
#include<QString>
#include<QFileDialog>
#include <QSettings>
#include<QMessageBox>
#include "util/paths.h"

//设置url的一些下载属性
NewDownloadInfoDialog::NewDownloadInfoDialog(QWidget *parent, QString title, QString UrlInput) :
    QDialog(parent),
    ui(new Ui::NewDownloadInfoDialog)
{
    ui->setupUi(this);
    QString key = QStringLiteral("在线");

    int pos = title.lastIndexOf(key);
    title = title.left(title.length() - pos);

    ui->_lableTitle->setText(title);
    ui->pushButton_3->setHidden(true);

    _title = title;
    _url = UrlInput;
    //_path = Paths::devicePath(ui->categoryBox->currentText());
    _path = ui->categoryBox->currentText();

    qDebug() <<"NewDownloadInfoDialog: title="<< _title <<", url="<<_url<<", path=" <<_path;
}


NewDownloadInfoDialog::~NewDownloadInfoDialog()
{
    delete ui;
}



//设置保存路径，点击事件， 打开系统文件对话框，选中后更新 SaveToEdit控件的内容。
//void NewDownloadInfoDialog::on_browseSaveToButton_clicked() {
//    //browse to change Saveto
//    QFileDialog filedialog(this);
//    filedialog.setFileMode(filedialog.Directory);
//    QStringList seldir;
//    if(filedialog.exec())
//        seldir = filedialog.selectedFiles();
//    //ui->SaveToEdit->setText(seldir.first());
//}

//cancel
void NewDownloadInfoDialog::on_pushButton_4_clicked()
{
    this->destroy();
}

// 更新记录到, 先更新记录到model中,返回ID值(返回行号超级不靠谱)
qint64 NewDownloadInfoDialog::insertANewDownload(){
    //采集相关信息，更新这条记录到model中
    QFileInfo fileInfo(QUrl(_url).path());

    if(_title.isEmpty())
       _title = fileInfo.fileName();

    QString loc = _path;
    QString desc = "";
    int cat = ui->categoryBox->currentIndex();
    QString ref = "";
    int queue = 0;
    int pieces = 10;
    QString uuid = QUuid::createUuid().toString();
    qint64 ID = _model->insertDownload(_title, _url, loc,desc,cat,ref,queue,pieces,uuid);
    return ID;
}

//download later
void NewDownloadInfoDialog::on_pushButton_2_clicked()
{
    //download later
    insertANewDownload();
    this->destroy();
}

//分类事件-触发，更新-刷新界面路径信息
void NewDownloadInfoDialog::on_categoryBox_currentIndexChanged(int index)
{
    qDebug()<< ui->categoryBox->currentText();

//    QSettings settings;
//    switch(index){
//    case 0: ui->SaveToEdit->setText(settings.value("generalDirectory").toString());break;
//    case 1: ui->SaveToEdit->setText(settings.value("compressedDirectory").toString());break;
//    case 2: ui->SaveToEdit->setText(settings.value("documentDirectory").toString());break;
//    case 3: ui->SaveToEdit->setText(settings.value("musicDirectory").toString());break;
//    case 4: ui->SaveToEdit->setText(settings.value("programDirectory").toString());break;
//    case 5: ui->SaveToEdit->setText(settings.value("videoDirectory").toString());break;
//    }

    _path = ui->categoryBox->currentText();
}

void NewDownloadInfoDialog::setDownLoader(DownLoader *dl){
    mDownLoader = dl;
}

//download now
// 目前 下载功能没有实现
//所有下载的数据都是
void NewDownloadInfoDialog::on_pushButton_3_clicked()
{
    //先保存记录,返回插入行的ID值
    int ID = insertANewDownload();

    DownloadsDBManager* dm = _model->getDM();
    QString url = dm->getURL(ID);
    QString filename = dm->getFileName(ID);
    QString uuid = dm->getUuid(ID);
    qint64 size = dm->getSize(ID);


     mDownLoader->start(ID, url, uuid, filename, size);

    this->destroy();
}

void NewDownloadInfoDialog::setLocalModel(modelDownloads *model){
    _model = model;
}

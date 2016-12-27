#include "download/newdownloadinfodialog.h"
#include "download/downloadsdbmanager.h"
//#include "download/downloads.h"
#include<QString>
#include<QFileDialog>
#include <QSettings>
#include<QMessageBox>

//设置url的一些下载属性
NewDownloadInfoDialog::NewDownloadInfoDialog(QWidget *parent,QString UrlInput) :
    QDialog(parent),
    ui(new Ui::NewDownloadInfoDialog)
{
    ui->setupUi(this);
    ui->urlinput->setText(UrlInput);
    ui->descriptionEdit->setFocus();

    QSettings settings;
    switch(ui->categoryBox->currentIndex()){ //分类索引对应 保存路径。
    case 0: ui->SaveToEdit->setText(settings.value("generalDirectory").toString());break;
    case 1: ui->SaveToEdit->setText(settings.value("compressedDirectory").toString());break;
    case 2: ui->SaveToEdit->setText(settings.value("documentDirectory").toString());break;
    case 3: ui->SaveToEdit->setText(settings.value("musicDirectory").toString());break;
    case 4: ui->SaveToEdit->setText(settings.value("programDirectory").toString());break;
    case 5: ui->SaveToEdit->setText(settings.value("videoDirectory").toString());break;
    }
}


NewDownloadInfoDialog::~NewDownloadInfoDialog()
{
    delete ui;
}


//设置保存路径，点击事件， 打开系统文件对话框，选中后更新 SaveToEdit控件的内容。
void NewDownloadInfoDialog::on_browseSaveToButton_clicked() {
    //browse to change Saveto
    QFileDialog filedialog(this);
    filedialog.setFileMode(filedialog.Directory);
    QStringList seldir;
    if(filedialog.exec())
        seldir = filedialog.selectedFiles();
    ui->SaveToEdit->setText(seldir.first());
}

//cancel
void NewDownloadInfoDialog::on_pushButton_4_clicked()
{
    this->destroy();
}

// 更新记录到, 先更新记录到model中,返回行号
int NewDownloadInfoDialog::insertANewDownload(){
    //采集相关信息，更新这条记录到model中
    QString url = ui->urlinput->text();

    QFileInfo fileInfo(QUrl(url).path());
    QString filename = fileInfo.fileName();

    QString loc = ui->SaveToEdit->text();
    QString desc = ui->descriptionEdit->toPlainText();
    int cat = ui->categoryBox->currentIndex();
    QString ref = "";
    int queue = 0;
    int pieces = 10;
    QString uuid = QUuid::createUuid().toString();
    int newrow = localmodel->insertDownload(filename, url, loc,desc,cat,ref,queue,pieces,uuid);
    return newrow;
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
    QSettings settings;
    switch(index){
    case 0: ui->SaveToEdit->setText(settings.value("generalDirectory").toString());break;
    case 1: ui->SaveToEdit->setText(settings.value("compressedDirectory").toString());break;
    case 2: ui->SaveToEdit->setText(settings.value("documentDirectory").toString());break;
    case 3: ui->SaveToEdit->setText(settings.value("musicDirectory").toString());break;
    case 4: ui->SaveToEdit->setText(settings.value("programDirectory").toString());break;
    case 5: ui->SaveToEdit->setText(settings.value("videoDirectory").toString());break;
    }
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
    int newrow = insertANewDownload();
    if(newrow!=-1){
        //start download
//        QString filepath = ui->SaveToEdit->text();

//        Downloads *dl = new Downloads();
//        dl->SetupDownloadData(localmodel,newrow,filepath);
//        dl->StartDownload();
//        connect(dl,SIGNAL(completed(QString)),this,SLOT(ADownloadCompleted(QString)));
//        connect(dl,SIGNAL(updateinterface()),this,SLOT(UpdateInterface()));

          //数据获取也通过model
          int ID = localmodel->data(localmodel->index(newrow, 0)).toInt();
          QString url = localmodel->data(localmodel->index(newrow,2)).toString();
          QString filename = localmodel->data(localmodel->index(newrow, 1)).toString();
          QString uuid = localmodel->data(localmodel->index(newrow, 17)).toString();

//        Downloads *mManager = new Downloads(this);
//        connect(mManager,SIGNAL(downloadComplete()),this,SLOT(finished()));
//        connect(mManager,SIGNAL(progress(int)),this,SLOT(progress(int)));
//        mManager->startDownload(QUrl(url));

          mDownLoader->start(ID, url, uuid, filename);
    }

    this->destroy();
}

void NewDownloadInfoDialog::setLocalModel(modelDownloads *model){
    localmodel = model;
}

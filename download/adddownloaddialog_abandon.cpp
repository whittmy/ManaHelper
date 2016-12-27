#include "download/adddownloaddialog_abandon.h"
#include "download/ui_adddownloaddialog.h"
#include "download/newdownloadinfodialog.h"

AddDownloadDialog_abandon::AddDownloadDialog_abandon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDownloadDialog)
{
    ui->setupUi(this);
}

AddDownloadDialog_abandon::~AddDownloadDialog_abandon()
{
    delete ui;
}
void AddDownloadDialog_abandon::setUrl(QString url)
{
    ui->URLinput->setText(url);
}

// cancel
void AddDownloadDialog_abandon::on_pushButton_2_clicked()
{
    destroy(this); //释放窗口系统资源
}

// ok
void AddDownloadDialog_abandon::on_pushButton_clicked()
{
    //
    NewDownloadInfoDialog *newDownloadUi = new NewDownloadInfoDialog(this,ui->URLinput->text());
    newDownloadUi->show();
    newDownloadUi->setLocalModel(localmodel);
    newDownloadUi->setDownLoader(mDownLoader);
    destroy(this);
}


void AddDownloadDialog_abandon::setLocalModel(modelDownloads *model){
    localmodel = model;
}


void AddDownloadDialog_abandon::setDownLoader(DownLoader *dl){
    mDownLoader = dl;
}

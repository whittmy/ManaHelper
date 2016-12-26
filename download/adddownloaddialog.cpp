#include "download/adddownloaddialog.h"
#include "download/ui_adddownloaddialog.h"
#include "download/newdownloadinfodialog.h"

AddDownloadDialog::AddDownloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDownloadDialog)
{
    ui->setupUi(this);
}

AddDownloadDialog::~AddDownloadDialog()
{
    delete ui;
}
void AddDownloadDialog::setUrl(QString url)
{
    ui->URLinput->setText(url);
}

// cancel
void AddDownloadDialog::on_pushButton_2_clicked()
{
    destroy(this); //释放窗口系统资源
}

// ok
void AddDownloadDialog::on_pushButton_clicked()
{
    //
    NewDownloadInfoDialog *newDownloadUi = new NewDownloadInfoDialog(this,ui->URLinput->text());
    newDownloadUi->show();
    newDownloadUi->setLocalModel(localmodel);
    newDownloadUi->setDownLoader(mDownLoader);
    destroy(this);
}


void AddDownloadDialog::setLocalModel(modelDownloads *model){
    localmodel = model;
}


void AddDownloadDialog::setDownLoader(DownLoader *dl){
    mDownLoader = dl;
}

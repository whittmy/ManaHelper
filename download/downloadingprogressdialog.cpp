#include "downloadingprogressdialog.h"
#include "ui_downloadingprogressdialog.h"

DownloadingProgressDialog::DownloadingProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadingProgressDialog)
{
    ui->setupUi(this);
    mapper = new QDataWidgetMapper();

}

DownloadingProgressDialog::~DownloadingProgressDialog(){
    delete ui;
    this->close();
    this->destroy();
}

void DownloadingProgressDialog::setStatus(QString status){
    ui->statusLabel->setText(status);
}

void DownloadingProgressDialog::setFileSize(QString filesize){
    ui->fileSizeLabel->setText(filesize);
}

void DownloadingProgressDialog::setDownloaded(QString downloaded){
    ui->DownloadedAmountLabel->setText(downloaded);
}

void DownloadingProgressDialog::setSpeed(QString speed){
    ui->TransferRateLabel->setText(speed);
}

void DownloadingProgressDialog::setTimeleft(QString timeleft){
    ui->TmeLeftLabel->setText(timeleft);
}

void DownloadingProgressDialog::updateProgressBar(int value){
    ui->progressBar->setValue(value);
}

void DownloadingProgressDialog::updateAll(QString status,QString filesize,QString downloaded,QString speed,QString timeleft){
    ui->statusLabel->setText(status);
    ui->fileSizeLabel->setText(filesize);
    ui->DownloadedAmountLabel->setText(downloaded);
    ui->TransferRateLabel->setText(speed);
    ui->TmeLeftLabel->setText(timeleft);
}

void DownloadingProgressDialog::setLocalModel(modelDownloads *model){
    localmodel = model;
    mapper->setModel(localmodel);
    mapper->setOrientation(Qt::Horizontal);
    mapper->setSubmitPolicy(mapper->ManualSubmit);
    mapper->addMapping(ui->DownloadUrlLabel,2,"text");
    mapper->addMapping(ui->fileSizeLabel,5,"text");
    mapper->addMapping(ui->TransferRateLabel,9,"text");
    mapper->addMapping(ui->TmeLeftLabel,8,"text");
}

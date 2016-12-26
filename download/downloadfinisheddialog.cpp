#include "downloadfinisheddialog.h"
#include "ui_downloadfinisheddialog.h"

DownloadFinishedDialog::DownloadFinishedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadFinishedDialog)
{
    ui->setupUi(this);
}

DownloadFinishedDialog::~DownloadFinishedDialog()
{
    delete ui;
}

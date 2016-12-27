#include "ui_downloadpropertydialog.h"
#include "download/downloadpropertydialog.h"

#include <QDataWidgetMapper>
DownloadPropertyDialog::DownloadPropertyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadPropertyDialog)
{
    ui->setupUi(this);
    mapper = new QDataWidgetMapper();
}

DownloadPropertyDialog::~DownloadPropertyDialog()
{
    delete ui;
}

void DownloadPropertyDialog::setLocalModel(modelDownloads *model){
    localmodel = model;
    mapper->setModel(localmodel);
    mapper->setOrientation(Qt::Horizontal);
    mapper->setSubmitPolicy(mapper->ManualSubmit);
    mapper->addMapping(ui->filenamelabel, 1,"text");
    mapper->addMapping(ui->statuslabel, 7,"text");
    mapper->addMapping(ui->sizelabel, 5,"text");
    mapper->addMapping(ui->savedtolabel, 12,"text");
    mapper->addMapping(ui->urledit, 2);
    mapper->addMapping(ui->descedit, 11);
    mapper->addMapping(ui->refererEdit, 13);
    mapper->addMapping(ui->lastTryDateLabel, 10,"text");
    mapper->addMapping(ui->dateAddedLabel, 3,"text");
}

void DownloadPropertyDialog::setIndex(int index){
    mapper->setCurrentIndex(index);
}

void DownloadPropertyDialog::on_pushButton_2_clicked()
{
//ok
    accept();
}

void DownloadPropertyDialog::on_pushButton_clicked()
{
    //open
}

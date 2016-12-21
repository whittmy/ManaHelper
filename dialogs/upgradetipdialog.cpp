﻿#include "upgradetipdialog.h"
#include "ui_upgradetipdialog.h"

#pragma comment(lib,"Qt5Widgets.lib")
#pragma comment(lib,"Qt5WebKitWidgets.lib")


UpgradeTipDialog::UpgradeTipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpgradeTipDialog),_logger(new LogMe(this))
{
    ui->setupUi(this);

    // 禁止改变窗口大小。
    setFixedSize(this->geometry().size());

    _dp = NULL;
    ui->_progBar->setVisible(false);

    mNetMgr = new QNetworkAccessManager(this);
    mReply = NULL;
}

UpgradeTipDialog::~UpgradeTipDialog()
{
    if(_dp != NULL)
        delete _dp;

    delete mNetMgr;
    delete ui;
}

//既然设置都是合法的
void UpgradeTipDialog::setData(REQ_TYPE type, Xml_Parser_Upgrade *dp){
    _dp = dp; mType = type;

    QString intro = _dp->getDescription();
    int pos =  intro.indexOf("\n");
    QString ver  =  intro.left(pos-1);
    intro =  intro.right(intro.length()-pos-1);

    ui->_webView->setHtml(intro);




    ui->_webView->setContextMenuPolicy(Qt::NoContextMenu); //禁止右键
}


void UpgradeTipDialog::on__btnUpgrade_clicked(){
    _logger->info("-- on__btnUpgrade_clicked --");

    ui->_progBar->setVisible(true);
    ui->_progBar->setValue(0);


    QNetworkRequest request(QUrl(_dp->getUrl()));
    mReply =  mNetMgr->get(request);

    connect(mReply, SIGNAL(finished()), this, SLOT(dl_finished()));
    connect(mReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(dl_progress(qint64,qint64)));
    connect(mReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(dl_error(QNetworkReply::NetworkError)));
    connect(mReply, SIGNAL(readyRead()), this, SLOT(dl_readReady(QNetworkReply*)));
}

void UpgradeTipDialog::dl_readReady(QNetworkReply* reply){
    _logger->info("dl_readReady----");

    //读取数据
    reply->readAll();
}

void UpgradeTipDialog::dl_finished(){
    _logger->info("--dl_finished--");
    if(ui->_progBar->value() == 100){
        //finished!!

        //拷贝到设备根目录下

        //载入操作提示
        ui->_webView->load(QUrl("qrc:///other/html/devupgrade.html"));


    }
}

void UpgradeTipDialog::dl_progress(qint64 recv, qint64 total){
   // _logger->info(QString("%1,%2").arg(recv).arg(total));

    int p = 0;
    if(total >= 0){
        p = (recv/(total*1.0)) * 100;
    }
    //_logger->info(QString("%1").arg(p));
    ui->_progBar->setValue(p);
}

void UpgradeTipDialog::dl_error(QNetworkReply::NetworkError err){

}


void UpgradeTipDialog::on__btnCancel_clicked(){
    _logger->info("-- on__btnCancel_clicked--");

    if(mReply != NULL && mReply->isOpen())
        mReply->abort();

    close();
}

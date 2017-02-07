#include "welcomedialog.h"
#include "ui_welcomedialog.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include "storethread.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);

    mSt = new StoreThread;
    connect(mSt, SIGNAL(sig_storerlst(StoreThread*)), this, SLOT(slotStored(StoreThread*)));

    //_tip
    setWindowTitle(tr("Welcome"));
    ui->_tip->setText(tr("Initing"));
}

void WelcomeDialog::slotStored(StoreThread *t){
    if(t == NULL)
        return;
    if(t->bComplete()){

    }
    else{

    }

    delete t;
}

bool WelcomeDialog::detectElem(){
    QString ffmpeg = "C:\\Windows\\ffmpeg.exe";
    if(!QFile::exists(ffmpeg)){
        //QFile::copy(":/bin/bin/ffmpeg.exe", ffmpeg);

        mSt->setCopyInfo(-1, ":/bin/bin/ffmpeg.exe", ffmpeg);
        mSt->start();
    }
    return true;
}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}

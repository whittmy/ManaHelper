#include "systemtrayicon.h"
#include <QTimer>
SystemTrayIcon::SystemTrayIcon(QObject *parent) :
    QSystemTrayIcon(parent)
{
    this->setParent(parent);
    defaulticon=0;
    blinking = false;
    //this->setVisible(false);
    this->hide();
    //this->showMessage("Welcome to Download Manager","This is a nice download manager",QSystemTrayIcon::Information,5000);
}

SystemTrayIcon::~SystemTrayIcon(){
    //this->deleteLater();
    this->setVisible(false);
}

int SystemTrayIcon::setBlink(bool status){
    if(status){
        blinktimer = new QTimer();
        connect(blinktimer,SIGNAL(timeout()),this,SLOT(blinkicon()));
        blinktimer->start(1000);
        blinking = true;
    }else {
        blinktimer->stop();
        blinking = false;
    }
    return 0;
}

int SystemTrayIcon::blinkicon(){
    if(defaulticon==0){
        setIcon(QIcon(":/icons/images/icon.png"));
        defaulticon=1;
    }else{
        setIcon(QIcon(":/icons/images/blinkicon.png"));
        defaulticon=0;
    }
    return 0;
}

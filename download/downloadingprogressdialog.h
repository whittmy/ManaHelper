#ifndef DOWNLOADINGPROGRESSDIALOG_H
#define DOWNLOADINGPROGRESSDIALOG_H

#include <QDialog>
#include "download/modeldownloads.h"
#include <QDataWidgetMapper>
namespace Ui {
class DownloadingProgressDialog;
}

class DownloadingProgressDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DownloadingProgressDialog(QWidget *parent = 0);
    ~DownloadingProgressDialog();
    void setStatus(QString status);
    void setFileSize(QString filesize);
    void setDownloaded(QString downloaded);
    void setSpeed(QString speed);
    void setTimeleft(QString timeleft);
    void updateProgressBar(int value);
    void updateAll(QString status,QString filesize,QString downloaded,QString speed,QString timeleft);
    modelDownloads *localmodel;
    void setLocalModel(modelDownloads *);
    QDataWidgetMapper *mapper;

private:
    Ui::DownloadingProgressDialog *ui;
};

#endif // DOWNLOADINGPROGRESSDIALOG_H

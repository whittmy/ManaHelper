#ifndef ADDDOWNLOADDIALOG_H
#define ADDDOWNLOADDIALOG_H

#include <QDialog>
#include <download/modeldownloads.h>
#include "download/downloadsdbmanager.h"
#include "download/downloader.h"


namespace Ui {
class AddDownloadDialog;
}

class AddDownloadDialog_abandon : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddDownloadDialog_abandon(QWidget *parent = 0);
    ~AddDownloadDialog_abandon();
    void setUrl(QString url);
    void setLocalModel(modelDownloads *);
    void setDownLoader(DownLoader *dl);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::AddDownloadDialog *ui;

    modelDownloads *localmodel;
    DownLoader *mDownLoader;

};

#endif // ADDDOWNLOADDIALOG_H

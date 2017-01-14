#ifndef NEWDOWNLOADINFODIALOG_H
#define NEWDOWNLOADINFODIALOG_H
#include "ui_newdownloadinfodialog.h"

#include <QDialog>
#include <download/modeldownloads.h>
#include "download/downloadsdbmanager.h"
#include "download/downloader.h"


namespace Ui {
class NewDownloadInfoDialog;
}

class NewDownloadInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewDownloadInfoDialog(QWidget *parent = 0, QString text="", QString UrlInput="");
    ~NewDownloadInfoDialog();
    void setLocalModel(modelDownloads *);
    modelDownloads *_model;
    void setDownLoader(DownLoader *dl);
private slots:
    //void on_browseSaveToButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_categoryBox_currentIndexChanged(int index);
    void on_pushButton_3_clicked();
    int insertANewDownload();


private:
    Ui::NewDownloadInfoDialog *ui;
    QString _url, _title, _path;
    DownLoader *mDownLoader;
};

#endif // NEWDOWNLOADINFODIALOG_H

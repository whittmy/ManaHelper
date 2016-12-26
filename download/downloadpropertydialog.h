#ifndef DOWNLOADPROPERTYDIALOG_H
#define DOWNLOADPROPERTYDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
#include "download/modeldownloads.h"
namespace Ui {
class DownloadPropertyDialog;
}

class DownloadPropertyDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DownloadPropertyDialog(QWidget *parent = 0);
    ~DownloadPropertyDialog();
    modelDownloads *localmodel;
    void setLocalModel(modelDownloads *);
    QDataWidgetMapper *mapper;
    void setIndex(int index);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::DownloadPropertyDialog *ui;
};

#endif // DOWNLOADPROPERTYDIALOG_H

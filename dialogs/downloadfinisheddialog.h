#ifndef DOWNLOADFINISHEDDIALOG_H
#define DOWNLOADFINISHEDDIALOG_H

#include <QDialog>

namespace Ui {
class DownloadFinishedDialog;
}

class DownloadFinishedDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DownloadFinishedDialog(QWidget *parent = 0);
    ~DownloadFinishedDialog();
    
private:
    Ui::DownloadFinishedDialog *ui;
};

#endif // DOWNLOADFINISHEDDIALOG_H

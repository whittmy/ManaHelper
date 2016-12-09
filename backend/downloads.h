#ifndef DOWNLOADS_H
#define DOWNLOADS_H

#include <QObject>
#include "backend/modeldownloads.h"
#include "dialogs/downloadingprogressdialog.h"
#include "QtCore"

class Downloads : public QObject
{
    Q_OBJECT
public:
    explicit Downloads(QObject *parent = 0);
    DownloadingProgressDialog *dpd;//constructor init
    modelDownloads *localmodel;//from the calling function
    QModelIndex *mIndex;//from the calling function
    void setup(modelDownloads *mod,QModelIndex *mi);
    void updateModel();
    //void updateDialog();
signals:
    
public slots:
    
};

#endif // DOWNLOADS_H

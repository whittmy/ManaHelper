#ifndef DEVMANAGERDIALOG_H
#define DEVMANAGERDIALOG_H

#include <QDialog>
#include "backend/logme.h"
#include <QDir>
#include <QStandardItem>
#include <QMap>
#include "util/mytreeview.h"

namespace Ui {
class DevManagerDialog;
}

class DevManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DevManagerDialog(QWidget *parent = 0);
    ~DevManagerDialog();

    void addTopItemsForListView(QStandardItemModel *model, QDir dir, bool bchecked);
    void addTopItemsForTreeView(QStandardItemModel *model, QDir dir, bool bchecked=false);
    void addChildItemsForTreeView(QStandardItem *item, QDir dir, bool bchecked=false);
    void initResource();


private slots:
    void treeviewExpanded(QModelIndex &index);
    void treeviewFolded(QModelIndex &index);
    void treeviewClicked(QModelIndex &index);

private:
    Ui::DevManagerDialog *ui;
    QMap<QString, QIcon> m_publicIconMap ;
    LogMe *_logger;
    MyTreeView *_treeView_dir;
};

#endif // DEVMANAGERDIALOG_H

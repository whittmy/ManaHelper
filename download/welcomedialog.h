#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>
#include "storethread.h"

namespace Ui {
class WelcomeDialog;
}

class WelcomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeDialog(QWidget *parent = 0);
    ~WelcomeDialog();
    bool detectElem();

private slots:
    void slotStored(StoreThread *t);

private:

private:
    Ui::WelcomeDialog *ui;
    StoreThread *mSt;
};

#endif // WELCOMEDIALOG_H

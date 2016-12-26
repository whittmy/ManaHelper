/********************************************************************************
** Form generated from reading UI file 'downloadfinisheddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADFINISHEDDIALOG_H
#define UI_DOWNLOADFINISHEDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DownloadFinishedDialog
{
public:

    void setupUi(QDialog *DownloadFinishedDialog)
    {
        if (DownloadFinishedDialog->objectName().isEmpty())
            DownloadFinishedDialog->setObjectName(QStringLiteral("DownloadFinishedDialog"));
        DownloadFinishedDialog->resize(620, 161);

        retranslateUi(DownloadFinishedDialog);

        QMetaObject::connectSlotsByName(DownloadFinishedDialog);
    } // setupUi

    void retranslateUi(QDialog *DownloadFinishedDialog)
    {
        DownloadFinishedDialog->setWindowTitle(QApplication::translate("DownloadFinishedDialog", "Download Finished", 0));
    } // retranslateUi

};

namespace Ui {
    class DownloadFinishedDialog: public Ui_DownloadFinishedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADFINISHEDDIALOG_H

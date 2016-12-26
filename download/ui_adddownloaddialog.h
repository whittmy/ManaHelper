/********************************************************************************
** Form generated from reading UI file 'adddownloaddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDOWNLOADDIALOG_H
#define UI_ADDDOWNLOADDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddDownloadDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *URLinput;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *AddDownloadDialog)
    {
        if (AddDownloadDialog->objectName().isEmpty())
            AddDownloadDialog->setObjectName(QStringLiteral("AddDownloadDialog"));
        AddDownloadDialog->setWindowModality(Qt::WindowModal);
        AddDownloadDialog->resize(525, 86);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddDownloadDialog->sizePolicy().hasHeightForWidth());
        AddDownloadDialog->setSizePolicy(sizePolicy);
        AddDownloadDialog->setFocusPolicy(Qt::TabFocus);
        layoutWidget = new QWidget(AddDownloadDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 10, 504, 64));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        URLinput = new QLineEdit(layoutWidget);
        URLinput->setObjectName(QStringLiteral("URLinput"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(URLinput->sizePolicy().hasHeightForWidth());
        URLinput->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(URLinput);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(318, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_2);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(URLinput);
#endif // QT_NO_SHORTCUT

        retranslateUi(AddDownloadDialog);

        QMetaObject::connectSlotsByName(AddDownloadDialog);
    } // setupUi

    void retranslateUi(QDialog *AddDownloadDialog)
    {
        AddDownloadDialog->setWindowTitle(QApplication::translate("AddDownloadDialog", "Enter New URL to Download", 0));
        label->setText(QApplication::translate("AddDownloadDialog", "URL", 0));
        pushButton->setText(QApplication::translate("AddDownloadDialog", "OK", 0));
        pushButton_2->setText(QApplication::translate("AddDownloadDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class AddDownloadDialog: public Ui_AddDownloadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDOWNLOADDIALOG_H

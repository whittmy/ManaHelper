/********************************************************************************
** Form generated from reading UI file 'newdownloadinfodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWDOWNLOADINFODIALOG_H
#define UI_NEWDOWNLOADINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewDownloadInfoDialog
{
public:
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *urlinput;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *categoryBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *SaveToEdit;
    QPushButton *browseSaveToButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QPlainTextEdit *descriptionEdit;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QDialog *NewDownloadInfoDialog)
    {
        if (NewDownloadInfoDialog->objectName().isEmpty())
            NewDownloadInfoDialog->setObjectName(QStringLiteral("NewDownloadInfoDialog"));
        NewDownloadInfoDialog->resize(587, 189);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewDownloadInfoDialog->sizePolicy().hasHeightForWidth());
        NewDownloadInfoDialog->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(NewDownloadInfoDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(NewDownloadInfoDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(24, 27));
        label->setMaximumSize(QSize(24, 27));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label, 0, Qt::AlignLeft);

        horizontalSpacer_2 = new QSpacerItem(32, 0, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        urlinput = new QLineEdit(NewDownloadInfoDialog);
        urlinput->setObjectName(QStringLiteral("urlinput"));

        horizontalLayout->addWidget(urlinput);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(NewDownloadInfoDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(50, 25));
        label_2->setMaximumSize(QSize(50, 25));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2, 0, Qt::AlignLeft|Qt::AlignVCenter);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        categoryBox = new QComboBox(NewDownloadInfoDialog);
        QIcon icon;
        icon.addFile(QStringLiteral(":/categories/images/prio_0.png"), QSize(), QIcon::Normal, QIcon::Off);
        categoryBox->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/categories/images/archive.png"), QSize(), QIcon::Normal, QIcon::Off);
        categoryBox->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/categories/images/document.png"), QSize(), QIcon::Normal, QIcon::Off);
        categoryBox->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/categories/images/audio.png"), QSize(), QIcon::Normal, QIcon::Off);
        categoryBox->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/categories/images/downloadmanagment.png"), QSize(), QIcon::Normal, QIcon::Off);
        categoryBox->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/categories/images/video.png"), QSize(), QIcon::Normal, QIcon::Off);
        categoryBox->addItem(icon5, QString());
        categoryBox->setObjectName(QStringLiteral("categoryBox"));
        categoryBox->setMinimumSize(QSize(71, 27));
        categoryBox->setMaximumSize(QSize(132, 27));

        horizontalLayout_2->addWidget(categoryBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(NewDownloadInfoDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(62, 27));
        label_3->setMaximumSize(QSize(42, 27));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3, 0, Qt::AlignLeft);

        SaveToEdit = new QLineEdit(NewDownloadInfoDialog);
        SaveToEdit->setObjectName(QStringLiteral("SaveToEdit"));
        SaveToEdit->setEnabled(false);

        horizontalLayout_3->addWidget(SaveToEdit);

        browseSaveToButton = new QPushButton(NewDownloadInfoDialog);
        browseSaveToButton->setObjectName(QStringLiteral("browseSaveToButton"));
        browseSaveToButton->setMinimumSize(QSize(85, 27));
        browseSaveToButton->setMaximumSize(QSize(85, 27));

        horizontalLayout_3->addWidget(browseSaveToButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(NewDownloadInfoDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(63, 0));
        label_4->setMaximumSize(QSize(63, 28));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_4);

        descriptionEdit = new QPlainTextEdit(NewDownloadInfoDialog);
        descriptionEdit->setObjectName(QStringLiteral("descriptionEdit"));
        descriptionEdit->setMinimumSize(QSize(488, 27));
        descriptionEdit->setMaximumSize(QSize(488, 27));
        descriptionEdit->setTabChangesFocus(true);

        horizontalLayout_4->addWidget(descriptionEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pushButton_2 = new QPushButton(NewDownloadInfoDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_5->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(NewDownloadInfoDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_5->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(NewDownloadInfoDialog);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_5->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_5);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(urlinput);
        label_2->setBuddy(categoryBox);
        label_3->setBuddy(SaveToEdit);
        label_4->setBuddy(descriptionEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(NewDownloadInfoDialog);

        QMetaObject::connectSlotsByName(NewDownloadInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *NewDownloadInfoDialog)
    {
        NewDownloadInfoDialog->setWindowTitle(QApplication::translate("NewDownloadInfoDialog", "New Download", 0));
        label->setText(QApplication::translate("NewDownloadInfoDialog", "URL", 0));
        label_2->setText(QApplication::translate("NewDownloadInfoDialog", "Category", 0));
        categoryBox->setItemText(0, QApplication::translate("NewDownloadInfoDialog", "General", 0));
        categoryBox->setItemText(1, QApplication::translate("NewDownloadInfoDialog", "Compressed", 0));
        categoryBox->setItemText(2, QApplication::translate("NewDownloadInfoDialog", "Documents", 0));
        categoryBox->setItemText(3, QApplication::translate("NewDownloadInfoDialog", "Music", 0));
        categoryBox->setItemText(4, QApplication::translate("NewDownloadInfoDialog", "Programs", 0));
        categoryBox->setItemText(5, QApplication::translate("NewDownloadInfoDialog", "Video", 0));

        label_3->setText(QApplication::translate("NewDownloadInfoDialog", "Save As", 0));
        browseSaveToButton->setText(QApplication::translate("NewDownloadInfoDialog", "...", 0));
        label_4->setText(QApplication::translate("NewDownloadInfoDialog", "Description", 0));
        pushButton_2->setText(QApplication::translate("NewDownloadInfoDialog", "Download Later", 0));
        pushButton_3->setText(QApplication::translate("NewDownloadInfoDialog", "Start Download", 0));
        pushButton_4->setText(QApplication::translate("NewDownloadInfoDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class NewDownloadInfoDialog: public Ui_NewDownloadInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWDOWNLOADINFODIALOG_H

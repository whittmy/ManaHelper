/********************************************************************************
** Form generated from reading UI file 'downloadpropertydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADPROPERTYDIALOG_H
#define UI_DOWNLOADPROPERTYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DownloadPropertyDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *image_ext;
    QSpacerItem *horizontalSpacer;
    QLabel *filenamelabel;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *statuslabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *sizelabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *savedtolabel;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *urledit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *descedit;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *refererEdit;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_8;
    QLabel *lastTryDateLabel;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_9;
    QLabel *dateAddedLabel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *DownloadPropertyDialog)
    {
        if (DownloadPropertyDialog->objectName().isEmpty())
            DownloadPropertyDialog->setObjectName(QStringLiteral("DownloadPropertyDialog"));
        DownloadPropertyDialog->setWindowModality(Qt::WindowModal);
        DownloadPropertyDialog->resize(495, 388);
        layoutWidget = new QWidget(DownloadPropertyDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 479, 311));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        image_ext = new QLabel(layoutWidget);
        image_ext->setObjectName(QStringLiteral("image_ext"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(image_ext->sizePolicy().hasHeightForWidth());
        image_ext->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(image_ext);

        horizontalSpacer = new QSpacerItem(45, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        filenamelabel = new QLabel(layoutWidget);
        filenamelabel->setObjectName(QStringLiteral("filenamelabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(filenamelabel->sizePolicy().hasHeightForWidth());
        filenamelabel->setSizePolicy(sizePolicy1);
        filenamelabel->setMinimumSize(QSize(325, 0));

        horizontalLayout->addWidget(filenamelabel);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(layoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        statuslabel = new QLabel(layoutWidget);
        statuslabel->setObjectName(QStringLiteral("statuslabel"));
        sizePolicy1.setHeightForWidth(statuslabel->sizePolicy().hasHeightForWidth());
        statuslabel->setSizePolicy(sizePolicy1);
        statuslabel->setMinimumSize(QSize(325, 0));

        horizontalLayout_2->addWidget(statuslabel);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        sizelabel = new QLabel(layoutWidget);
        sizelabel->setObjectName(QStringLiteral("sizelabel"));
        sizelabel->setMinimumSize(QSize(325, 0));

        horizontalLayout_3->addWidget(sizelabel);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_5);

        horizontalSpacer_4 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        savedtolabel = new QLabel(layoutWidget);
        savedtolabel->setObjectName(QStringLiteral("savedtolabel"));
        savedtolabel->setMinimumSize(QSize(325, 0));

        horizontalLayout_4->addWidget(savedtolabel);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_5->addWidget(label_6);

        horizontalSpacer_5 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        urledit = new QLineEdit(layoutWidget);
        urledit->setObjectName(QStringLiteral("urledit"));

        horizontalLayout_5->addWidget(urledit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label_7);

        horizontalSpacer_6 = new QSpacerItem(12, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        descedit = new QLineEdit(layoutWidget);
        descedit->setObjectName(QStringLiteral("descedit"));

        horizontalLayout_6->addWidget(descedit);


        verticalLayout->addLayout(horizontalLayout_6);

        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(label_8);

        horizontalSpacer_7 = new QSpacerItem(33, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        refererEdit = new QLineEdit(layoutWidget);
        refererEdit->setObjectName(QStringLiteral("refererEdit"));

        horizontalLayout_7->addWidget(refererEdit);


        verticalLayout->addLayout(horizontalLayout_7);

        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(label_10);

        horizontalSpacer_8 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        lastTryDateLabel = new QLabel(layoutWidget);
        lastTryDateLabel->setObjectName(QStringLiteral("lastTryDateLabel"));
        lastTryDateLabel->setMinimumSize(QSize(325, 0));

        horizontalLayout_8->addWidget(lastTryDateLabel);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy2);
        label_11->setMinimumSize(QSize(88, 23));

        horizontalLayout_9->addWidget(label_11);

        horizontalSpacer_9 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        dateAddedLabel = new QLabel(layoutWidget);
        dateAddedLabel->setObjectName(QStringLiteral("dateAddedLabel"));
        dateAddedLabel->setMinimumSize(QSize(325, 0));

        horizontalLayout_9->addWidget(dateAddedLabel);


        verticalLayout->addLayout(horizontalLayout_9);

        layoutWidget1 = new QWidget(DownloadPropertyDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 340, 481, 29));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_10 = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_10->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_10->addWidget(pushButton_2);

#ifndef QT_NO_SHORTCUT
        label_6->setBuddy(urledit);
        label_7->setBuddy(descedit);
        label_8->setBuddy(refererEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(DownloadPropertyDialog);

        QMetaObject::connectSlotsByName(DownloadPropertyDialog);
    } // setupUi

    void retranslateUi(QDialog *DownloadPropertyDialog)
    {
        DownloadPropertyDialog->setWindowTitle(QApplication::translate("DownloadPropertyDialog", "Download Properties", 0));
        image_ext->setText(QApplication::translate("DownloadPropertyDialog", "Image", 0));
        filenamelabel->setText(QString());
        label_3->setText(QApplication::translate("DownloadPropertyDialog", "Status", 0));
        statuslabel->setText(QString());
        label_4->setText(QApplication::translate("DownloadPropertyDialog", "Size", 0));
        sizelabel->setText(QString());
        label_5->setText(QApplication::translate("DownloadPropertyDialog", "Saved to", 0));
        savedtolabel->setText(QString());
        label_6->setText(QApplication::translate("DownloadPropertyDialog", "URL", 0));
        label_7->setText(QApplication::translate("DownloadPropertyDialog", "Description", 0));
        label_8->setText(QApplication::translate("DownloadPropertyDialog", "Referer", 0));
        label_10->setText(QApplication::translate("DownloadPropertyDialog", "Last Try Date", 0));
        lastTryDateLabel->setText(QString());
        label_11->setText(QApplication::translate("DownloadPropertyDialog", "Date Added", 0));
        dateAddedLabel->setText(QApplication::translate("DownloadPropertyDialog", "s", 0));
        pushButton->setText(QApplication::translate("DownloadPropertyDialog", "Open", 0));
        pushButton_2->setText(QApplication::translate("DownloadPropertyDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class DownloadPropertyDialog: public Ui_DownloadPropertyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADPROPERTYDIALOG_H

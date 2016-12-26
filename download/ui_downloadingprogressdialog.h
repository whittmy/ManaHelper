/********************************************************************************
** Form generated from reading UI file 'downloadingprogressdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADINGPROGRESSDIALOG_H
#define UI_DOWNLOADINGPROGRESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DownloadingProgressDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *downloadStatusTab;
    QLabel *DownloadUrlLabel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *TransferRateLabel;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_5;
    QLabel *TmeLeftLabel;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_6;
    QLabel *ResumeCapabilityLabel;
    QProgressBar *progressBar;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *statusLabel;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *fileSizeLabel;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *DownloadedAmountLabel;
    QLabel *DownloadedSizeUnitLabel;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *PauseStartButton;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *CancelButton;

    void setupUi(QDialog *DownloadingProgressDialog)
    {
        if (DownloadingProgressDialog->objectName().isEmpty())
            DownloadingProgressDialog->setObjectName(QStringLiteral("DownloadingProgressDialog"));
        DownloadingProgressDialog->resize(599, 317);
        layoutWidget = new QWidget(DownloadingProgressDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 581, 311));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(layoutWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        downloadStatusTab = new QWidget();
        downloadStatusTab->setObjectName(QStringLiteral("downloadStatusTab"));
        DownloadUrlLabel = new QLabel(downloadStatusTab);
        DownloadUrlLabel->setObjectName(QStringLiteral("DownloadUrlLabel"));
        DownloadUrlLabel->setGeometry(QRect(10, 10, 581, 21));
        DownloadUrlLabel->setMinimumSize(QSize(581, 21));
        DownloadUrlLabel->setMaximumSize(QSize(581, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferDefault);
        DownloadUrlLabel->setFont(font);
        layoutWidget1 = new QWidget(downloadStatusTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 130, 571, 22));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_5);

        horizontalSpacer_4 = new QSpacerItem(42, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        TransferRateLabel = new QLabel(layoutWidget1);
        TransferRateLabel->setObjectName(QStringLiteral("TransferRateLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TransferRateLabel->sizePolicy().hasHeightForWidth());
        TransferRateLabel->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(TransferRateLabel);

        layoutWidget_2 = new QWidget(downloadStatusTab);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 160, 571, 22));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_6);

        horizontalSpacer_5 = new QSpacerItem(64, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        TmeLeftLabel = new QLabel(layoutWidget_2);
        TmeLeftLabel->setObjectName(QStringLiteral("TmeLeftLabel"));
        sizePolicy1.setHeightForWidth(TmeLeftLabel->sizePolicy().hasHeightForWidth());
        TmeLeftLabel->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(TmeLeftLabel);

        layoutWidget_3 = new QWidget(downloadStatusTab);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 190, 571, 22));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label_7);

        horizontalSpacer_6 = new QSpacerItem(15, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        ResumeCapabilityLabel = new QLabel(layoutWidget_3);
        ResumeCapabilityLabel->setObjectName(QStringLiteral("ResumeCapabilityLabel"));
        sizePolicy1.setHeightForWidth(ResumeCapabilityLabel->sizePolicy().hasHeightForWidth());
        ResumeCapabilityLabel->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(ResumeCapabilityLabel);

        progressBar = new QProgressBar(downloadStatusTab);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 220, 568, 23));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy2);
        progressBar->setMinimumSize(QSize(500, 23));
        progressBar->setMaximumSize(QSize(568, 23));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setInvertedAppearance(false);
        layoutWidget2 = new QWidget(downloadStatusTab);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 40, 570, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(81, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        statusLabel = new QLabel(layoutWidget2);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        sizePolicy1.setHeightForWidth(statusLabel->sizePolicy().hasHeightForWidth());
        statusLabel->setSizePolicy(sizePolicy1);
        statusLabel->setMinimumSize(QSize(300, 16));
        statusLabel->setMaximumSize(QSize(521, 16));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        statusLabel->setFont(font1);
        statusLabel->setFrameShape(QFrame::NoFrame);
        statusLabel->setFrameShadow(QFrame::Plain);

        horizontalLayout->addWidget(statusLabel);

        layoutWidget3 = new QWidget(downloadStatusTab);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 70, 571, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget3);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(72, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        fileSizeLabel = new QLabel(layoutWidget3);
        fileSizeLabel->setObjectName(QStringLiteral("fileSizeLabel"));
        sizePolicy1.setHeightForWidth(fileSizeLabel->sizePolicy().hasHeightForWidth());
        fileSizeLabel->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(fileSizeLabel);

        layoutWidget4 = new QWidget(downloadStatusTab);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 100, 571, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(46, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        DownloadedAmountLabel = new QLabel(layoutWidget4);
        DownloadedAmountLabel->setObjectName(QStringLiteral("DownloadedAmountLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(DownloadedAmountLabel->sizePolicy().hasHeightForWidth());
        DownloadedAmountLabel->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(DownloadedAmountLabel);

        DownloadedSizeUnitLabel = new QLabel(layoutWidget4);
        DownloadedSizeUnitLabel->setObjectName(QStringLiteral("DownloadedSizeUnitLabel"));
        sizePolicy1.setHeightForWidth(DownloadedSizeUnitLabel->sizePolicy().hasHeightForWidth());
        DownloadedSizeUnitLabel->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(DownloadedSizeUnitLabel);

        tabWidget->addTab(downloadStatusTab, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_7 = new QSpacerItem(308, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        PauseStartButton = new QPushButton(layoutWidget);
        PauseStartButton->setObjectName(QStringLiteral("PauseStartButton"));

        horizontalLayout_7->addWidget(PauseStartButton);

        horizontalSpacer_8 = new QSpacerItem(30, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);

        CancelButton = new QPushButton(layoutWidget);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        horizontalLayout_7->addWidget(CancelButton);


        verticalLayout->addLayout(horizontalLayout_7);


        retranslateUi(DownloadingProgressDialog);
        QObject::connect(CancelButton, SIGNAL(clicked()), DownloadingProgressDialog, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DownloadingProgressDialog);
    } // setupUi

    void retranslateUi(QDialog *DownloadingProgressDialog)
    {
        DownloadingProgressDialog->setWindowTitle(QApplication::translate("DownloadingProgressDialog", "Downloading..", 0));
#ifndef QT_NO_ACCESSIBILITY
        downloadStatusTab->setAccessibleName(QApplication::translate("DownloadingProgressDialog", "Download Status", 0));
#endif // QT_NO_ACCESSIBILITY
        DownloadUrlLabel->setText(QApplication::translate("DownloadingProgressDialog", "DownloadUrlLabel", 0));
        label_5->setText(QApplication::translate("DownloadingProgressDialog", "Transfer Rate", 0));
        TransferRateLabel->setText(QApplication::translate("DownloadingProgressDialog", "(unknown)", 0));
        label_6->setText(QApplication::translate("DownloadingProgressDialog", "Time Left", 0));
        TmeLeftLabel->setText(QApplication::translate("DownloadingProgressDialog", "(unknown)", 0));
        label_7->setText(QApplication::translate("DownloadingProgressDialog", "Resume Capability", 0));
        ResumeCapabilityLabel->setText(QApplication::translate("DownloadingProgressDialog", "(unknown)", 0));
        label_2->setText(QApplication::translate("DownloadingProgressDialog", "Status", 0));
        statusLabel->setText(QApplication::translate("DownloadingProgressDialog", "Status Connecting", 0));
        label->setText(QApplication::translate("DownloadingProgressDialog", "File Size", 0));
        fileSizeLabel->setText(QApplication::translate("DownloadingProgressDialog", "(unknown)", 0));
        label_4->setText(QApplication::translate("DownloadingProgressDialog", "Downloaded", 0));
        DownloadedAmountLabel->setText(QApplication::translate("DownloadingProgressDialog", "0", 0));
        DownloadedSizeUnitLabel->setText(QApplication::translate("DownloadingProgressDialog", "bytes", 0));
        tabWidget->setTabText(tabWidget->indexOf(downloadStatusTab), QApplication::translate("DownloadingProgressDialog", "Download Status", 0));
        PauseStartButton->setText(QApplication::translate("DownloadingProgressDialog", "Pause", 0));
        CancelButton->setText(QApplication::translate("DownloadingProgressDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class DownloadingProgressDialog: public Ui_DownloadingProgressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADINGPROGRESSDIALOG_H

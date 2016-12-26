/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSDIALOG_H
#define UI_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget;
    QStackedWidget *optionStacks;
    QWidget *GeneralPage;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *ConnectionsPerDownloadSpinBox;
    QCheckBox *showDownloadsCompleteDialogCheckbox;
    QCheckBox *EnableSoundsCheckBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *maxTasksSpinBox;
    QWidget *SavetoPage;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer;
    QLineEdit *generalDirectoryEdit;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *CompressedDirectoryEdit;
    QPushButton *pushButton_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *DocumentsDirectoryEdit;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *MusicDirectoryEdit;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *ProgramsDirectoryEdit;
    QPushButton *pushButton_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *VideoDirectoryEdit;
    QPushButton *pushButton_4;
    QWidget *Categoriespage;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_24;
    QSpacerItem *horizontalSpacer_12;
    QLineEdit *CompressedExtensionsEdit;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_19;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *DocumentsExtensionsEdit;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_20;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *MusicExtensionsEdit;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_21;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *ProgramsExtensionsEdit;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_22;
    QSpacerItem *horizontalSpacer_10;
    QLineEdit *VideoExtensionsEdit;
    QWidget *NetworkPage;
    QGroupBox *proxySupport;
    QGridLayout *gridLayout_6;
    QLabel *label_9;
    QComboBox *proxyType;
    QLabel *label_10;
    QLineEdit *proxyHostName;
    QLabel *label_11;
    QSpinBox *proxyPort;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_12;
    QLineEdit *proxyUserName;
    QLabel *label_23;
    QLineEdit *proxyPassword;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QStringLiteral("OptionsDialog"));
        OptionsDialog->resize(572, 385);
        buttonBox = new QDialogButtonBox(OptionsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(220, 350, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        listWidget = new QListWidget(OptionsDialog);
        QIcon icon;
        icon.addFile(QStringLiteral(":/settings/images/AddDownload.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/settings/images/harddisk.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/settings/images/extensionmanager.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/settings/images/network-idle.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setIcon(icon3);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 111, 371));
        listWidget->setMinimumSize(QSize(111, 371));
        listWidget->setMaximumSize(QSize(111, 371));
        listWidget->setContextMenuPolicy(Qt::NoContextMenu);
        listWidget->setGridSize(QSize(30, 36));
        listWidget->setViewMode(QListView::ListMode);
        listWidget->setUniformItemSizes(true);
        optionStacks = new QStackedWidget(OptionsDialog);
        optionStacks->setObjectName(QStringLiteral("optionStacks"));
        optionStacks->setGeometry(QRect(130, 10, 431, 331));
        GeneralPage = new QWidget();
        GeneralPage->setObjectName(QStringLiteral("GeneralPage"));
        layoutWidget = new QWidget(GeneralPage);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 40, 421, 27));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        ConnectionsPerDownloadSpinBox = new QSpinBox(layoutWidget);
        ConnectionsPerDownloadSpinBox->setObjectName(QStringLiteral("ConnectionsPerDownloadSpinBox"));
        ConnectionsPerDownloadSpinBox->setMinimum(1);
        ConnectionsPerDownloadSpinBox->setMaximum(20);

        horizontalLayout_2->addWidget(ConnectionsPerDownloadSpinBox);

        showDownloadsCompleteDialogCheckbox = new QCheckBox(GeneralPage);
        showDownloadsCompleteDialogCheckbox->setObjectName(QStringLiteral("showDownloadsCompleteDialogCheckbox"));
        showDownloadsCompleteDialogCheckbox->setGeometry(QRect(0, 70, 221, 21));
        EnableSoundsCheckBox = new QCheckBox(GeneralPage);
        EnableSoundsCheckBox->setObjectName(QStringLiteral("EnableSoundsCheckBox"));
        EnableSoundsCheckBox->setGeometry(QRect(0, 90, 121, 21));
        layoutWidget1 = new QWidget(GeneralPage);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 10, 421, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        maxTasksSpinBox = new QSpinBox(layoutWidget1);
        maxTasksSpinBox->setObjectName(QStringLiteral("maxTasksSpinBox"));
        maxTasksSpinBox->setMinimum(1);
        maxTasksSpinBox->setMaximum(20);

        horizontalLayout->addWidget(maxTasksSpinBox);

        optionStacks->addWidget(GeneralPage);
        SavetoPage = new QWidget();
        SavetoPage->setObjectName(QStringLiteral("SavetoPage"));
        groupBox_2 = new QGroupBox(SavetoPage);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 10, 421, 321));
        groupBox_2->setMinimumSize(QSize(371, 131));
        groupBox_2->setMaximumSize(QSize(500, 500));
        layoutWidget2 = new QWidget(groupBox_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 20, 421, 211));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_14 = new QLabel(layoutWidget2);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_3->addWidget(label_14);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        generalDirectoryEdit = new QLineEdit(layoutWidget2);
        generalDirectoryEdit->setObjectName(QStringLiteral("generalDirectoryEdit"));
        generalDirectoryEdit->setEnabled(false);

        horizontalLayout_3->addWidget(generalDirectoryEdit);

        pushButton = new QPushButton(layoutWidget2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_18 = new QLabel(layoutWidget2);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_8->addWidget(label_18);

        horizontalSpacer_6 = new QSpacerItem(15, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_6);

        CompressedDirectoryEdit = new QLineEdit(layoutWidget2);
        CompressedDirectoryEdit->setObjectName(QStringLiteral("CompressedDirectoryEdit"));
        CompressedDirectoryEdit->setEnabled(false);

        horizontalLayout_8->addWidget(CompressedDirectoryEdit);

        pushButton_6 = new QPushButton(layoutWidget2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_8->addWidget(pushButton_6);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_16 = new QLabel(layoutWidget2);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_4->addWidget(label_16);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        DocumentsDirectoryEdit = new QLineEdit(layoutWidget2);
        DocumentsDirectoryEdit->setObjectName(QStringLiteral("DocumentsDirectoryEdit"));
        DocumentsDirectoryEdit->setEnabled(false);

        horizontalLayout_4->addWidget(DocumentsDirectoryEdit);

        pushButton_2 = new QPushButton(layoutWidget2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_17 = new QLabel(layoutWidget2);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_7->addWidget(label_17);

        horizontalSpacer_3 = new QSpacerItem(51, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        MusicDirectoryEdit = new QLineEdit(layoutWidget2);
        MusicDirectoryEdit->setObjectName(QStringLiteral("MusicDirectoryEdit"));
        MusicDirectoryEdit->setEnabled(false);

        horizontalLayout_7->addWidget(MusicDirectoryEdit);

        pushButton_3 = new QPushButton(layoutWidget2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_7->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_15 = new QLabel(layoutWidget2);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_6->addWidget(label_15);

        horizontalSpacer_4 = new QSpacerItem(31, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        ProgramsDirectoryEdit = new QLineEdit(layoutWidget2);
        ProgramsDirectoryEdit->setObjectName(QStringLiteral("ProgramsDirectoryEdit"));
        ProgramsDirectoryEdit->setEnabled(false);

        horizontalLayout_6->addWidget(ProgramsDirectoryEdit);

        pushButton_5 = new QPushButton(layoutWidget2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_6->addWidget(pushButton_5);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_13 = new QLabel(layoutWidget2);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_5->addWidget(label_13);

        horizontalSpacer_5 = new QSpacerItem(51, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        VideoDirectoryEdit = new QLineEdit(layoutWidget2);
        VideoDirectoryEdit->setObjectName(QStringLiteral("VideoDirectoryEdit"));
        VideoDirectoryEdit->setEnabled(false);

        horizontalLayout_5->addWidget(VideoDirectoryEdit);

        pushButton_4 = new QPushButton(layoutWidget2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_5->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_5);

        optionStacks->addWidget(SavetoPage);
        Categoriespage = new QWidget();
        Categoriespage->setObjectName(QStringLiteral("Categoriespage"));
        groupBox_3 = new QGroupBox(Categoriespage);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 10, 421, 311));
        groupBox_3->setMinimumSize(QSize(371, 131));
        groupBox_3->setMaximumSize(QSize(500, 500));
        layoutWidget_2 = new QWidget(groupBox_3);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 20, 421, 171));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_24 = new QLabel(layoutWidget_2);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_14->addWidget(label_24);

        horizontalSpacer_12 = new QSpacerItem(15, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_12);

        CompressedExtensionsEdit = new QLineEdit(layoutWidget_2);
        CompressedExtensionsEdit->setObjectName(QStringLiteral("CompressedExtensionsEdit"));

        horizontalLayout_14->addWidget(CompressedExtensionsEdit);


        verticalLayout_2->addLayout(horizontalLayout_14);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_19 = new QLabel(layoutWidget_2);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_9->addWidget(label_19);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);

        DocumentsExtensionsEdit = new QLineEdit(layoutWidget_2);
        DocumentsExtensionsEdit->setObjectName(QStringLiteral("DocumentsExtensionsEdit"));

        horizontalLayout_9->addWidget(DocumentsExtensionsEdit);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_20 = new QLabel(layoutWidget_2);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_10->addWidget(label_20);

        horizontalSpacer_8 = new QSpacerItem(51, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_8);

        MusicExtensionsEdit = new QLineEdit(layoutWidget_2);
        MusicExtensionsEdit->setObjectName(QStringLiteral("MusicExtensionsEdit"));

        horizontalLayout_10->addWidget(MusicExtensionsEdit);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_21 = new QLabel(layoutWidget_2);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_11->addWidget(label_21);

        horizontalSpacer_9 = new QSpacerItem(31, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_9);

        ProgramsExtensionsEdit = new QLineEdit(layoutWidget_2);
        ProgramsExtensionsEdit->setObjectName(QStringLiteral("ProgramsExtensionsEdit"));

        horizontalLayout_11->addWidget(ProgramsExtensionsEdit);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_22 = new QLabel(layoutWidget_2);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_12->addWidget(label_22);

        horizontalSpacer_10 = new QSpacerItem(51, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_10);

        VideoExtensionsEdit = new QLineEdit(layoutWidget_2);
        VideoExtensionsEdit->setObjectName(QStringLiteral("VideoExtensionsEdit"));

        horizontalLayout_12->addWidget(VideoExtensionsEdit);


        verticalLayout_2->addLayout(horizontalLayout_12);

        optionStacks->addWidget(Categoriespage);
        NetworkPage = new QWidget();
        NetworkPage->setObjectName(QStringLiteral("NetworkPage"));
        proxySupport = new QGroupBox(NetworkPage);
        proxySupport->setObjectName(QStringLiteral("proxySupport"));
        proxySupport->setEnabled(true);
        proxySupport->setGeometry(QRect(0, 10, 431, 222));
        proxySupport->setCheckable(true);
        gridLayout_6 = new QGridLayout(proxySupport);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_9 = new QLabel(proxySupport);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_9, 0, 0, 1, 1);

        proxyType = new QComboBox(proxySupport);
        proxyType->setObjectName(QStringLiteral("proxyType"));

        gridLayout_6->addWidget(proxyType, 0, 1, 1, 2);

        label_10 = new QLabel(proxySupport);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_10, 1, 0, 1, 1);

        proxyHostName = new QLineEdit(proxySupport);
        proxyHostName->setObjectName(QStringLiteral("proxyHostName"));

        gridLayout_6->addWidget(proxyHostName, 1, 1, 1, 2);

        label_11 = new QLabel(proxySupport);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_11, 2, 0, 1, 1);

        proxyPort = new QSpinBox(proxySupport);
        proxyPort->setObjectName(QStringLiteral("proxyPort"));
        proxyPort->setMaximum(10000);
        proxyPort->setValue(1080);

        gridLayout_6->addWidget(proxyPort, 2, 1, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(293, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_11, 2, 2, 1, 1);

        label_12 = new QLabel(proxySupport);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_12, 3, 0, 1, 1);

        proxyUserName = new QLineEdit(proxySupport);
        proxyUserName->setObjectName(QStringLiteral("proxyUserName"));

        gridLayout_6->addWidget(proxyUserName, 3, 1, 1, 2);

        label_23 = new QLabel(proxySupport);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_23, 4, 0, 1, 1);

        proxyPassword = new QLineEdit(proxySupport);
        proxyPassword->setObjectName(QStringLiteral("proxyPassword"));
        proxyPassword->setEchoMode(QLineEdit::Password);

        gridLayout_6->addWidget(proxyPassword, 4, 1, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_2, 5, 0, 1, 1);

        optionStacks->addWidget(NetworkPage);
#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(ConnectionsPerDownloadSpinBox);
        label->setBuddy(maxTasksSpinBox);
        label_14->setBuddy(pushButton);
        label_18->setBuddy(pushButton_6);
        label_16->setBuddy(pushButton_2);
        label_17->setBuddy(pushButton_3);
        label_15->setBuddy(pushButton_5);
        label_13->setBuddy(pushButton_4);
        label_24->setBuddy(CompressedExtensionsEdit);
        label_19->setBuddy(DocumentsExtensionsEdit);
        label_20->setBuddy(MusicExtensionsEdit);
        label_21->setBuddy(ProgramsExtensionsEdit);
        label_22->setBuddy(VideoExtensionsEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(listWidget, maxTasksSpinBox);
        QWidget::setTabOrder(maxTasksSpinBox, ConnectionsPerDownloadSpinBox);
        QWidget::setTabOrder(ConnectionsPerDownloadSpinBox, showDownloadsCompleteDialogCheckbox);
        QWidget::setTabOrder(showDownloadsCompleteDialogCheckbox, EnableSoundsCheckBox);
        QWidget::setTabOrder(EnableSoundsCheckBox, generalDirectoryEdit);
        QWidget::setTabOrder(generalDirectoryEdit, pushButton);
        QWidget::setTabOrder(pushButton, CompressedDirectoryEdit);
        QWidget::setTabOrder(CompressedDirectoryEdit, pushButton_6);
        QWidget::setTabOrder(pushButton_6, DocumentsDirectoryEdit);
        QWidget::setTabOrder(DocumentsDirectoryEdit, pushButton_2);
        QWidget::setTabOrder(pushButton_2, MusicDirectoryEdit);
        QWidget::setTabOrder(MusicDirectoryEdit, pushButton_3);
        QWidget::setTabOrder(pushButton_3, ProgramsDirectoryEdit);
        QWidget::setTabOrder(ProgramsDirectoryEdit, pushButton_5);
        QWidget::setTabOrder(pushButton_5, VideoDirectoryEdit);
        QWidget::setTabOrder(VideoDirectoryEdit, pushButton_4);
        QWidget::setTabOrder(pushButton_4, CompressedExtensionsEdit);
        QWidget::setTabOrder(CompressedExtensionsEdit, DocumentsExtensionsEdit);
        QWidget::setTabOrder(DocumentsExtensionsEdit, MusicExtensionsEdit);
        QWidget::setTabOrder(MusicExtensionsEdit, ProgramsExtensionsEdit);
        QWidget::setTabOrder(ProgramsExtensionsEdit, VideoExtensionsEdit);
        QWidget::setTabOrder(VideoExtensionsEdit, buttonBox);

        retranslateUi(OptionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionsDialog, SLOT(reject()));

        optionStacks->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Options", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("OptionsDialog", "General", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("OptionsDialog", "Save To", 0));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("OptionsDialog", "Categories", 0));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("OptionsDialog", "Network", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        label_2->setText(QApplication::translate("OptionsDialog", "Connections per download", 0));
        showDownloadsCompleteDialogCheckbox->setText(QApplication::translate("OptionsDialog", "Show Download Complete Dialog", 0));
        EnableSoundsCheckBox->setText(QApplication::translate("OptionsDialog", "Enable Sounds", 0));
        label->setText(QApplication::translate("OptionsDialog", "Max Running Downloads", 0));
        groupBox_2->setTitle(QApplication::translate("OptionsDialog", "Locations", 0));
        label_14->setText(QApplication::translate("OptionsDialog", "General", 0));
        pushButton->setText(QApplication::translate("OptionsDialog", "Browse", 0));
        label_18->setText(QApplication::translate("OptionsDialog", "Compressed", 0));
        pushButton_6->setText(QApplication::translate("OptionsDialog", "Browse", 0));
        label_16->setText(QApplication::translate("OptionsDialog", "Documents", 0));
        pushButton_2->setText(QApplication::translate("OptionsDialog", "Browse", 0));
        label_17->setText(QApplication::translate("OptionsDialog", "Music", 0));
        pushButton_3->setText(QApplication::translate("OptionsDialog", "Browse", 0));
        label_15->setText(QApplication::translate("OptionsDialog", "Programs", 0));
        pushButton_5->setText(QApplication::translate("OptionsDialog", "Browse", 0));
        label_13->setText(QApplication::translate("OptionsDialog", "Video", 0));
        pushButton_4->setText(QApplication::translate("OptionsDialog", "Browse", 0));
        groupBox_3->setTitle(QApplication::translate("OptionsDialog", "Categories", 0));
        label_24->setText(QApplication::translate("OptionsDialog", "Compressed", 0));
        label_19->setText(QApplication::translate("OptionsDialog", "Documents", 0));
        label_20->setText(QApplication::translate("OptionsDialog", "Music", 0));
        label_21->setText(QApplication::translate("OptionsDialog", "Programs", 0));
        label_22->setText(QApplication::translate("OptionsDialog", "Video", 0));
        proxySupport->setTitle(QApplication::translate("OptionsDialog", "Enable proxy", 0));
        label_9->setText(QApplication::translate("OptionsDialog", "Type:", 0));
        proxyType->clear();
        proxyType->insertItems(0, QStringList()
         << QApplication::translate("OptionsDialog", "Socks5", 0)
         << QApplication::translate("OptionsDialog", "Http", 0)
        );
        label_10->setText(QApplication::translate("OptionsDialog", "Host:", 0));
        label_11->setText(QApplication::translate("OptionsDialog", "Port:", 0));
        label_12->setText(QApplication::translate("OptionsDialog", "User Name:", 0));
        label_23->setText(QApplication::translate("OptionsDialog", "Password:", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H

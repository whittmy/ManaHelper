/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_New;
    QAction *actionQuit;
    QAction *actionStop_Download;
    QAction *actionRemove;
    QAction *actionDownload_Now;
    QAction *actionRedownload;
    QAction *actionPause_All;
    QAction *actionStop_All;
    QAction *actionDelete_All_Completed;
    QAction *actionOptions;
    QAction *actionHide_Categories;
    QAction *actionAbout;
    QAction *actionArrange_Files;
    QAction *actionTo_text_file;
    QAction *actionFrom_text_file;
    QAction *actionProperties;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTableView *DownloadsTable;
    QMenuBar *menuBar;
    QMenu *menuTasks;
    QMenu *menuExport;
    QMenu *menuImport;
    QMenu *menuFile;
    QMenu *menuDownload;
    QMenu *menuView;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockCategories;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *categoriesTree;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(640, 480));
        QIcon icon;
        icon.addFile(QStringLiteral(":/menu/images/AddDownload.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        actionAdd_New = new QAction(MainWindow);
        actionAdd_New->setObjectName(QStringLiteral("actionAdd_New"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/menu/images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd_New->setIcon(icon1);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/menu/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon2);
        actionStop_Download = new QAction(MainWindow);
        actionStop_Download->setObjectName(QStringLiteral("actionStop_Download"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/menu/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop_Download->setIcon(icon3);
        actionRemove = new QAction(MainWindow);
        actionRemove->setObjectName(QStringLiteral("actionRemove"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/menu/images/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemove->setIcon(icon4);
        actionDownload_Now = new QAction(MainWindow);
        actionDownload_Now->setObjectName(QStringLiteral("actionDownload_Now"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/menu/images/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDownload_Now->setIcon(icon5);
        actionRedownload = new QAction(MainWindow);
        actionRedownload->setObjectName(QStringLiteral("actionRedownload"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/menu/images/restart.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedownload->setIcon(icon6);
        actionPause_All = new QAction(MainWindow);
        actionPause_All->setObjectName(QStringLiteral("actionPause_All"));
        actionStop_All = new QAction(MainWindow);
        actionStop_All->setObjectName(QStringLiteral("actionStop_All"));
        actionDelete_All_Completed = new QAction(MainWindow);
        actionDelete_All_Completed->setObjectName(QStringLiteral("actionDelete_All_Completed"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/menu/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_All_Completed->setIcon(icon7);
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/menu/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOptions->setIcon(icon8);
        actionHide_Categories = new QAction(MainWindow);
        actionHide_Categories->setObjectName(QStringLiteral("actionHide_Categories"));
        actionHide_Categories->setCheckable(true);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/menu/images/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon9);
        actionArrange_Files = new QAction(MainWindow);
        actionArrange_Files->setObjectName(QStringLiteral("actionArrange_Files"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/menu/images/sort.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionArrange_Files->setIcon(icon10);
        actionTo_text_file = new QAction(MainWindow);
        actionTo_text_file->setObjectName(QStringLiteral("actionTo_text_file"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/menu/images/text.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTo_text_file->setIcon(icon11);
        actionFrom_text_file = new QAction(MainWindow);
        actionFrom_text_file->setObjectName(QStringLiteral("actionFrom_text_file"));
        actionFrom_text_file->setIcon(icon11);
        actionProperties = new QAction(MainWindow);
        actionProperties->setObjectName(QStringLiteral("actionProperties"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/menu/images/batch.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProperties->setIcon(icon12);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        DownloadsTable = new QTableView(centralWidget);
        DownloadsTable->setObjectName(QStringLiteral("DownloadsTable"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DownloadsTable->sizePolicy().hasHeightForWidth());
        DownloadsTable->setSizePolicy(sizePolicy);
        DownloadsTable->setMaximumSize(QSize(10000, 10000));
        DownloadsTable->setContextMenuPolicy(Qt::ActionsContextMenu);
        DownloadsTable->setAcceptDrops(true);
        DownloadsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        DownloadsTable->setDragEnabled(true);
        DownloadsTable->setDragDropOverwriteMode(false);
        DownloadsTable->setDragDropMode(QAbstractItemView::DragDrop);
        DownloadsTable->setDefaultDropAction(Qt::ActionMask);
        DownloadsTable->setAlternatingRowColors(true);
        DownloadsTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
        DownloadsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        DownloadsTable->setGridStyle(Qt::DashLine);
        DownloadsTable->setSortingEnabled(true);
        DownloadsTable->setCornerButtonEnabled(false);
        DownloadsTable->horizontalHeader()->setCascadingSectionResizes(false);
        DownloadsTable->horizontalHeader()->setStretchLastSection(true);
        DownloadsTable->verticalHeader()->setVisible(false);
        DownloadsTable->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(DownloadsTable);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 25));
        menuTasks = new QMenu(menuBar);
        menuTasks->setObjectName(QStringLiteral("menuTasks"));
        menuExport = new QMenu(menuTasks);
        menuExport->setObjectName(QStringLiteral("menuExport"));
        menuImport = new QMenu(menuTasks);
        menuImport->setObjectName(QStringLiteral("menuImport"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuDownload = new QMenu(menuBar);
        menuDownload->setObjectName(QStringLiteral("menuDownload"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockCategories = new QDockWidget(MainWindow);
        dockCategories->setObjectName(QStringLiteral("dockCategories"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dockCategories->sizePolicy().hasHeightForWidth());
        dockCategories->setSizePolicy(sizePolicy1);
        dockCategories->setMinimumSize(QSize(184, 513));
        dockCategories->setMaximumSize(QSize(184, 10000));
        dockCategories->setContextMenuPolicy(Qt::DefaultContextMenu);
        dockCategories->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        dockCategories->setFeatures(QDockWidget::DockWidgetMovable);
        dockCategories->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        categoriesTree = new QTreeWidget(dockWidgetContents);
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/categories/images/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/categories/images/archive.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/categories/images/document.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/categories/images/audio.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/categories/images/downloadmanagment.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/categories/images/video.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/categories/images/folder_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/categories/images/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/categories/images/prio_0.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/categories/images/tab.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(categoriesTree);
        __qtreewidgetitem->setIcon(0, icon13);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setIcon(0, icon14);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem2->setIcon(0, icon15);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem3->setIcon(0, icon16);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem4->setIcon(0, icon17);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem5->setIcon(0, icon18);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(categoriesTree);
        __qtreewidgetitem6->setIcon(0, icon19);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(__qtreewidgetitem6);
        __qtreewidgetitem7->setIcon(0, icon14);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(__qtreewidgetitem6);
        __qtreewidgetitem8->setIcon(0, icon15);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem6);
        __qtreewidgetitem9->setIcon(0, icon16);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem6);
        __qtreewidgetitem10->setIcon(0, icon17);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(__qtreewidgetitem6);
        __qtreewidgetitem11->setIcon(0, icon18);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(categoriesTree);
        __qtreewidgetitem12->setIcon(0, icon20);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem13->setIcon(0, icon14);
        QTreeWidgetItem *__qtreewidgetitem14 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem14->setIcon(0, icon15);
        QTreeWidgetItem *__qtreewidgetitem15 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem15->setIcon(0, icon16);
        QTreeWidgetItem *__qtreewidgetitem16 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem16->setIcon(0, icon17);
        QTreeWidgetItem *__qtreewidgetitem17 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem17->setIcon(0, icon18);
        QTreeWidgetItem *__qtreewidgetitem18 = new QTreeWidgetItem(categoriesTree);
        __qtreewidgetitem18->setIcon(0, icon21);
        QTreeWidgetItem *__qtreewidgetitem19 = new QTreeWidgetItem(__qtreewidgetitem18);
        __qtreewidgetitem19->setIcon(0, icon22);
        QTreeWidgetItem *__qtreewidgetitem20 = new QTreeWidgetItem(__qtreewidgetitem18);
        __qtreewidgetitem20->setIcon(0, icon22);
        QTreeWidgetItem *__qtreewidgetitem21 = new QTreeWidgetItem(__qtreewidgetitem18);
        __qtreewidgetitem21->setIcon(0, icon22);
        QTreeWidgetItem *__qtreewidgetitem22 = new QTreeWidgetItem(__qtreewidgetitem18);
        __qtreewidgetitem22->setIcon(0, icon22);
        categoriesTree->setObjectName(QStringLiteral("categoriesTree"));
        sizePolicy1.setHeightForWidth(categoriesTree->sizePolicy().hasHeightForWidth());
        categoriesTree->setSizePolicy(sizePolicy1);
        categoriesTree->setMinimumSize(QSize(166, 470));
        categoriesTree->setMaximumSize(QSize(166, 1000));
        categoriesTree->setContextMenuPolicy(Qt::DefaultContextMenu);
        categoriesTree->setAcceptDrops(true);
        categoriesTree->setAutoScrollMargin(15);
        categoriesTree->setTabKeyNavigation(true);
        categoriesTree->setDragEnabled(false);
        categoriesTree->setDragDropMode(QAbstractItemView::DropOnly);
        categoriesTree->setDefaultDropAction(Qt::LinkAction);
        categoriesTree->setAlternatingRowColors(true);
        categoriesTree->setAnimated(true);
        categoriesTree->header()->setVisible(false);
        categoriesTree->header()->setHighlightSections(true);

        verticalLayout_2->addWidget(categoriesTree);

        dockCategories->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockCategories);

        menuBar->addAction(menuTasks->menuAction());
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuDownload->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuTasks->addAction(actionAdd_New);
        menuTasks->addSeparator();
        menuTasks->addAction(menuExport->menuAction());
        menuTasks->addAction(menuImport->menuAction());
        menuTasks->addSeparator();
        menuTasks->addAction(actionQuit);
        menuExport->addAction(actionTo_text_file);
        menuImport->addAction(actionFrom_text_file);
        menuFile->addAction(actionStop_Download);
        menuFile->addAction(actionRemove);
        menuFile->addAction(actionDownload_Now);
        menuFile->addAction(actionRedownload);
        menuDownload->addAction(actionPause_All);
        menuDownload->addAction(actionStop_All);
        menuDownload->addAction(actionProperties);
        menuDownload->addSeparator();
        menuDownload->addAction(actionDelete_All_Completed);
        menuDownload->addSeparator();
        menuDownload->addAction(actionOptions);
        menuView->addAction(actionHide_Categories);
        menuView->addAction(actionArrange_Files);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionAdd_New);
        mainToolBar->addAction(actionDownload_Now);
        mainToolBar->addAction(actionStop_Download);
        mainToolBar->addAction(actionRemove);
        mainToolBar->addAction(actionProperties);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Download Manager", 0));
        actionAdd_New->setText(QApplication::translate("MainWindow", "Add New", 0));
        actionAdd_New->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionStop_Download->setText(QApplication::translate("MainWindow", "Stop Download", 0));
        actionRemove->setText(QApplication::translate("MainWindow", "Remove", 0));
        actionDownload_Now->setText(QApplication::translate("MainWindow", "Download Now", 0));
        actionRedownload->setText(QApplication::translate("MainWindow", "Redownload", 0));
        actionPause_All->setText(QApplication::translate("MainWindow", "Pause All", 0));
        actionStop_All->setText(QApplication::translate("MainWindow", "Stop All", 0));
        actionDelete_All_Completed->setText(QApplication::translate("MainWindow", "Delete All Completed", 0));
        actionOptions->setText(QApplication::translate("MainWindow", "Options", 0));
        actionHide_Categories->setText(QApplication::translate("MainWindow", "Hide Categories", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionAbout->setShortcut(QApplication::translate("MainWindow", "F1", 0));
        actionArrange_Files->setText(QApplication::translate("MainWindow", "Arrange Files", 0));
        actionTo_text_file->setText(QApplication::translate("MainWindow", "to text file", 0));
        actionFrom_text_file->setText(QApplication::translate("MainWindow", "from text file", 0));
        actionProperties->setText(QApplication::translate("MainWindow", "Properties", 0));
#ifndef QT_NO_TOOLTIP
        actionProperties->setToolTip(QApplication::translate("MainWindow", "Show Download Properties", 0));
#endif // QT_NO_TOOLTIP
        menuTasks->setTitle(QApplication::translate("MainWindow", "Tasks", 0));
        menuExport->setTitle(QApplication::translate("MainWindow", "Export", 0));
        menuImport->setTitle(QApplication::translate("MainWindow", "Import", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuDownload->setTitle(QApplication::translate("MainWindow", "Downloads", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        mainToolBar->setWindowTitle(QApplication::translate("MainWindow", "Toolbar", 0));
#ifndef QT_NO_TOOLTIP
        dockCategories->setToolTip(QApplication::translate("MainWindow", "Dock for Categories", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        dockCategories->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        dockCategories->setWhatsThis(QApplication::translate("MainWindow", "Categories Dock", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        dockCategories->setAccessibleName(QApplication::translate("MainWindow", "Categories", "Categories"));
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        dockCategories->setAccessibleDescription(QApplication::translate("MainWindow", "Categories Dock", 0));
#endif // QT_NO_ACCESSIBILITY
        dockCategories->setWindowTitle(QApplication::translate("MainWindow", "Categories", 0));
        QTreeWidgetItem *___qtreewidgetitem = categoriesTree->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Type", 0));

        const bool __sortingEnabled = categoriesTree->isSortingEnabled();
        categoriesTree->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = categoriesTree->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "All Downloads", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "Compressed", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainWindow", "Documents", 0));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("MainWindow", "Music", 0));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(0, QApplication::translate("MainWindow", "Programs", 0));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem1->child(4);
        ___qtreewidgetitem6->setText(0, QApplication::translate("MainWindow", "Video", 0));
        QTreeWidgetItem *___qtreewidgetitem7 = categoriesTree->topLevelItem(1);
        ___qtreewidgetitem7->setText(0, QApplication::translate("MainWindow", "Unfinished", 0));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem7->child(0);
        ___qtreewidgetitem8->setText(0, QApplication::translate("MainWindow", "Compressed", 0));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem7->child(1);
        ___qtreewidgetitem9->setText(0, QApplication::translate("MainWindow", "Documents", 0));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem7->child(2);
        ___qtreewidgetitem10->setText(0, QApplication::translate("MainWindow", "Music", 0));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem7->child(3);
        ___qtreewidgetitem11->setText(0, QApplication::translate("MainWindow", "Programs", 0));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem7->child(4);
        ___qtreewidgetitem12->setText(0, QApplication::translate("MainWindow", "Video", 0));
        QTreeWidgetItem *___qtreewidgetitem13 = categoriesTree->topLevelItem(2);
        ___qtreewidgetitem13->setText(0, QApplication::translate("MainWindow", "Finished", 0));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem13->child(0);
        ___qtreewidgetitem14->setText(0, QApplication::translate("MainWindow", "Compressed", 0));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem13->child(1);
        ___qtreewidgetitem15->setText(0, QApplication::translate("MainWindow", "Documents", 0));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem13->child(2);
        ___qtreewidgetitem16->setText(0, QApplication::translate("MainWindow", "Music", 0));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem13->child(3);
        ___qtreewidgetitem17->setText(0, QApplication::translate("MainWindow", "Programs", 0));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem13->child(4);
        ___qtreewidgetitem18->setText(0, QApplication::translate("MainWindow", "Video", 0));
        QTreeWidgetItem *___qtreewidgetitem19 = categoriesTree->topLevelItem(3);
        ___qtreewidgetitem19->setText(0, QApplication::translate("MainWindow", "Queues", 0));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem19->child(0);
        ___qtreewidgetitem20->setText(0, QApplication::translate("MainWindow", "Main Queue", 0));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem19->child(1);
        ___qtreewidgetitem21->setText(0, QApplication::translate("MainWindow", "Queue #1", 0));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem19->child(2);
        ___qtreewidgetitem22->setText(0, QApplication::translate("MainWindow", "Queue #2", 0));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem19->child(3);
        ___qtreewidgetitem23->setText(0, QApplication::translate("MainWindow", "Queue #3", 0));
        categoriesTree->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

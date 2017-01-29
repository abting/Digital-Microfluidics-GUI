/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *New_Layout;
    QAction *Save_Layout;
    QAction *Open_Layout;
    QAction *Save_Sequence;
    QAction *Open_Sequence;
    QAction *Connect;
    QAction *actionSave_Droplets;
    QAction *actionLoad_Droplets;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    QWidget *gridLayoutWidget;
    QGridLayout *electrodeLayout;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget_2;
    QWidget *tabWidget_2Page1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *DispenceButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *SplitButton;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *PreviewButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *StartButton;
    QCheckBox *addDrop;
    QCheckBox *removedrop;
    QPushButton *BeginButton;
    QPushButton *CancelButton;
    QWidget *tab;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *InstructonMonitor;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpinBox *dropTime;
    QLabel *label_2;
    QLabel *currentStepText;
    QLineEdit *lineEdit;
    QSlider *dropSlider;
    QTableWidget *dropTable;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSequencing;
    QMenu *menuAdruino;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1116, 664);
        New_Layout = new QAction(MainWindow);
        New_Layout->setObjectName(QStringLiteral("New_Layout"));
        Save_Layout = new QAction(MainWindow);
        Save_Layout->setObjectName(QStringLiteral("Save_Layout"));
        Open_Layout = new QAction(MainWindow);
        Open_Layout->setObjectName(QStringLiteral("Open_Layout"));
        Save_Sequence = new QAction(MainWindow);
        Save_Sequence->setObjectName(QStringLiteral("Save_Sequence"));
        Open_Sequence = new QAction(MainWindow);
        Open_Sequence->setObjectName(QStringLiteral("Open_Sequence"));
        Connect = new QAction(MainWindow);
        Connect->setObjectName(QStringLiteral("Connect"));
        actionSave_Droplets = new QAction(MainWindow);
        actionSave_Droplets->setObjectName(QStringLiteral("actionSave_Droplets"));
        actionLoad_Droplets = new QAction(MainWindow);
        actionLoad_Droplets->setObjectName(QStringLiteral("actionLoad_Droplets"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        gridLayoutWidget = new QWidget(splitter);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        electrodeLayout = new QGridLayout(gridLayoutWidget);
        electrodeLayout->setSpacing(50);
        electrodeLayout->setContentsMargins(11, 11, 11, 11);
        electrodeLayout->setObjectName(QStringLiteral("electrodeLayout"));
        electrodeLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        electrodeLayout->setContentsMargins(10, 10, 10, 10);
        splitter->addWidget(gridLayoutWidget);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget_2 = new QTabWidget(layoutWidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2Page1 = new QWidget();
        tabWidget_2Page1->setObjectName(QStringLiteral("tabWidget_2Page1"));
        verticalLayout = new QVBoxLayout(tabWidget_2Page1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        DispenceButton = new QPushButton(tabWidget_2Page1);
        DispenceButton->setObjectName(QStringLiteral("DispenceButton"));

        horizontalLayout_2->addWidget(DispenceButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        SplitButton = new QPushButton(tabWidget_2Page1);
        SplitButton->setObjectName(QStringLiteral("SplitButton"));

        horizontalLayout_3->addWidget(SplitButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        PreviewButton = new QPushButton(tabWidget_2Page1);
        PreviewButton->setObjectName(QStringLiteral("PreviewButton"));

        horizontalLayout_4->addWidget(PreviewButton);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        StartButton = new QPushButton(tabWidget_2Page1);
        StartButton->setObjectName(QStringLiteral("StartButton"));
        StartButton->setStyleSheet(QStringLiteral("background: rgb(71, 200, 51)"));

        horizontalLayout->addWidget(StartButton);


        verticalLayout->addLayout(horizontalLayout);

        addDrop = new QCheckBox(tabWidget_2Page1);
        addDrop->setObjectName(QStringLiteral("addDrop"));

        verticalLayout->addWidget(addDrop);

        removedrop = new QCheckBox(tabWidget_2Page1);
        removedrop->setObjectName(QStringLiteral("removedrop"));

        verticalLayout->addWidget(removedrop);

        BeginButton = new QPushButton(tabWidget_2Page1);
        BeginButton->setObjectName(QStringLiteral("BeginButton"));
        BeginButton->setStyleSheet(QStringLiteral("background: rgb(255, 255, 0)"));

        verticalLayout->addWidget(BeginButton);

        CancelButton = new QPushButton(tabWidget_2Page1);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));
        CancelButton->setToolTipDuration(-1);
        CancelButton->setStyleSheet(QStringLiteral("background: rgb(255, 79, 48);"));
        CancelButton->setAutoDefault(false);
        CancelButton->setFlat(false);

        verticalLayout->addWidget(CancelButton);

        tabWidget_2->addTab(tabWidget_2Page1, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget_2->addTab(tab, QString());

        verticalLayout_2->addWidget(tabWidget_2);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        InstructonMonitor = new QTextEdit(groupBox);
        InstructonMonitor->setObjectName(QStringLiteral("InstructonMonitor"));

        verticalLayout_3->addWidget(InstructonMonitor);


        verticalLayout_2->addWidget(groupBox);

        splitter->addWidget(layoutWidget);

        verticalLayout_4->addWidget(splitter);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QStringLiteral("tabWidgetPage1"));
        verticalLayout_6 = new QVBoxLayout(tabWidgetPage1);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label = new QLabel(tabWidgetPage1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        dropTime = new QSpinBox(tabWidgetPage1);
        dropTime->setObjectName(QStringLiteral("dropTime"));
        dropTime->setEnabled(true);
        dropTime->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        dropTime->setMaximum(500);

        horizontalLayout_5->addWidget(dropTime);

        label_2 = new QLabel(tabWidgetPage1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);

        currentStepText = new QLabel(tabWidgetPage1);
        currentStepText->setObjectName(QStringLiteral("currentStepText"));

        horizontalLayout_5->addWidget(currentStepText);

        lineEdit = new QLineEdit(tabWidgetPage1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_5->addWidget(lineEdit);

        dropSlider = new QSlider(tabWidgetPage1);
        dropSlider->setObjectName(QStringLiteral("dropSlider"));
        dropSlider->setMaximum(0);
        dropSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(dropSlider);


        verticalLayout_5->addLayout(horizontalLayout_5);

        dropTable = new QTableWidget(tabWidgetPage1);
        if (dropTable->columnCount() < 3)
            dropTable->setColumnCount(3);
        if (dropTable->rowCount() < 3)
            dropTable->setRowCount(3);
        dropTable->setObjectName(QStringLiteral("dropTable"));
        dropTable->setRowCount(3);
        dropTable->setColumnCount(3);
        dropTable->horizontalHeader()->setVisible(false);
        dropTable->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(dropTable);


        verticalLayout_6->addLayout(verticalLayout_5);

        tabWidget->addTab(tabWidgetPage1, QString());

        verticalLayout_4->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1116, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSequencing = new QMenu(menuBar);
        menuSequencing->setObjectName(QStringLiteral("menuSequencing"));
        menuAdruino = new QMenu(menuBar);
        menuAdruino->setObjectName(QStringLiteral("menuAdruino"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSequencing->menuAction());
        menuBar->addAction(menuAdruino->menuAction());
        menuFile->addAction(New_Layout);
        menuFile->addAction(Save_Layout);
        menuFile->addAction(Open_Layout);
        menuFile->addAction(actionSave_Droplets);
        menuFile->addAction(actionLoad_Droplets);
        menuSequencing->addAction(Save_Sequence);
        menuSequencing->addAction(Open_Sequence);
        menuAdruino->addAction(Connect);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(0);
        CancelButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        New_Layout->setText(QApplication::translate("MainWindow", "New Layout", 0));
        New_Layout->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        Save_Layout->setText(QApplication::translate("MainWindow", "Save Layout", 0));
        Save_Layout->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        Open_Layout->setText(QApplication::translate("MainWindow", "Open Layout", 0));
        Open_Layout->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        Save_Sequence->setText(QApplication::translate("MainWindow", "Save Sequence", 0));
        Save_Sequence->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0));
        Open_Sequence->setText(QApplication::translate("MainWindow", "Open Sequence", 0));
        Open_Sequence->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+O", 0));
        Connect->setText(QApplication::translate("MainWindow", "Connect ", 0));
        Connect->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+C", 0));
        actionSave_Droplets->setText(QApplication::translate("MainWindow", "Save Droplets", 0));
        actionSave_Droplets->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        actionLoad_Droplets->setText(QApplication::translate("MainWindow", "Load Droplets", 0));
#ifndef QT_NO_STATUSTIP
        DispenceButton->setStatusTip(QApplication::translate("MainWindow", "perform Dispence", 0));
#endif // QT_NO_STATUSTIP
        DispenceButton->setText(QApplication::translate("MainWindow", "Dispense", 0));
#ifndef QT_NO_STATUSTIP
        SplitButton->setStatusTip(QApplication::translate("MainWindow", "perform split", 0));
#endif // QT_NO_STATUSTIP
        SplitButton->setText(QApplication::translate("MainWindow", "Split", 0));
#ifndef QT_NO_STATUSTIP
        PreviewButton->setStatusTip(QApplication::translate("MainWindow", "Preview current sequence", 0));
#endif // QT_NO_STATUSTIP
        PreviewButton->setText(QApplication::translate("MainWindow", "Preview", 0));
#ifndef QT_NO_STATUSTIP
        StartButton->setStatusTip(QApplication::translate("MainWindow", "Send the path sequence to Arduino", 0));
#endif // QT_NO_STATUSTIP
        StartButton->setText(QApplication::translate("MainWindow", "Start", 0));
        addDrop->setText(QApplication::translate("MainWindow", "Add Droplet", 0));
        removedrop->setText(QApplication::translate("MainWindow", "Remove Droplet", 0));
        BeginButton->setText(QApplication::translate("MainWindow", "Begin Dispensing", 0));
#ifndef QT_NO_TOOLTIP
        CancelButton->setToolTip(QApplication::translate("MainWindow", "[Esc]", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        CancelButton->setStatusTip(QApplication::translate("MainWindow", "Press to cancel the action", 0));
#endif // QT_NO_STATUSTIP
        CancelButton->setText(QApplication::translate("MainWindow", "Cancel", 0));
        CancelButton->setShortcut(QApplication::translate("MainWindow", "Esc", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tabWidget_2Page1), QString());
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QApplication::translate("MainWindow", "Page", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Instruction Monitor", 0));
        label->setText(QApplication::translate("MainWindow", "Maximum Step:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Current Step:", 0));
        currentStepText->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuSequencing->setTitle(QApplication::translate("MainWindow", "Sequencing", 0));
        menuAdruino->setTitle(QApplication::translate("MainWindow", "Adruino", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

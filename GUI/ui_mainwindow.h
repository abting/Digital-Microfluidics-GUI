/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    QWidget *gridLayoutWidget;
    QGridLayout *electrodeLayout;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *ModeButtonTab;
    QWidget *DropletMode;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *DispenceButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *SplitButton;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *PreviewButton;
    QPushButton *CancelPreviwButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *StartButton;
    QCheckBox *addDrop;
    QCheckBox *removedrop;
    QPushButton *BeginButton;
    QPushButton *CancelButton;
    QWidget *ElectrodeMode;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QPushButton *Increment_EmodeButton;
    QPushButton *preview_EmodeButton;
    QPushButton *CancelPreviwEmodeButton;
    QPushButton *Start_EmodeButton;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *turnOn_EmodeButton;
    QCheckBox *turnOff_EmodeButton;
    QCheckBox *RealTimeActuationBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *InstructonMonitor;
    QTabWidget *ModeTableTab;
    QWidget *DropletMode1;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpinBox *dropTime;
    QLabel *label_2;
    QLabel *currentStepText;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *dropTable;
    QWidget *ElectrodeMode1;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QSpinBox *dropTimeEmode;
    QLabel *label_6;
    QLabel *currentStepText_Emode;
    QSpacerItem *horizontalSpacer_3;
    QTableWidget *dropTableEmode;
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
        MainWindow->resize(1095, 692);
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
        ModeButtonTab = new QTabWidget(layoutWidget);
        ModeButtonTab->setObjectName(QStringLiteral("ModeButtonTab"));
        DropletMode = new QWidget();
        DropletMode->setObjectName(QStringLiteral("DropletMode"));
        verticalLayout = new QVBoxLayout(DropletMode);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        DispenceButton = new QPushButton(DropletMode);
        DispenceButton->setObjectName(QStringLiteral("DispenceButton"));

        horizontalLayout_2->addWidget(DispenceButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        SplitButton = new QPushButton(DropletMode);
        SplitButton->setObjectName(QStringLiteral("SplitButton"));

        horizontalLayout_3->addWidget(SplitButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        PreviewButton = new QPushButton(DropletMode);
        PreviewButton->setObjectName(QStringLiteral("PreviewButton"));

        horizontalLayout_4->addWidget(PreviewButton);


        verticalLayout->addLayout(horizontalLayout_4);

        CancelPreviwButton = new QPushButton(DropletMode);
        CancelPreviwButton->setObjectName(QStringLiteral("CancelPreviwButton"));
        CancelPreviwButton->setStyleSheet(QStringLiteral("background: rgb(255, 79, 48);"));

        verticalLayout->addWidget(CancelPreviwButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        StartButton = new QPushButton(DropletMode);
        StartButton->setObjectName(QStringLiteral("StartButton"));
        StartButton->setStyleSheet(QStringLiteral("background: rgb(71, 200, 51)"));

        horizontalLayout->addWidget(StartButton);


        verticalLayout->addLayout(horizontalLayout);

        addDrop = new QCheckBox(DropletMode);
        addDrop->setObjectName(QStringLiteral("addDrop"));

        verticalLayout->addWidget(addDrop);

        removedrop = new QCheckBox(DropletMode);
        removedrop->setObjectName(QStringLiteral("removedrop"));

        verticalLayout->addWidget(removedrop);

        BeginButton = new QPushButton(DropletMode);
        BeginButton->setObjectName(QStringLiteral("BeginButton"));

        verticalLayout->addWidget(BeginButton);

        CancelButton = new QPushButton(DropletMode);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));
        CancelButton->setToolTipDuration(-1);
        CancelButton->setStyleSheet(QStringLiteral("background: rgb(255, 79, 48);"));
        CancelButton->setAutoDefault(false);
        CancelButton->setFlat(false);

        verticalLayout->addWidget(CancelButton);

        ModeButtonTab->addTab(DropletMode, QString());
        ElectrodeMode = new QWidget();
        ElectrodeMode->setObjectName(QStringLiteral("ElectrodeMode"));
        verticalLayout_11 = new QVBoxLayout(ElectrodeMode);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        Increment_EmodeButton = new QPushButton(ElectrodeMode);
        Increment_EmodeButton->setObjectName(QStringLiteral("Increment_EmodeButton"));

        verticalLayout_10->addWidget(Increment_EmodeButton);

        preview_EmodeButton = new QPushButton(ElectrodeMode);
        preview_EmodeButton->setObjectName(QStringLiteral("preview_EmodeButton"));

        verticalLayout_10->addWidget(preview_EmodeButton);

        CancelPreviwEmodeButton = new QPushButton(ElectrodeMode);
        CancelPreviwEmodeButton->setObjectName(QStringLiteral("CancelPreviwEmodeButton"));
        CancelPreviwEmodeButton->setStyleSheet(QStringLiteral("background: rgb(255, 79, 48);"));

        verticalLayout_10->addWidget(CancelPreviwEmodeButton);

        Start_EmodeButton = new QPushButton(ElectrodeMode);
        Start_EmodeButton->setObjectName(QStringLiteral("Start_EmodeButton"));
        Start_EmodeButton->setStyleSheet(QStringLiteral("background: rgb(71, 200, 51)"));

        verticalLayout_10->addWidget(Start_EmodeButton);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        turnOn_EmodeButton = new QCheckBox(ElectrodeMode);
        turnOn_EmodeButton->setObjectName(QStringLiteral("turnOn_EmodeButton"));

        horizontalLayout_6->addWidget(turnOn_EmodeButton);

        turnOff_EmodeButton = new QCheckBox(ElectrodeMode);
        turnOff_EmodeButton->setObjectName(QStringLiteral("turnOff_EmodeButton"));

        horizontalLayout_6->addWidget(turnOff_EmodeButton);


        verticalLayout_7->addLayout(horizontalLayout_6);

        RealTimeActuationBox = new QCheckBox(ElectrodeMode);
        RealTimeActuationBox->setObjectName(QStringLiteral("RealTimeActuationBox"));

        verticalLayout_7->addWidget(RealTimeActuationBox);


        verticalLayout_10->addLayout(verticalLayout_7);


        verticalLayout_11->addLayout(verticalLayout_10);

        ModeButtonTab->addTab(ElectrodeMode, QString());

        verticalLayout_2->addWidget(ModeButtonTab);

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

        ModeTableTab = new QTabWidget(centralWidget);
        ModeTableTab->setObjectName(QStringLiteral("ModeTableTab"));
        DropletMode1 = new QWidget();
        DropletMode1->setObjectName(QStringLiteral("DropletMode1"));
        verticalLayout_6 = new QVBoxLayout(DropletMode1);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label = new QLabel(DropletMode1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        dropTime = new QSpinBox(DropletMode1);
        dropTime->setObjectName(QStringLiteral("dropTime"));
        dropTime->setEnabled(true);
        dropTime->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        dropTime->setMaximum(500);

        horizontalLayout_5->addWidget(dropTime);

        label_2 = new QLabel(DropletMode1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);

        currentStepText = new QLabel(DropletMode1);
        currentStepText->setObjectName(QStringLiteral("currentStepText"));

        horizontalLayout_5->addWidget(currentStepText);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_5);

        dropTable = new QTableWidget(DropletMode1);
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

        ModeTableTab->addTab(DropletMode1, QString());
        ElectrodeMode1 = new QWidget();
        ElectrodeMode1->setObjectName(QStringLiteral("ElectrodeMode1"));
        verticalLayout_9 = new QVBoxLayout(ElectrodeMode1);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(ElectrodeMode1);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        dropTimeEmode = new QSpinBox(ElectrodeMode1);
        dropTimeEmode->setObjectName(QStringLiteral("dropTimeEmode"));
        dropTimeEmode->setEnabled(true);
        dropTimeEmode->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        dropTimeEmode->setMaximum(500);

        horizontalLayout_7->addWidget(dropTimeEmode);

        label_6 = new QLabel(ElectrodeMode1);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_7->addWidget(label_6);

        currentStepText_Emode = new QLabel(ElectrodeMode1);
        currentStepText_Emode->setObjectName(QStringLiteral("currentStepText_Emode"));

        horizontalLayout_7->addWidget(currentStepText_Emode);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_8->addLayout(horizontalLayout_7);

        dropTableEmode = new QTableWidget(ElectrodeMode1);
        if (dropTableEmode->columnCount() < 2)
            dropTableEmode->setColumnCount(2);
        if (dropTableEmode->rowCount() < 3)
            dropTableEmode->setRowCount(3);
        dropTableEmode->setObjectName(QStringLiteral("dropTableEmode"));
        dropTableEmode->setRowCount(3);
        dropTableEmode->setColumnCount(2);
        dropTableEmode->horizontalHeader()->setVisible(false);
        dropTableEmode->verticalHeader()->setVisible(false);

        verticalLayout_8->addWidget(dropTableEmode);


        verticalLayout_9->addLayout(verticalLayout_8);

        ModeTableTab->addTab(ElectrodeMode1, QString());

        verticalLayout_4->addWidget(ModeTableTab);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1095, 21));
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
        menuSequencing->addAction(Save_Sequence);
        menuSequencing->addAction(Open_Sequence);
        menuAdruino->addAction(Connect);

        retranslateUi(MainWindow);

        ModeButtonTab->setCurrentIndex(1);
        CancelButton->setDefault(false);
        ModeTableTab->setCurrentIndex(0);


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
        CancelPreviwButton->setText(QApplication::translate("MainWindow", "Cancel Preview", 0));
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
        ModeButtonTab->setTabText(ModeButtonTab->indexOf(DropletMode), QApplication::translate("MainWindow", "Droplet Mode", 0));
#ifndef QT_NO_TOOLTIP
        Increment_EmodeButton->setToolTip(QApplication::translate("MainWindow", "Press spacebar to Increment", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        Increment_EmodeButton->setStatusTip(QApplication::translate("MainWindow", "Press spacebar to Increment", 0));
#endif // QT_NO_STATUSTIP
        Increment_EmodeButton->setText(QApplication::translate("MainWindow", "Increment", 0));
        Increment_EmodeButton->setShortcut(QApplication::translate("MainWindow", "Space", 0));
        preview_EmodeButton->setText(QApplication::translate("MainWindow", "Preview", 0));
        CancelPreviwEmodeButton->setText(QApplication::translate("MainWindow", "Cancel Preview", 0));
        Start_EmodeButton->setText(QApplication::translate("MainWindow", "Start", 0));
        turnOn_EmodeButton->setText(QApplication::translate("MainWindow", "Turn ON Electrode", 0));
        turnOff_EmodeButton->setText(QApplication::translate("MainWindow", "Turn OFF Electrode", 0));
        RealTimeActuationBox->setText(QApplication::translate("MainWindow", "Real-Time Actuation", 0));
        ModeButtonTab->setTabText(ModeButtonTab->indexOf(ElectrodeMode), QApplication::translate("MainWindow", "Electrode Mode", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Instruction Monitor", 0));
        label->setText(QApplication::translate("MainWindow", "Maximum Step:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Current Step:", 0));
        currentStepText->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        ModeTableTab->setTabText(ModeTableTab->indexOf(DropletMode1), QApplication::translate("MainWindow", "Droplet Mode", 0));
        label_5->setText(QApplication::translate("MainWindow", "Maximum Step:", 0));
        label_6->setText(QApplication::translate("MainWindow", "Current Step:", 0));
        currentStepText_Emode->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        ModeTableTab->setTabText(ModeTableTab->indexOf(ElectrodeMode1), QApplication::translate("MainWindow", "Electrode Mode", 0));
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

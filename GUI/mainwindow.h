#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "electrode.h"
#include "layout.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <ClickHandler.h>
#include <PathHandler.h>
#include <Arduino.h>
#include <QCheckBox>
#include <Time.h>
#include <Droplet.h>
#include <Table.h>
#include <QSlider>
#include <QSpinBox>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectSignals();
    void printToInstructionMonitor(string);
    void InitializeUI(bool);

    //Method to ask for user input, creates a new thread and waits for the desired number of electrode clicks
    void getUserInput(int);

    //Droplet Management functions
    void SplitDroplet(QList<Electrode*>);
    void DispenceDroplet(QList<Electrode*>);

    QList<Droplet*> listdrop;

private slots:

    void ProcessClick();
    //SLOT to handle clicked electrodes depending on the functionality required (split, dispence, move, etc)
    void ProcessEvents();

    //UI signals and triggers
    void on_New_Layout_triggered();
    void on_StartButton_clicked();
    void on_SplitButton_clicked();
    void on_PreviewButton_clicked();
    void on_DispenceButton_clicked();
    void on_CancelButton_clicked();
    void on_Connect_triggered();
    void on_Save_Layout_triggered();
    void on_Open_Layout_triggered();
    void on_addDrop_clicked();
    void on_removedrop_clicked();
    void on_BeginButton_clicked();
    void on_actionSave_Droplets_triggered();
    void on_actionLoad_Droplets_triggered();

    void InitializeTable();
    void on_dropTime_valueChanged(int arg1);
    void addDropToTable(Droplet*);
    void updateTable(Droplet*);
    void selectColumn(int);
    void removeDropFromTable(Droplet *drop);
    void timeChange(int);
    void addToDList(Droplet*);

private:
    Ui::MainWindow *ui;

    Layout *mylayout;
    QThread *thread;
    ClickHandler *clickhandler;
    PathHandler *pathHandler;
    Arduino *arduino;
    Time *time;
    Table* tab;

    //Modes
    bool DispenceMode;
    bool SplitMode;
    bool LayoutExists;

    //Widgets
    QGridLayout *ElectrodeLayout;
    QTextEdit *InstructonMonitor;
    QPushButton *SplitButton;
    QPushButton *DispenceButton;
    QPushButton *PreviewButton;
    QPushButton *StartButton;
    QPushButton *CancelButton;
    QCheckBox *AddDroplet;
    QCheckBox *RemoveDeroplet;
    QPushButton *BeginButton;
    QTableWidget *DropletTable;
    QSpinBox *TimeSpinner;
    QSlider *TimeSlider;
    QSlider *TableSlider;
};

#endif // MAINWINDOW_H

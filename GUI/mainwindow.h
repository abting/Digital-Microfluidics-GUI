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

//TODO NEW
#include <QSlider>
#include <QSpinBox>
#include <QTableWidget>
#include <QTabWidget>


//extern bool ow;

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

    QList<Droplet*> listdrop;  //TODO NEW


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



    //TODO NEW
    void InitializeTable();
    void on_dropTime_valueChanged(int arg1);
    void addDropToTable(Droplet*);
    void updateTable(Electrode*);
    void selectColumn(int);
    void removeDropFromTable(Droplet *drop);
    void timeChange(int);
    void addToDList(Droplet*);


    void on_BeginButton_clicked();

    void on_Increment_EmodeButton_clicked();

    void on_Start_EmodeButton_clicked();

    void on_turnOn_EmodeButton_clicked(bool checked);

    void on_turnOff_EmodeButton_clicked(bool checked);

    void DisableSignals();

    void on_ModeButtonTab_tabBarClicked(int index);
    
    void on_ModeTableTab_tabBarClicked(int index);
    
    void on_dropTimeEmode_valueChanged(int arg1);

    void on_addDrop_clicked(bool checked);

    void on_removedrop_clicked(bool checked);



    void on_preview_EmodeButton_clicked();

    void on_Save_Sequence_triggered();

    void on_Open_Sequence_triggered();

    void SpinboxValueChanged(int, Table*,QSpinBox*, int);

    void Preview(Table*, Time*, bool);

    void on_CancelPreviwEmodeButton_clicked();

    void on_CancelPreviwButton_clicked();

    void on_RealTimeActuationBox_clicked(bool checked);

    void on_CancelStart_EmodeButton_clicked();

    void on_CancelStartButton_clicked();

    void on_setActuationButton_clicked();

signals:
    //Emited when the thread should be deleted
    void Done();

private:
    Ui::MainWindow *ui;

    Layout *mylayout;
    QThread *thread;
    ClickHandler *clickhandler;
    PathHandler *pathHandler;
    Arduino *arduino;
    Time *time;
    Time *timeEmode;
    Table* tableDmode;
    Table* tableEmode;


    //Modes
    bool DispenceMode;
    bool SplitMode;
    bool LayoutExists;
    bool turnOn;
    bool turnOff;
    bool RealTimeActuate;
    bool CancelpreviewMode;
    bool CancelpreviewEMode;

    //Widgets
    QGridLayout *ElectrodeLayout;
    QTextEdit *InstructonMonitor;
    QPushButton *SplitButton;
    QPushButton *DispenceButton;
    QPushButton *PreviewButton;
    QPushButton *StartButton;
    QPushButton *CancelButton;
    QCheckBox *AddDroplet;
    QCheckBox *RemoveDroplet;
    QPushButton *BeginButton;   
    QPushButton *CancelPreviewButton;   
    QPushButton *CancelStartButton;
    QSpinBox *IterationBox;
    QLineEdit *IterationDelayText;
    QLineEdit *ActuationText;

    QCheckBox *TurnOnButton;
    QCheckBox *TurnOffButton;
    QPushButton *IncrementButton;
    QPushButton *StartEmodeButton;
    QTabWidget *TabButton;
    QTabWidget *TabTable; 
    QPushButton *CancelPreviewEmodeButton;
    QCheckBox *RealTimeActuationButton;   
    QPushButton *CancelStartEmodeButton;

    //TODO NEW
    QTableWidget *DropletTable;
    QTableWidget *DropletTableEmode;
    QSpinBox *TimeSpinner;
    QSpinBox *TimeSpinnerEmode;
    QSlider *TimeSlider;

signals:
    void increment();
    void stopArduino(bool);
    void deleteArduinoThread();

};

#endif // MAINWINDOW_H

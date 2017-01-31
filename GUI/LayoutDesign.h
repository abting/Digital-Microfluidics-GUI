#ifndef LAYOUTDESIGN_H
#define LAYOUTDESIGN_H

#include <QDialog>
#include <layout.h>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class LayoutDesign;
}

class LayoutDesign : public QDialog
{
    Q_OBJECT

public:
    explicit LayoutDesign(QWidget *parent = 0);
    ~LayoutDesign();

    void DesignLayout();            //method to get the user input for rows and columns
    void ConnectSignals();          //method to connect all the signals needed
    void AddContactPads();          //add the contact pads on top, botom and left side

    //Methods to check for errors
    bool checkDuplicates();         //check for duplicates
    bool checkName();               //check if all electrodes are connected

    QGridLayout *returnDesign();
    int getRows();
    int getColumns();

    //boolean to let the program know the user is done inputting the rows and columns
    bool Done = false;

private slots:
    void Edit();
    void SetElectrodeNumber();
    void on_AcceptButton_clicked();
    void on_CreateButton_clicked();

private:
    Ui::LayoutDesign *ui;
    QList<QPushButton*> contactPads;
    QList<int>          elecName;

    bool        EditMode;
    Layout*     mylayout;
    Electrode*  electrode = NULL;    //refrence to the most recent electrode clicked
    int         inputRows;                  //number of rows the user wants
    int         inputColumns;               //number of columns the user wants

    //widgets
    QGridLayout *Designgrid;      //handler for the QGridLayout
    QPushButton *CreateButton;    //handler for the create button
    QPushButton *AcceptButton;    //handler for the accpet button

    QGridLayout *TopFrame;        //contact pad number 1 to 47
    QGridLayout *BottomFrame;     //contact pad number 58 to 104
    QGridLayout *LeftFrame;       //contact pad number 48  to 57
};

#endif // LAYOUTDESIGN_H

#ifndef LAYOUT_H
#define LAYOUT_H

#include <fstream>
#include <QtCore>
#include <iostream>
#include <QGridLayout>
#include <QMainWindow>
#include <electrode.h>
#include <droplet.h>
#include <QObject>

//forward decleration of the electrode class
//needed for CheckSurroundingElectrodes function
class Electrode;
class Droplet;


class Layout : public QObject
{
 Q_OBJECT

public:

    explicit Layout(QObject *parent = 0);
    ~Layout();
    Layout(QGridLayout*,int,int);
    Layout();
    Layout(QGridLayout *);
    void CreateLayout();                                //method to create a grid of electrodes
    void ClearLayout();                                 //method to clear the grid
    void SaveLayout(QMainWindow*);                      //method to save the current design as a .txt
    void OpenLayout(QMainWindow*,QGridLayout*);         //method to open a saved design
    void saveDroplets(QMainWindow*,QList<Droplet*>);    //save the information about all droplets
    QList<Droplet*> openDroplets(QMainWindow*);         //open and return the info about all droplets
    void FinalizeLayout();                              //method to hide and disable the electrodes not necessary, used after creating a design
    void InsertDesign(QGridLayout*);                    //method to recieve the desired design from the "LayoutDesign" class and copy it to the mainwindow
    void CheckSurroundingElectrodes(Electrode*, int time);        //method to check right, bottom, left and top of a given electrodde for available droplets to merge and move

    //setters and getters
    int getRows();
    int getColumns();
    void setRows(int);
    void setColumns(int);

    //adds the surrounding neibors of an electrode to it
    void Neighbors();

 private:
     int rows;
     int columns;
     QGridLayout *gridlayout;

signals:
     void Lsignal(Droplet* nDrop);
     void l(int a);


};

#endif // LAYOUT_H

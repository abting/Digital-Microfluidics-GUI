#include <QGridLayout>
#include <QFileDialog>
#include "layout.h"
#include "electrode.h"
#include <iostream>
#include <QMessageBox>
#include "Droplet.h"

Layout::Layout(QObject *parent): QObject(parent){
}

Layout::~Layout(){
}

Layout::Layout(QGridLayout *_gridlayout,int _rows, int _columns)
{
    rows= _rows;
    columns = _columns;
    gridlayout = _gridlayout;

    gridlayout->setSpacing(0);
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->setMargin(0);
}

Layout::Layout(QGridLayout *_gridlayout){
    gridlayout = _gridlayout;
}

Layout::Layout(){

}

void Layout::CreateLayout(){

    for (int i=0; i<rows;i++){
        for(int j=0; j<columns;j++){
            Electrode *electrode = new Electrode(NULL,i,j,"");
            gridlayout->addWidget(electrode,i,j,1,1,0);
        }
    }
}

void Layout::ClearLayout(){

    for (int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            QLayoutItem* item = gridlayout->itemAtPosition(i,j);
            if(item){                
                QWidget* widget = item->widget();
                gridlayout->removeWidget(widget);
                delete widget;
            }
        }
    }
}


void Layout::FinalizeLayout(){

    for (int i=0; i<rows;i++){
        for(int j=0; j<columns;j++){

            QLayoutItem* item = gridlayout->itemAtPosition(i,j);
            QWidget* widget = item->widget();
            Electrode* electrode = dynamic_cast<Electrode*>(widget);
            if(!electrode->getState()){
                electrode->setVisible(false);
                electrode->setEnabled(false);
            }
            else{
                electrode->set_x_position(i);
                electrode->set_y_positon(j);
            }
        }
    }
}

void Layout::InsertDesign(QGridLayout *E_grid){

    int row = E_grid->rowCount();
    int column = E_grid->columnCount();
    for (int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            QLayoutItem* item = E_grid->itemAtPosition(i,j);
            QWidget* widget = item->widget();
            Electrode* electrode = dynamic_cast<Electrode*>(widget);
            if(electrode->getState()){
                electrode->setStyleSheet("background: gray");
                gridlayout->addWidget(electrode,i,j);
            }
        }
    }
}

void Layout::SaveLayout(QMainWindow *layout){

    QString fileName = QFileDialog::getSaveFileName(layout,QObject::tr("Save File"),"","Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream outStream(&file);
    QString text = QString::fromStdString(std::to_string(rows)) + "," + QString::fromStdString(std::to_string(columns))+ "\n";
    outStream << text;

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            QLayoutItem* item = gridlayout->itemAtPosition(i,j);
            if(item){
                QWidget* widget = item->widget();
                Electrode* electrode = dynamic_cast<Electrode*>(widget);
                outStream<<electrode->text()<<",";
            }
            else{
                outStream<<"0"<<",";
            }

        }
        outStream<<endl;
    }
    file.close();
}

void Layout::OpenLayout(QMainWindow *layout,QGridLayout *grid){

    gridlayout = grid;
    gridlayout->setSpacing(0);
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->setMargin(0);

    QString fileName = QFileDialog::getOpenFileName(layout,QObject::tr("Open Design"), "", "Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    ClearLayout();
    QTextStream inStream(&file);
    bool firstLine = true;
    int at_row=0;
    while(!inStream.atEnd()){
        QString line = inStream.readLine();
        QStringList list = line.split(",");
        if(firstLine){
            rows = list.at(0).toInt();
            columns = list.at(1).toInt();
            std::cout<<rows;
            std::cout<<columns;
            firstLine = false;
        }
        else{
            for(int j=0;j<columns;j++){
               if(list.at(j) != "0"){
                   Electrode *electrode = new Electrode(NULL,at_row,j,list.at(j).toStdString());
                   electrode->setState(true);
                   gridlayout->addWidget(electrode,at_row,j,1,1,0);
               }
            }
            at_row++;
        }
    }
   file.close();
}

//check right, bottom,left and top of the clicked electrode to see whether there is a
//droplet nearby or not
void Layout::CheckSurroundingElectrodes(Electrode* clicked_electrode, int time){

   int foundDroplets = 0; //number of droplets found
   QList<Electrode*> occupied_electrodes;  //list of electrodes that have a droplet on them
   Electrode *temp;

   QLayoutItem* item;
   QWidget* widget;

   int i = clicked_electrode->get_x_position();    //current row
   int j = clicked_electrode->get_y_positon();     //current column

   //first check if the clicked electrode already has a droplet on it
   if(clicked_electrode->getAvailability() == 0){
       //FIXME do nothing??or merge??
       clicked_electrode->getDroplet()->updateInfo(clicked_electrode->text(), time,clicked_electrode, "remain");

   }
   else{
       //check right of the current electrode
       item = gridlayout->itemAtPosition(i,j+1);
       if(item){
           widget = item->widget();
           temp = dynamic_cast<Electrode*>(widget);
           if(temp != NULL){
            if(temp->getAvailability() == 0){
                occupied_electrodes << temp;
                foundDroplets++;
           }
         }
       }
       //check bottom of the current electrode
       item = gridlayout->itemAtPosition(i+1,j);
       if(item){
           widget = item->widget();
           temp = dynamic_cast<Electrode*>(widget);
           if(temp != NULL){
            if(temp->getAvailability() == 0){
                occupied_electrodes << temp;
                foundDroplets++;
           }
         }
       }
       //check left of the current electrode
       item = gridlayout->itemAtPosition(i,j-1);
       if(item){
           widget = item->widget();
           temp = dynamic_cast<Electrode*>(widget);
           if(temp != NULL){
            if(temp->getAvailability() == 0){
                occupied_electrodes << temp;
                foundDroplets++;
           }
         }
       }
       //check top of the current electrode
       item = gridlayout->itemAtPosition(i-1,j);
       if(item){
           widget = item->widget();
           temp = dynamic_cast<Electrode*>(widget);
           if(temp != NULL){
            if(temp->getAvailability() == 0){
                occupied_electrodes << temp;
                foundDroplets++;
           }
         }
       }
       //if no droplet is nearby
       if(foundDroplets == 0){
           //TODO add to path or add to time or dont do anything??????
       }
       //if there is only one droplet nearby
       else if(foundDroplets == 1){

            clicked_electrode->setDroplet(occupied_electrodes.at(0)->getDroplet());
            clicked_electrode->getDroplet()->updateInfo(clicked_electrode->text(), time, clicked_electrode, "update");

            if(occupied_electrodes.at(0)->getDroplet()){
                occupied_electrodes.at(0)->removeDroplet();
            }
       }
       //if  there is more than one droplet nearby merge them as a new droplet
       else{
           Droplet *newdrop = new Droplet("Merged","red",0, time);
           newdrop->updateInfo(clicked_electrode->text(), time, clicked_electrode, "update");

          double vol =0;
           foreach(Electrode *elec,occupied_electrodes){

             vol += elec->getDroplet()->getVolume();
             elec->getDroplet()->updateInfo("",time,elec,"merged");
             if(elec->getDroplet()){
                 elec->removeDroplet();
             }
           }
           newdrop->setVolume(vol);
           clicked_electrode->setDroplet(newdrop);

           emit Lsignal(newdrop);
       }
    }
}

void Layout::Neighbors(){

    Electrode *temp;
    Electrode *current;
    QLayoutItem* item;
    QWidget* widget;

    for (int i = 0; i<rows;i++){
        for(int j =0; j<columns; j++){

            //the current electrode that is being checked
            item = gridlayout->itemAtPosition(i,j);
            if(item){
                widget = item->widget();
                current = dynamic_cast<Electrode*>(widget);
            }

            //check top of the current electrode
            item = gridlayout->itemAtPosition(i-1,j);
            if(item){
                widget = item->widget();
                temp = dynamic_cast<Electrode*>(widget);
                if(temp != NULL){
                    current->addNeighbor(temp);
              }
            }
            //check right of the current electrode
            item = gridlayout->itemAtPosition(i,j+1);
            if(item){
                widget = item->widget();
                temp = dynamic_cast<Electrode*>(widget);
                if(temp != NULL){
                    current->addNeighbor(temp);
              }
            }
            //check bottom of the current electrode
            item = gridlayout->itemAtPosition(i+1,j);
            if(item){
                widget = item->widget();
                temp = dynamic_cast<Electrode*>(widget);
                if(temp != NULL){
                    current->addNeighbor(temp);
              }
            }
            //check left of the current electrode
            item = gridlayout->itemAtPosition(i,j-1);
            if(item){
                widget = item->widget();
                temp = dynamic_cast<Electrode*>(widget);
                if(temp != NULL){
                    current->addNeighbor(temp);
              }
            }
        }
    }

}

int Layout::getRows(){
    return rows;
}

int Layout::getColumns(){
    return columns;
}

void Layout::setRows(int _rows){
    rows = _rows;
}

void Layout::setColumns(int _columns){
    columns = _columns;
}



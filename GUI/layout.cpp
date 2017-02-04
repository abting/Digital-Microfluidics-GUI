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

    QString fileName = QFileDialog::getSaveFileName(layout,QObject::tr("Save File"),"Layout Files","Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream outStream(&file);
    outStream<<"#NL"<<endl;
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


    QString fileName = QFileDialog::getOpenFileName(layout,QObject::tr("Open Design"), "Layout Files", "Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream inStream(&file);

    QString specialChar = inStream.readLine();
    if(specialChar != "#NL"){
        QMessageBox::warning(NULL,tr("Wrong File Type"), tr("The chosen file does not contain the information"));
        return;
    }

    ClearLayout();
    bool firstLine = true;
    int at_row=0;
    while(!inStream.atEnd()){
        QString line = inStream.readLine();
        QStringList list = line.split(",");
        if(firstLine){
            rows = list.at(0).toInt();
            columns = list.at(1).toInt();
            //std::cout<<rows;
            //std::cout<<columns;
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
       //TODO clicked on the same droplet?
       clicked_electrode->getDroplet()->updateInfo(clicked_electrode->text(), time,clicked_electrode, "update");

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
            //TODO NEW
            //if(clicked_electrode->getDroplet()!=NULL){
                clicked_electrode->getDroplet()->updateInfo(clicked_electrode->text(), time, clicked_electrode, "update");
            //}
            if(occupied_electrodes.at(0)->getDroplet()){
                occupied_electrodes.at(0)->removeDroplet();
            }
       }
       //if  there is more than one droplet nearby merge them as a new droplet
       else{
           Droplet *newdrop = new Droplet("Merged","red",0, time);
           newdrop->updateInfo(clicked_electrode->text(), time, clicked_electrode, "update");

          double vol =0;
          QString nameMerged = "";
           foreach(Electrode *elec,occupied_electrodes){
             vol += elec->getDroplet()->getVolume();
             nameMerged += elec->getDroplet()->getName() + "-";         //Needed to change "," to "-" to avoid txt file issues
             elec->getDroplet()->updateInfo("",time,elec,"merged");
             if(elec->getDroplet()){
                 elec->removeDroplet();
             }
           }
           nameMerged += "Merged";
           newdrop->setVolume(vol);
           newdrop->setName(nameMerged);
           clicked_electrode->setDroplet(newdrop);
           emit addDropletFromLayout(newdrop);
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

                item = gridlayout->itemAtPosition(i,j+1); //j+1
                if(item){
                    widget = item->widget();
                    temp = dynamic_cast<Electrode*>(widget);
                    if(temp != NULL){
                        current->addNeighbor(temp);
                  }
                }
                //check bottom of the current electrode
                item = gridlayout->itemAtPosition(i+1,j); //i+1
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

//Return the electrode based on it's number, go through the gridlayout
Electrode* Layout::elecFromText(QString elec){
    for (int i=0; i<rows;i++){
        for(int j=0; j<columns;j++){
            if(gridlayout->itemAtPosition(i,j)){
                QLayoutItem* item = gridlayout->itemAtPosition(i,j);
                QWidget* widget = item->widget();
                Electrode* e = dynamic_cast<Electrode*>(widget);
                if(e->text() == elec){
                    return e;
                }
            }
        }
    }
    return NULL;
}

//Sets all the colors to default grey (turned off or no droplets on an electrode)
void Layout::ResetColors(){
    for (int i=0; i<rows;i++){
        for(int j=0; j<columns;j++){
            if(gridlayout->itemAtPosition(i,j)){
                QLayoutItem* item = gridlayout->itemAtPosition(i,j);
                QWidget* widget = item->widget();
                Electrode* e = dynamic_cast<Electrode*>(widget);
                e->setStyleSheet("background-color:grey");
            }
        }
    }
}


void Layout::saveDroplets(QMainWindow *layout,QList<Droplet*> list){

    if(list.isEmpty()) return;

    QString fileName = QFileDialog::getSaveFileName(layout,QObject::tr("Save File"),"Sequence Files","Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream outStream(&file);
    outStream<<"#ND"<<endl;
    foreach(Droplet* drop,list){
        outStream<<drop->getName()<<","<<drop->getColor()<<","<<drop->getVolume()<<","<<drop->getInitialTime()<<",";
        foreach(Info info, drop->getDropletInfo()){
            outStream<<QString::number(info.time)<<","<<info.position<<","<<info.status<<",";
        }
        outStream<<endl;
    }
    file.close();
}

QList<Droplet*> Layout::openDroplets(QMainWindow * layout){
    //TODO open droplets
    QList<Droplet*> dropletlist;
    QString fileName = QFileDialog::getOpenFileName(layout,QObject::tr("Load Droplets"), "Sequence Files", "Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly))
        return dropletlist; //FIXME dont want to return list if it failed to open
    QTextStream inStream(&file);


    QString specialChar = inStream.readLine();
    if(specialChar != "#ND"){
        QMessageBox::warning(NULL,tr("Wrong File Type"), tr("The chosen file does not contain the information"));
        return dropletlist;
    }

    while(!inStream.atEnd()){
        QString line = inStream.readLine();
        QStringList list = line.split(",");

        Droplet* droplet = new Droplet();
        droplet->setName(list.at(0));
        droplet->setColor(list.at(1));
        droplet->setVolume(QString(list.at(2)).toDouble());
        droplet->setInitialTime(QString(list.at(3)).toDouble());

        Electrode* latest;                              //Record the latest electrode
        for(int i = 4; i<list.length()-2; i+=3){
            Info info;
            info.time       =   list.at(i).toInt();
            info.position   =   list.at(i+1);
            info.status     =   list.at(i+2);
            if(info.status!="remain" && info.status!= "absent"){
                info.elec       =   elecFromText(info.position);
                latest = info.elec;
            }
            else if(info.status=="remain"){
                info.elec = latest;                         //It should be set to the last electrode that the droplet was on
            }

            droplet->addInfo(info);
        }
        dropletlist.append(droplet);
    }
   file.close();
   return dropletlist;
}

void Layout::saveElectrodeModeSequence(QMainWindow *layout, Table* tableEmode){

    QString fileName = QFileDialog::getSaveFileName(layout,QObject::tr("Save ElectrodeMode Sequence"),"Sequence Files","Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream outStream(&file);
    outStream<<"#NE"<<endl;
    outStream<<tableEmode->getColumn()<<","<<tableEmode->getRow();          //Save Row and column
    outStream<<endl;
    for(int j = 1;j<tableEmode->getColumn();j++){
        outStream <<QString::number(j)<<",";                                //Save Timeslot (column)
        for(int i = 2; i<tableEmode->getRow();i++){
            if(tableEmode->getItem(i,j)){
                outStream<<tableEmode->getItem(i,j)->text()<<",";           //Save positions at a given timeslot
            }
        }
        outStream<<endl;
    }
    file.close();
}

void Layout::openElectrodeModeSequence(QMainWindow * layout, Table* tableEmode){
    //TODO open droplets

    QString fileName = QFileDialog::getOpenFileName(layout,QObject::tr("Open ElectrodeMode Sequence"), "Sequence Files", "Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly)){
         return;                    //FIXME dont want to return list if it failed to open
    }
    QTextStream inStream(&file);

    QString specialChar = inStream.readLine();
    if(specialChar != "#NE"){
        QMessageBox::warning(NULL,tr("Wrong File Type"), tr("The chosen file does not contain the information"));
        return;
    }

    bool firstLine = true;                              //In the first line record the row and column information
    while(!inStream.atEnd()){
        QString line = inStream.readLine();
        QStringList list = line.split(",");
        if(firstLine){
            QString col = list.at(0);
            QString row = list.at(1);
            emit setColumn(col.toInt()-2);              //offset for table      --Sets the Maximum step to the correct value
            tableEmode->setRow(row.toInt());
            firstLine=false;
        }
        else{
            int i=1;                                                                //First position would appear at index 1
            while(i<list.length()-1){
                QTableWidgetItem* position = new QTableWidgetItem(list.at(i));
                QString col = list.at(0);                                           //Timeslot that it should be added to
                tableEmode->setItem(i+1,col.toInt(),position);                      //Take into account +1 offset for the row
                tableEmode->setBackColor(i+1,col.toInt(),"blue");
                i++;
            }
        }
    }
   file.close();
}

#include "table.h"

Table::Table()
{

}
Table::Table(QTableWidget* dTable )
{

    table = dTable;
}

void Table::CreateTable(QMainWindow* main)
{

    //Setup Table
    table->setColumnCount(3);
    table->setRowCount(3);
    table->setColumnWidth(0,100);
    //for(int i = 1;i<20;i++){
        table->setColumnWidth(1,50);

        table->setColumnWidth(2,20);
    //}
    for (int j = 1;j<3;j++){
        table->setRowHeight(j,20);
    }
    QTableWidgetItem* THeader = new QTableWidgetItem("Timeline");
    QTableWidgetItem* DHeader = new QTableWidgetItem("Droplet Name");
    QTableWidgetItem* VHeader = new QTableWidgetItem("Volume");
    table->setSpan(0,0,2,1);
    table->setSpan(0,1,2,1);
    table->setItem(0, 0, DHeader);
    table->setItem(0, 1, VHeader);
    table->setItem(0, 2, THeader);
    table->item(0,0)->setTextAlignment(Qt::AlignCenter); //4 is center
    table->item(0,1)->setTextAlignment(Qt::AlignCenter); //4 is center
    table->item(0,2)->setTextAlignment(Qt::AlignCenter); //4 is center

    //Setup TableSlider
    slide = new QSlider(Qt::Horizontal);

    connect(slide,SIGNAL(valueChanged(int)),main,SLOT(selectColumn(int)));
    connect(slide,SIGNAL(actionTriggered(int)),main,SLOT(timeChange(int)));
    slide->setMaximum(0);         //Initialize slider size to 0
    slide->setPageStep(1);
    table->setCellWidget(1,2,slide);
}


void Table::addDropToTable(Droplet *drop, QList <Droplet*> listD, int tTime) //tTime is current time
{
    //listD.append(drop);
    QTableWidgetItem* Name = new QTableWidgetItem(drop->getName());
    QTableWidgetItem* Volume = new QTableWidgetItem(QString::number(drop->getVolume()));
    QTableWidgetItem* initialPosition = new QTableWidgetItem(drop->getDropletInfo().at(tTime).position);
    //If table is full, create an extra row
    if(table->item(table->rowCount()-1,0)){
        table->setRowCount(table->rowCount()+1);
        table->setRowHeight(table->rowCount()-1,20);
    }
    //Add the new droplet at the specified time
    table->setItem(table->rowCount()-1, 0, Name);
    table->setItem(table->rowCount()-1, 1, Volume);
    table->setItem(table->rowCount()-1, tTime+2, initialPosition);
    table->item(table->rowCount()-1,tTime+2)->setBackgroundColor(drop->getColor());
}

void Table::removeDropFromTable(Droplet *drop)
{
    for(int i = 2; i<table->rowCount();i++){
        if(drop->getName() == table->item(i,0)->text()){
            table->removeRow(i);
        }
    }
    if(table->rowCount()<=2){
        table->setRowCount(table->rowCount()+1);
        table->setRowHeight(table->rowCount()-1,20);
    }
}


void Table::updateTable(Electrode *elec, int tTime)
{


    if(elec->getDroplet()){
        Droplet *drop = elec->getDroplet();
        int rowNum = 0;
        //Find the row that corresponds to that specified droplet
        for(int i=2;i<table->rowCount();i++){
            if(drop->getName() == table->item(i,0)->text()){
               rowNum = i;
            }
        }
       QTableWidgetItem* item = table->item(rowNum,tTime+2);
       //Check if the droplet name exists
       if(rowNum != 0){
           //Check if that particular time has already been accessed, if so, simply change the text
           if(item){
               table->item(rowNum,tTime+2)->setText(drop->getDropletInfo().at(tTime).position);
               table->item(rowNum,tTime+2)->setBackgroundColor(drop->getColor());
           }
           //Create a new time slot in the table if time hasn't been accessed
           else{
               QTableWidgetItem* initialPosition = new QTableWidgetItem(drop->getDropletInfo().at(tTime).position);
               table->setItem(rowNum, tTime+2, initialPosition);
               table->item(rowNum,tTime+2)->setBackgroundColor(drop->getColor());
           }
       }
    }
}

QSlider* Table::getSlider(){
    return slide;
}

int Table::getColumn(){
    return table->columnCount();
}
int Table::getRow(){
    return table->rowCount();
}

void Table::setColumn(int value){
    table->setColumnCount(value);
}

void Table::setRow(int value){
    table->setRowCount(value);
}

void Table::setColumnW(int col, int value){
    table->setColumnWidth(col,value);
}

void Table::setSp(int r, int c, int rS, int cS){
    table->setSpan(r,c,rS,cS);
}

QTableWidgetItem* Table::getItem(int r, int c){
    return table->item(r,c);
}

void Table::setItem(int r, int c, QTableWidgetItem* it){
    table->setItem(r,c,it);;
}


void Table::updateTableEmode(QString type, Electrode* elec)
{
    if(type=="add"){
        bool addRow = true;
        for(int i = 2; i<table->rowCount(); i++){
            if(table->item(i,slide->value()+1)){        //+1 is for the offset
                //Do Nothing
            }
            else{
                addRow = false;
            }
        }
        if(addRow){
            table->setRowCount(table->rowCount()+1);
            table->setRowHeight(table->rowCount()-1,20);
            table->setSpan(0,0,table->rowCount(),1);
        }
        for(int i = 2; i<table->rowCount(); i++){
            if(table->item(i,slide->value()+1)){
                //Do Nothing
            }
            else{
                QTableWidgetItem* initialPosition = new QTableWidgetItem();
                table->setItem(i,slide->value()+1 , initialPosition);
                table->item(i,slide->value()+1)->setBackgroundColor("blue");
                table->item(i,slide->value()+1)->setText(elec->text());
                break;
            }
        }
    }
    else if(type=="remove"){
        for(int i = 2; i<table->rowCount(); i++){
            if(table->item(i,slide->value()+1)){
                if(table->item(i,slide->value()+1)->text() == elec->text()){
                    //Take back ownership of the item -> equivalent to removing item
                    table->takeItem(i,slide->value()+1);
                }
            }
        }
    }
}

void Table::InitializeTableEmode(QMainWindow* main)
{
    //Setup Table
    table->setColumnCount(2);
    table->setRowCount(3);
    table->setColumnWidth(0,150);
    //for(int i = 1;i<20;i++){
        table->setColumnWidth(1,20);
    //}
    for (int j = 1;j<3;j++){
        table->setRowHeight(j,20);
    }
    QTableWidgetItem* EHeader = new QTableWidgetItem("Electrodes");
    QTableWidgetItem* THeader = new QTableWidgetItem("Timeline");
    table->setSpan(0,0,3,1);
    table->setItem(0, 0, EHeader);
    table->setItem(0, 1, THeader);
    table->item(0,0)->setTextAlignment(Qt::AlignCenter); //4 is center
    table->item(0,1)->setTextAlignment(Qt::AlignCenter); //4 is center

    //Setup TableSlider
    slide = new QSlider(Qt::Horizontal);
    connect(slide,SIGNAL(valueChanged(int)),main,SLOT(selectColumn(int)));
    connect(slide,SIGNAL(actionTriggered(int)),main,SLOT(timeChange(int)));
    slide->setMaximum(0);         //Initialize slider size to 0
    slide->setPageStep(1);
    table->setCellWidget(1,1,slide);
}

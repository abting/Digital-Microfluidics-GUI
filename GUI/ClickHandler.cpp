#include <iostream>
#include <electrode.h>
#include "ClickHandler.h"

//BANANA
ClickHandler::ClickHandler(QObject *parent) : QObject(parent){

}

ClickHandler::ClickHandler(int input){

    ElectrodeList.clear();
    requiredInputs = input;
}

ClickHandler::~ClickHandler(){
    //TODO DELETE QList?
}

void ClickHandler::clicked(){

    //returns a pointer to the object that emited the SIGNAL that envoked this SLOT
    ElectrodeList.append(qobject_cast<Electrode*>(QObject::sender()));

    if(ElectrodeList.size() == requiredInputs){
        emit Done();
    }

}

QList<Electrode*> ClickHandler::getElectrodeList(){
    return ElectrodeList;
}

void ClickHandler::setRequiredInputs(int input){

    requiredInputs = input;
}

int ClickHandler::getRequiredInputs(){

    return requiredInputs;
}



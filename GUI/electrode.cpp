#include "electrode.h"
#include <QPushButton>

Electrode::Electrode(QWidget *parent,int _x,int _y,std::string _number){

     parent = Q_NULLPTR;
     x_position = _x;       //its x position
     y_position = _y;       //its y position

     number = _number;      //number displayed on the elcetrode
     state = false;         //on creation, no electrode is "enabled", clicking on in will result in "enableling" it
     availability = 1;      //all electrodes are "available" since there is no droplet
     droplet = NULL;        //no droplet when the electrode is first created

     this->setMaximumSize(30,30);
     QString text = QString::fromStdString(number);
     this->setText(text);
     this->setStyleSheet("background-color: grey");
}

Electrode::Electrode(){

}

Electrode::~Electrode(){
}

bool Electrode::isEmpty(){
    if(droplet) return false;
    return true;
}

Droplet* Electrode::getDroplet(){
    return droplet;
}

void Electrode::setDroplet(Droplet *drop){
    droplet = drop;
    availability = 0;
    this->setStyleSheet("background-color: " + drop->getColor());
    drop->setParent(this);
    this->setToolTip("Name: " + drop->getName() + "\nVolume: " + QString::number(drop->getVolume()));
}

void Electrode::removeDroplet(){
    this->setStyleSheet("background-color: grey");
    availability = 1;
    //droplet->setParent(NULL);
    droplet = NULL;
    this->setToolTip("");

}

void Electrode::addNeighbor(Electrode* neighbor){
    neighbours.append(neighbor);
}
QList<Electrode*> Electrode::getNeighbors(){
    return neighbours;
}

std::string Electrode::getNumber(){
    return number;
}

int Electrode::get_x_position(){
    return x_position;
}

int Electrode::get_y_positon(){
    return y_position;
}

bool Electrode::getState(){
    return state;
}

double Electrode::getOntime(){
    return onTime;
}

double Electrode::getOffTime(){
    return offTime;
}

int Electrode::getAvailability(){
   return availability;
}

void Electrode::set_x_position(int xpos){
    x_position = xpos;
}

void Electrode::set_y_positon(int ypos){
    y_position = ypos;
}

void Electrode::setNumber(std::string num){
    number = num;
}

void Electrode::setState(bool mstate){
    state = mstate;
}

void Electrode::setOnTime(double otime){
    onTime = otime;
}

void Electrode::setOffTime(double ftime){
    offTime = ftime;
}

void Electrode::setAvailability(int avail){
    availability = avail;
}

#include "Droplet.h"
#include <DropletSelector.h>
#include <qmessagebox.h>

Droplet::Droplet(int FirstIndex){

   DropletSelector *dropselect = new DropletSelector();
   dropselect->exec();

   if(dropselect->Done){
       Selected = true;
       Name = dropselect->getName();
       volume = dropselect->getVolume();
       Color = dropselect->getColor();
       latestElectrode = NULL;
       InitialTime = FirstIndex;

   }

}

Droplet::Droplet(QString name,QString color, double vol, int FirstIndex){

   Name = name;
   Color = color;
   volume = vol;
   InitialTime = FirstIndex;
}

void Droplet::setName(QString name){
   Name = name;
}

void Droplet::setColor(QString color){
   Color = color;
}

void Droplet::setVolume(double vol){
   volume = vol;
}

QString Droplet::getName(){
   return Name;
}

QString Droplet::getColor(){
   return Color;
}

double Droplet::getVolume(){
   return volume;
}

//Updates the droplet's information, it's index represents a time slot
//It contains the droplet's position, electrode (that it is on) and status based on a given time
void Droplet::updateInfo(QString pos, int time, Electrode* e, QString status){

    //The time hasn't been accessed yet in the droplet's information list
    //thus you need to fill in information up until the specified time

    if(time>=DropletInfo.length()){

       Electrode* tempE;
       if(DropletInfo.length()>0){
            tempE = DropletInfo.at(DropletInfo.length()-1).elec;
       }
       QString statusE;
       //The droplet has just been created, but it's added at a later time
       //Thus specify that at times leading up to the current time, it was absent
       if(DropletInfo.length() == 0){
           statusE = "absent";
           tempE = NULL;
       }
       //The droplet has already been created, but it was been untouched for a while
       else{
           statusE = "remain";
       }

       //Fill in the "untouched" time slots with information
       int i = DropletInfo.length();
       while(i<time){
           Info temp1;
           temp1.position = "";
           temp1.time = i;
           temp1.status = statusE;
           temp1.elec = tempE;
           DropletInfo.append(temp1);
           i++;
       }

       //Set the information to the specified time
       Info temp;
       temp.position = pos;
       temp.time = time;
       temp.elec = e;
       temp.status = status;
       DropletInfo.append(temp);
   }


    //If this time has already been accessed and you're editing it
    else{
        if(DropletInfo[time].elec){
            DropletInfo[time].elec->removeDroplet();
        }      
        DropletInfo[time].time = time;
        DropletInfo[time].position = pos;
        DropletInfo[time].elec = e;
        DropletInfo[time].status = status;
   }
}

Info Droplet::getInfo(int time){
   return DropletInfo.at(time);
}

void Droplet::setdropletPath(Info inf){
   DropletInfo.append(inf);
}

QList <Info> Droplet::getDropletInfo(){
   return DropletInfo;
}

void Droplet::setParent(Electrode* par){
    parent = par;
}

Electrode* Droplet::getParent(){
    return parent;
}

void Droplet::setInitialTime(int initial){
    InitialTime = initial;
}

int Droplet::getInitialTime(){
    return InitialTime;
}

void Droplet::setLatestElectrode(Electrode* lateE){
    latestElectrode = lateE;

}

Electrode* Droplet::getLatestElectrode(){
    return latestElectrode;

}





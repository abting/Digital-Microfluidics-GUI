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

Droplet::Droplet(){

}

//checks for a duplicate, the list of droplets has to be pased to it first
bool Droplet::isDupliate(QList<Droplet *> list){
    foreach(Droplet* drop,list){
        if(drop->getName() == Name){
            return true;
        }
    }
    return false;
}

void Droplet::addInfo(Info info){
    DropletInfo.append(info);
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

void Droplet::updateInfo(QString pos, int time, Electrode* e, QString status){

   if(time>=DropletInfo.length()){
       Info temp;
       temp.position = pos;
       temp.time = time;
       temp.elec = e;
       temp.status = status;

       Electrode* tempE;
       if(DropletInfo.length()>0){
            tempE = DropletInfo.at(DropletInfo.length()-1).elec;
       }

       int i = DropletInfo.length();

       QString statusE;
       if(DropletInfo.length() == 0){
           statusE = "absent";
           tempE = NULL;

       }
       else{
           statusE = "remain";
       }
       while(i<time){
           Info temp1;
           temp1.position = ""; //FIXME double commas
           temp1.time = i;
           temp1.status = statusE;
           temp1.elec = tempE;
           DropletInfo.append(temp1);
           i++;
       }

       DropletInfo.append(temp);
   }
   else{

       if(DropletInfo[time].elec){          //If the elctrode is being changed, remove the droplet from it
           DropletInfo[time].elec->removeDroplet();
       }
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





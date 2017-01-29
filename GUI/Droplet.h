#ifndef DROPLET_H
#define DROPLET_H

#include <iostream>
#include <QString>
#include <QList>
#include <electrode.h>

class Electrode;

struct Info
{
   int time;
   QString position; 
   QString status;
   Electrode* elec;
};

class Droplet
{
public:
   Droplet();
   Droplet(int);
   Droplet(QString name,QString color,double volume, int);

   //setters and getters
   void setName(QString name);
   void setColor(QString color);
   void setVolume(double volume);

   void updateInfo(QString pos, int time, Electrode*, QString);     //update the position and the time of the droplet
   void setdropletPath(Info);

   QString getName();
   QString getColor();
   double getVolume();

   QList <Info> getDropletInfo();
   Info getInfo(int time);            //get the struct at a specific time
   void addInfo(Info);

   bool Selected = false;

   void setParent(Electrode*);
   Electrode* getParent();
   void setInitialTime(int);
   int getInitialTime();
   Electrode* getLatestElectrode();
   void setLatestElectrode(Electrode*);

private:

   QString Color;
   QString Name;
   double volume;      //uL
   int InitialTime;

   Electrode* parent;
   Electrode* latestElectrode;

   QList <Info> DropletInfo;  //list of droplet's position at a specific time

};

#endif // DROPLET_H




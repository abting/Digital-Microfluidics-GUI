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
   Electrode* elec;
   QString status;
};

class Droplet
{
public:
   Droplet(int);
   Droplet(QString name,QString color,double volume, int);
   Droplet();

   //setters and getters
   void setName(QString name);
   void setColor(QString color);
   void setVolume(double volume);
   void setdropletPath(Info);
   QString getName();
   QString getColor();
   double getVolume();
   Info getInfo(int time);            //get the struct at a specific time

   void updateInfo(QString pos, int time, Electrode*, QString);     //update the position and the time of the droplet


   QList <Info> getDropletInfo();

   bool Selected = false;

   //TODO NEW

   void setParent(Electrode*);
   Electrode* getParent();
   void setInitialTime(int);
   int getInitialTime();
   Electrode* getLatestElectrode();
   void setLatestElectrode(Electrode*);

   bool isDupliate(QList<Droplet*>);
   void addInfo(Info);

private:
   QString Color;
   QString Name;
   double volume;      //microL
   int InitialTime;

   Electrode* parent;
   Electrode* latestElectrode;

   QList <Info> DropletInfo;  //list of droplet's position at a specific time

};

#endif // DROPLET_H




#ifndef TIME_H
#define TIME_H

#include <QList>
#include <Droplet.h>
#include <QSlider>
#include <QSpinBox>

class Time
{
public:
   Time();
   Time(QSlider*);
   void setPreviousTime();
   int getPreviousTime();
   int CurrentTime();
   void increaseTime(QSpinBox* );   //increase time (just increase the index)


//   void undoLastEntry(Droplet *droplet);                //deletes last entry of QList time
//   void deleteDropletPath(Droplet* droplet, int Index);   //deletes the rest of the Droplet path INCASE the user made an error
//   QList <int> returnTimeList();


   QList <int> time;                    //list of total times


private:

   int PreviousTime;
   QSlider *TimeSlider;


};

#endif // TIME_H



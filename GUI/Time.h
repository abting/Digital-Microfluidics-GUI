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
   QList <int> time;                //list of total times

private:

   int PreviousTime;
   QSlider *TimeSlider;
};

#endif // TIME_H



#include "Time.h"

Time::Time()
{
   time.clear();   //clear the list
   time << 0;      //start the timer at ZERO (the first element of the QList is the integer ZERO)
}

Time::Time(QSlider* slider)
{

   time.clear();   //clear the list
   time << 0;      //start the timer at ZERO (the first element of the QList is the integer ZERO)
   TimeSlider = slider;
}

int Time::CurrentTime()
{
   return TimeSlider->value();
}

void Time::setPreviousTime()
{
    PreviousTime = TimeSlider->value();
}

int Time::getPreviousTime()
{
    return PreviousTime;
}


//QList<int> Time::returnTimeList()
//{
//   return time;
//}

//void Time::undoLastEntry(Droplet *droplet)
//{

//}

//void Time::deleteDropletPath(Droplet* droplet, int Index ){

//}

void Time::increaseTime(QSpinBox* TimeSpin)
{
    if(TimeSpin->value()<=TimeSlider->value()){
        TimeSpin->setValue(TimeSpin->value()+1);
    }
    TimeSlider->setValue(TimeSlider->value()+1);
}




#include "Time.h"


Time::Time(QObject *parent): QObject(parent){
}
Time::~Time(){

}
Time::Time(QSlider* slider)
{

   timeD = 0;
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
void Time::increaseTime(QSpinBox* TimeSpin)
{
    if(TimeSpin->value()<=TimeSlider->value()){
        TimeSpin->setValue(TimeSpin->value()+1);
    }
    TimeSlider->setValue(TimeSlider->value()+1);
}

//For Sleep function in preview
void Time::timeDelay(){
    timeD += 1;
    QThread::msleep(500);
    QString a =QString::number(timeD);
    emit timeDelayPreview(a);
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






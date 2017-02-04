#ifndef TIME_H
#define TIME_H

#include <QList>
#include <Droplet.h>
#include <QSlider>
#include <QSpinBox>
#include <QObject>

class Time : public QObject
{
    Q_OBJECT

public:


   explicit Time(QObject *parent = 0);
   ~Time();
   Time(QSlider*);
   void setPreviousTime();
   int getPreviousTime();
   int CurrentTime();
   int timeD;
   void increaseTime(QSpinBox* );   //increase time (just increase the index)


//   void undoLastEntry(Droplet *droplet);                //deletes last entry of QList time
//   void deleteDropletPath(Droplet* droplet, int Index);   //deletes the rest of the Droplet path INCASE the user made an error
//   QList <int> returnTimeList();


   QList <int> time;                    //list of total times

signals:
    void timeDelayPreview(QString);

public slots:
   void timeDelay();

private:

   int PreviousTime;
   QSlider *TimeSlider;





};

#endif // TIME_H



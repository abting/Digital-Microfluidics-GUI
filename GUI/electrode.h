#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <QWidget>
#include <iostream>
#include <QPushButton>
#include <Droplet.h>
#include <layout.h>

class Droplet;
class Electrode : public QPushButton
{
    Q_OBJECT
public:
    Electrode(QWidget *parent,int x,int y,std::string number);
    Electrode();
    ~Electrode();

    void set_x_position(int);
    void set_y_positon(int);
    void setNumber(std::string);
    void setState(bool);
    void setOnTime(double);
    void setOffTime(double);
    void setAvailability(int);
    void setDroplet(Droplet*);
    void removeDroplet();
    bool isEmpty();

    int get_x_position();
    int get_y_positon();
    std::string getNumber();
    bool getState();
    double getOntime();
    double getOffTime();
    int getAvailability();
    Droplet* getDroplet();
    void addNeighbor(Electrode*);
    QList<Electrode*> getNeighbors();

private:

    //neighbors surrounding the electrode top, right, bottom, left
    QList<Electrode*> neighbours;
    int x_position;
    int y_position;
    std::string number;      //number displayed on the electrode
    bool state;              //"true" for "active" and "false" for "inactive"
    int availability;        //1 for "available" and 0 for "unavailable"
    double onTime;           //how long the electrode stays on
    double offTime;          //how long the electrode stays off
    Droplet *droplet;       //refrence to the droplet it holds

signals:

public slots:

};

#endif // ELECTRODE_H

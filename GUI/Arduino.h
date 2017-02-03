#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <PathHandler.h>


class Arduino:public QSerialPort
{
    Q_OBJECT

public:

    Arduino();

    Arduino(PathHandler*, int);

    bool isConnected();

public slots:

    void Connect();
    void SendSequence();//PathHandler*, int);
    //KIWI
    void SendSingleCommand(QString, QString);
    void setPathHandler(PathHandler*);
    void setStartTime(int);
    void StopArduino(bool);
    void setIterationDelay(int);
    void setIterations(int);

signals:
    //Emited when the arduino sending information is done
    void Done();
private:

    bool stopArduino;
    PathHandler* pathHandler;
    int startTime;
    int numberOfIterations;
    unsigned IterationDelay;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name = "";
    bool arduino_is_available = false;
};

#endif // ARDUINO_H

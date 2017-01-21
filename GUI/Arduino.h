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
    void Connect();
    bool isConnected();
    void SendSequence(PathHandler *pathhandler);
    //KIWI
    void SendSingleCommand(QString, QString);

private:

    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name = "";
    bool arduino_is_available = false;
};

#endif // ARDUINO_H

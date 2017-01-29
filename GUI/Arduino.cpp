#include "Arduino.h"
#include <QSerialPortInfo>

Arduino::Arduino(){

}

void Arduino::Connect()
{
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if (serialPortInfo.hasVendorIdentifier()&& serialPortInfo.hasProductIdentifier()){
            if (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if (serialPortInfo.productIdentifier()==arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }
    if (arduino_is_available){
        this->setPortName(arduino_port_name);
        this->open(QSerialPort::ReadWrite);
        this->setBaudRate(QSerialPort::Baud9600);
        this->setDataBits(QSerialPort::Data8);
        this->setParity(QSerialPort::NoParity);
        this->setStopBits(QSerialPort::OneStop);
        this->setFlowControl(QSerialPort::NoFlowControl);
    }
    else{arduino_is_available = false;}
}


void Arduino::SendSequence(PathHandler *pathhandler, int startTime)
{
    if (this->isWritable()){
        QByteArray readData = this->readAll();
        QByteArray detectionValue_read = "2";                           //Detection value read, arduino will have to send this back as a signal for us to send the next block of electrodes
        QString detectionValue_send = "a";                              //Detection value sent, this tells arduino to stop reading (speed up processing)
        QString s_data = readData;                                      //Need to convert QByteArray info into a QString in order to compare

        for(int i = startTime; i<pathhandler->getPathList().length(); i++){     //Number of Slots
            QString infoToBeSent = pathhandler->getPathList().at(i) + "," +  detectionValue_send;        //Identifier to stop reading on the arduino end
            this->write(infoToBeSent.toStdString().c_str());         //Communicating with Arduino
            qApp->processEvents();
            //Sleep(100);
            while(readData!=detectionValue_read){
                readData = this->readAll();
                s_data = readData;
                qApp->processEvents();
            }
            readData = this->readAll();
        }
    }
    else{
        qDebug() << "Communication Error, Couldn't write to serial";
    }
}

void Arduino::SendSingleCommand(QString instruction, QString command)
{
    QString infoToBeSent;
    QString detectionValue_send = "a";
    if(instruction == "actuate"){
        infoToBeSent += "1000," + command + "," + detectionValue_send;
    }
    if (this->isWritable()){
        this->write(infoToBeSent.toStdString().c_str());
    }
    else{
        qDebug() << "Communication Error, Couldn't write to serial";
    }

}
bool Arduino::isConnected()
{
    return arduino_is_available;
}

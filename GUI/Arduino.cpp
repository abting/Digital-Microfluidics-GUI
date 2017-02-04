#include "Arduino.h"
#include <QSerialPortInfo>

Arduino::Arduino(){

    numberOfIterations = 1;
    IterationDelay = 3000;
}

Arduino::Arduino(PathHandler* pHandler, int sTime){
    pathHandler = pHandler;
    startTime = sTime ;
    numberOfIterations = 1;
    IterationDelay = 3000;


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


void Arduino::SendSequence()//PathHandler *pathhandler, int startTime)
{
    if (this->isWritable()){
        QByteArray readData = this->readAll();
        QByteArray detectionValue_read = "2";                           //Detection value read, arduino will have to send this back as a signal for us to send the next block of electrodes
        QString detectionValue_send = "a";                              //Detection value sent, this tells arduino to stop reading (speed up processing)
        QString s_data = readData;                                      //Need to convert QByteArray info into a QString in order to compare

        for (int k = 0; k<numberOfIterations;k++){
            for(int i = startTime; i<pathHandler->getPathList().length(); i++){     //Number of Slots
                QString infoToBeSent = pathHandler->getPathList().at(i) + "," +  detectionValue_send;        //Identifier to stop reading on the arduino end
                this->write(infoToBeSent.toStdString().c_str());         //Communicating with Arduino
                qApp->processEvents();
                //Sleep(100);
                while(readData!=detectionValue_read){
                    readData = this->readAll();
                    s_data = readData;
                    qApp->processEvents();
                    if(stopArduino){
                        emit Done();
                        moveToThread(qApp->thread());   //Moves the thread back to the  thread
                        return;
                    }
                }
                readData = this->readAll();
            }
            QThread::msleep(IterationDelay);          //Wait before next iteration
        }
        emit Done();
        moveToThread(qApp->thread());               //Moves the thread back to the  thread
    }
    else{
        qDebug() << "Communication Error, Couldn't write to serial";
        emit Done();
    }
}

void Arduino::SendSingleCommand(QString instruction, QString command)
{
    QString infoToBeSent;
    QString detectionValue_send = "a";
    if(instruction == "actuate"){
        infoToBeSent += "1000," + command + "," + detectionValue_send;
    }
    else if(instruction == "delay"){
        infoToBeSent += "1005," + command + "," + detectionValue_send;
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

void Arduino::setPathHandler(PathHandler * pathH){
    pathHandler = pathH;
}
void Arduino::setStartTime(int sTime){
    startTime = sTime;
}

void Arduino::StopArduino(bool stop){
    stopArduino = stop;

}

void Arduino::setIterations(int numIterations){
    numberOfIterations=numIterations;
}

void Arduino::setIterationDelay(int iterationDelay){
    IterationDelay=iterationDelay;
}

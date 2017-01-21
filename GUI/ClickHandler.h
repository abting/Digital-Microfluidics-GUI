#ifndef CLICKHANDLER_H
#define CLICKHANDLER_H

#include <QObject>
#include <electrode.h>

class ClickHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClickHandler(QObject *parent = 0);
    ClickHandler(int inputs);
    ~ClickHandler();

    void setRequiredInputs(int);
    int getRequiredInputs();
    QList<Electrode*> getElectrodeList();

private:
    QList<Electrode*> ElectrodeList;
    //Number of inputs changes depending on the task the user needs to do
    int requiredInputs;

signals:
    //Emited when the thread has recieved the number of inputs needed
    void Done();

public slots:
    void clicked();
};

#endif // CLICKHANDLER_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "electrode.h"
#include "NewLayout.h"
#include "layout.h"
#include "LayoutDesign.h"
#include <QMessageBox>
#include <Droplet.h>
#include <windows.h>



MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){

    ui->setupUi(this);

    ElectrodeLayout = ui->electrodeLayout;      //GridLayout

    //Droplet Mode Widgets
    DispenceButton = ui->DispenceButton;
    SplitButton = ui->SplitButton;
    PreviewButton = ui->PreviewButton ;
    StartButton = ui->StartButton;
    AddDroplet = ui->addDrop;
    RemoveDroplet = ui->removedrop;
    InstructonMonitor = ui->InstructonMonitor;
    BeginButton = ui->BeginButton;
    CancelButton = ui->CancelButton;
    DropletTable = ui->dropTable;
    TimeSpinner = ui->dropTime;
    CancelPreviewButton = ui->CancelPreviwButton;
    CancelStartButton = ui->CancelStartButton;
    IterationBox = ui->IterationspinBox;
    IterationDelayText = ui->IterationDelayText;
    ActuationText = ui->ActuationTimeText;
    setActuation = ui->setActuationButton;
    VoltageText = ui->VoltageText;
    setVoltage = ui->setVoltageButton;


    //Electrode Mode Widgets
    IncrementButton = ui->Increment_EmodeButton;
    TurnOnButton = ui->turnOn_EmodeButton;
    TurnOffButton = ui->turnOff_EmodeButton;
    StartEmodeButton = ui->Start_EmodeButton;
    TimeSpinnerEmode = ui->dropTimeEmode;
    DropletTableEmode = ui->dropTableEmode; 
    CancelPreviewEmodeButton = ui->CancelPreviwEmodeButton;
    RealTimeActuationButton = ui->RealTimeActuationBox;
    CancelStartEmodeButton = ui->CancelStart_EmodeButton;

    //Tab Widgets
    TabButton = ui->ModeButtonTab;
    TabTable = ui->ModeTableTab;
    TabTable->setCurrentIndex(0);
    TabButton->setCurrentIndex(0);


    //Action booleans
    DispenceMode = false;
    SplitMode = false;
    LayoutExists = false;
    turnOn = false;
    turnOff = false;
    RealTimeActuate = false;


    //Hide and Show certain buttons
    CancelButton->setEnabled(false);
    CancelButton->setVisible(false);   
    CancelPreviewButton->setEnabled(false);
    CancelPreviewButton->setVisible(false);
    CancelPreviewEmodeButton->setEnabled(false);
    CancelPreviewEmodeButton->setVisible(false);
    CancelStartButton->setEnabled(false);
    CancelStartButton->setVisible(false);
    CancelStartEmodeButton->setEnabled(false);
    CancelStartEmodeButton->setVisible(false);
    BeginButton->setEnabled(false);
    BeginButton->setVisible(false);
    StartButton->setEnabled(false);
    StartEmodeButton->setEnabled(false);
    IterationBox->setEnabled(false);
    IterationDelayText->setEnabled(false);
    ActuationText->setEnabled(false);
    setActuation->setEnabled(false);
    VoltageText->setEnabled(false);
    setVoltage->setEnabled(false);


    //Initialize Arduino and GridLayout
    InitializeUI(false);
    //arduino = new Arduino();
    mylayout = new Layout(ElectrodeLayout);
    //funcgen = new funcGen();
    IterationDelayText->setValidator(new QIntValidator(500, 10000, this));      //Set delay between iterations 0.5 and 10s
    ActuationText->setValidator(new QIntValidator(500, 10000, this));           //Set delay between actuation 0.5 and 10s
    VoltageText->setValidator(new QIntValidator(0, 10000, this));                                  //Set voltage in mV between 0 and 10000
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitializeUI(bool enable){

    //Enable buttons once the gridlayout is set
    SplitButton->setEnabled(enable);
    PreviewButton->setEnabled(enable);
    DispenceButton->setEnabled(enable);
    InstructonMonitor->setEnabled(enable);
    AddDroplet->setEnabled(enable);
    RemoveDroplet->setEnabled(enable);
    TabButton->setEnabled(enable);
    TabTable->setEnabled(enable);

    //Initiliaze Table and reset function if layout is already created
    InitializeTable();
    InitializeTableEmode();
    if(listdrop.length()>0){
        qDeleteAll(listdrop.begin(), listdrop.end());
    }
    listdrop.clear();

    time = new Time(tableDmode->getSlider());
    timeEmode = new Time(tableEmode->getSlider());
}

void MainWindow::connectSignals(){

    int totalColumns = ElectrodeLayout->columnCount();
    int totalRows = ElectrodeLayout->rowCount();
    for(int i=0; i<totalRows;i++){
        for(int j=0; j<totalColumns;j++){
            QLayoutItem* item = ElectrodeLayout->itemAtPosition(i,j);
            if(item){
                QWidget* widget = item->widget();
                Electrode* electrode = dynamic_cast<Electrode*>(widget);
                connect(electrode,SIGNAL(clicked()),this,SLOT(ProcessClick()));
            }
        }
    }
}

void MainWindow::ProcessClick(){
    Electrode *electrode = qobject_cast<Electrode*>(QObject::sender());

    if(AddDroplet->isChecked()){                    //if "add droplet" option is selected
        if(electrode->isEmpty()){
            Droplet *NewDroplet = new Droplet(tableDmode->getSlider()->value());
            while(NewDroplet->isDupliate(listdrop)){
                QMessageBox::warning(this,tr("Duplicate Name"), tr("Please choose a unique name"));
                NewDroplet = new Droplet(tableDmode->getSlider()->value());
            }
            if(NewDroplet->Selected){
                electrode->setDroplet(NewDroplet);
                electrode->setToolTip("Name: " + NewDroplet->getName() + "\nVolume: " + QString::number(NewDroplet->getVolume()));
                electrode->getDroplet()->updateInfo(electrode->text(), tableDmode->getSlider()->value(), electrode, "update");
                listdrop.append(NewDroplet);
                addDropToTable(NewDroplet);
                InstructonMonitor->setPlainText("Added Droplet '" + NewDroplet->getName() + "' to electrode: " + electrode->text());
            }
        }
    }
    else if(RemoveDroplet->isChecked()){           //if the "Remove droplet" option is selected
        if(!(electrode->isEmpty())){
            Droplet* removeDrop = electrode->getDroplet();
            InstructonMonitor->setPlainText("Removed Droplet '" + removeDrop->getName() + "'");
            listdrop.removeOne(removeDrop);
            removeDropFromTable(removeDrop);
            electrode->removeDroplet();
            RemoveDroplet->setChecked(false);
            delete removeDrop;
        }
    }
    else if(SplitMode){}
    else if(DispenceMode){}
    else if(turnOn){
        electrode->setStyleSheet("background-color: blue");
        tableEmode->updateTableEmode("add",electrode);
        InstructonMonitor->setPlainText("Turned on Electrode:" + electrode->text());
    }
    else if (turnOff){
        electrode->setStyleSheet("background-color: grey");
        tableEmode->updateTableEmode("remove",electrode);
        InstructonMonitor->setPlainText("Turned off Electrode:" + electrode->text());
    }
    else if(RealTimeActuate){
        if(arduino->isConnected() && arduino->isWritable()){
            arduino->SendSingleCommand("actuate", electrode->text());
        }
        else{
            printToInstructionMonitor("Communication Error\nArduino is not connected or is busy");
        }
    }
    else{                                              //if the user just want to move the droplet
        time->setPreviousTime();
        time->increaseTime(TimeSpinner);
        mylayout->CheckSurroundingElectrodes(electrode,time->CurrentTime());
        if(electrode->getDroplet()){
            updateTable(electrode);
        }
        timeChange(8);
        selectColumn(tableDmode->getSlider()->value());
        InstructonMonitor->setPlainText("Electrode " + electrode->text() + " was clicked");
    }
}

void MainWindow::printToInstructionMonitor(string words){
    QString text = QString::fromStdString(words);
    InstructonMonitor->setPlainText(text);
}

void MainWindow::getUserInput(int input){

    clickhandler = new ClickHandler(input);
    thread = new QThread;


    int totalColumns = ElectrodeLayout->columnCount();
    int totalRows = ElectrodeLayout->rowCount();
    for(int i=0; i<totalRows;i++){
        for(int j=0; j<totalColumns;j++){
            QLayoutItem* item = ElectrodeLayout->itemAtPosition(i,j);
            if(item){
                QWidget* widget = item->widget();
                Electrode* electrode = dynamic_cast<Electrode*>(widget);
                connect(electrode,SIGNAL(clicked()),clickhandler,SLOT(clicked()));
            }
        }
    }

    clickhandler->moveToThread(thread);
    connect(clickhandler, SIGNAL(Done()), this, SLOT(ProcessEvents()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void MainWindow::ProcessEvents(){
    QList<Electrode*> listOfElectrodes = clickhandler->getElectrodeList();

//    clickhandler->deleteLater();          ABTIN REMOVED THIS
//    thread->deleteLater();

    if(DispenceMode){
        DispenceButton->setEnabled(true);
        DispenceDroplet(listOfElectrodes);
    }
    if(SplitMode){
        SplitButton->setEnabled(true);
        SplitDroplet(listOfElectrodes);
    }
}

void MainWindow::DispenceDroplet(QList<Electrode*> elecList){

    CancelButton->setVisible(false);
    CancelButton->setEnabled(false);
    SplitButton->setEnabled(true);          //Abtin set this
    DispenceButton->setEnabled(true);
    DispenceMode = false;

    Electrode *last;
    Electrode* current;
    Droplet *reservoir = elecList.at(0)->getDroplet();

    //if there is a droplet on the first electrode continute
    if(elecList.at(0)->getAvailability() == 0 ){
    //if the electrodes are not empty at any point, break
        foreach(Electrode* elec, elecList){
            if(elec->getAvailability() == 0 && elec->getDroplet() != reservoir){
                QMessageBox::warning(this,tr("Warning"), tr("The chosen dispencing path has additional droplets on it"));
                return;
            }
        }
        for(int i=0; i<elecList.size()-1; i++){
            last = elecList.at(i);
            current = elecList.at(i+1);
            int sharedNeighbor = 0;
            //check through all the naighbors of each electrode and see if they are adjacent
            foreach(Electrode* elec, current->getNeighbors()){
                if(elec == last){
                    sharedNeighbor++;
                }
            }
            if(sharedNeighbor != 1){
                QMessageBox::warning(this,tr("Warning"), tr("The electrodes you have chosen are not adjacant to one another"));
                printToInstructionMonitor("Dispensing was unsuccessful");
                return;
            }
            sharedNeighbor = 0;
        }
        //at this point everything should be ok, else the function should have broken out of the loop

        //Create the two first timeslots, actuate the reservoir, then add a droplet to the adjacent electrode (second user input)
        time->setPreviousTime();
        time->increaseTime(TimeSpinner);
        Droplet* initialDrop = elecList.at(0)->getDroplet();
        initialDrop->updateInfo(elecList.at(0)->text(),time->CurrentTime(),elecList.at(0),"update");
        updateTable(elecList.at(0));
        timeChange(8);
        time->setPreviousTime();
        time->increaseTime(TimeSpinner);
        Droplet* drop = new Droplet(elecList.at(0)->getDroplet()->getName()+ "-D",elecList.at(0)->getDroplet()->getColor(),1,time->CurrentTime());
        drop->updateInfo(elecList.at(1)->text(),time->CurrentTime(),elecList.at(1),"update");
        elecList.at(1)->setDroplet(drop);
        listdrop.append(drop);
        addDropToTable(drop);
        timeChange(8);

        //Add the remaining electrodes to the path of the newly created droplet (subsequent user inputs)
        for(int i = 2; i<elecList.size();i++){
            time->setPreviousTime();
            time->increaseTime(TimeSpinner);
            elecList.at(i)->setDroplet(drop);
            drop->updateInfo(elecList.at(i)->text(),time->CurrentTime(),elecList.at(i),"update");
            updateTable(elecList.at(i));
            timeChange(8);
        }

        //Update the reservoir to actuate simulatenously, this breaks off the two droplets

        elecList.at(0)->setDroplet(initialDrop);
        initialDrop->updateInfo(elecList.at(0)->text(),time->CurrentTime(),elecList.at(0),"update");
        updateTable(elecList.at(0));
        selectColumn(tableDmode->getSlider()->value());
        printToInstructionMonitor("Dispensing was successful");
    }
    else{
        QMessageBox::warning(this,tr("Warning"), tr("There is no droplet on the first Electrode"));
    }
}

//list with 3 Elements, first being the electrode with the droplet followed by two adjacent electrodes
void MainWindow::SplitDroplet(QList<Electrode*> elecList){

    CancelButton->setVisible(false);
    CancelButton->setEnabled(false);

    SplitButton->setEnabled(true);
    DispenceButton->setEnabled(true);
    SplitMode = false;

    Electrode* parent = elecList.at(0);
    int sharedNeighbor = 0;
    //Droplet* temp;
    //if there is a droplet on the first electrode
    if(parent->getAvailability() == 0){
        Droplet* temp = parent->getDroplet();
        bool fail = false;

        if(parent == elecList.at(1) || parent == elecList.at(2) || elecList.at(1) == elecList.at(2)){
            QMessageBox::warning(this,tr("Warning"), tr("Split failed, you have selected the same electrode more than once"));
            return;
        }
        foreach(Electrode* elec, elecList.at(1)->getNeighbors()){
            if(elec == parent){
                sharedNeighbor++;
            }
            if(elec->getAvailability() == 0 ){
                if(elec->getDroplet() != temp){
                    QMessageBox::warning(this,tr("Warning"), tr("Split failed, there are more droplets around"));
                    fail = true;
                    return;
                }
            }
        }
        if(sharedNeighbor != 1){
            QMessageBox::warning(this,tr("Warning"), tr("Electrode 1 is not adajecnt to the parent droplet"));
            return;
        }
        sharedNeighbor =0;
        foreach(Electrode* elec, elecList.at(2)->getNeighbors()){
            if(elec == parent){
                sharedNeighbor++;
            }
            if(elec->getAvailability() == 0 ){
                if(elec->getDroplet() != temp ){
                    QMessageBox::warning(this,tr("Warning"), tr("Split failed, there are more droplets around"));
                    fail = true;
                    return;
                }
            }
        }
        if(sharedNeighbor != 1){
            QMessageBox::warning(this,tr("Warning"), tr("Electrode 2 is not adajecnt to the parent droplet"));
            return;
        }
        if(!fail){

            //if all the surrounding electrodes are empty, create two new droplets
            time->increaseTime(TimeSpinner);
            Droplet* split1 = new Droplet(temp->getName()+"-S1",temp->getColor(),temp->getVolume()/2, tableDmode->getSlider()->value());
            split1->updateInfo(elecList.at(1)->text(),time->CurrentTime(),elecList.at(1),"update");
            elecList.at(1)->setDroplet(split1);
            listdrop.append(split1);
            addDropToTable(split1);

            Droplet* split2 = new Droplet(temp->getName()+"-S2",temp->getColor(),temp->getVolume()/2, tableDmode->getSlider()->value());
            split2->updateInfo(elecList.at(2)->text(),time->CurrentTime(),elecList.at(2),"update");
            elecList.at(2)->setDroplet(split2);
            listdrop.append(split2);
            addDropToTable(split2);

            //Remove access to the droplet that was used to be split
            parent->getDroplet()->updateInfo("", time->CurrentTime(), parent, "split");
            parent->removeDroplet();
            cout<<listdrop.size()<<endl;
        }
    }
    else{
        QMessageBox::warning(this,tr("Warning"), tr("No droplet was selected!"));
    }
}

void MainWindow::on_StartButton_clicked()
{
    DisableSignals();
    pathHandler = new PathHandler(listdrop);
    pathHandler->setPathList();

    arduino->setPathHandler(pathHandler);
    arduino->setStartTime(tableDmode->getSlider()->value());
    arduino->StopArduino(false);
    arduino->setIterations(IterationBox->value());
    arduino->setIterationDelay(IterationDelayText->text().toInt());


    if(arduino->isConnected()){
        CancelStartButton->setEnabled(true);
        CancelStartButton->setVisible(true);

        QThread* threadArduinoDmode = new QThread;
        connect(threadArduinoDmode, SIGNAL(started()), arduino, SLOT(SendSequence()));
        connect(arduino,SIGNAL(Done()),this, SLOT(on_CancelStartButton_clicked()));
        connect(this,SIGNAL(stopArduino(bool)),arduino, SLOT(StopArduino(bool)));
        connect(this,SIGNAL(deleteArduinoThread()),threadArduinoDmode, SLOT(deleteLater()));
        connect(threadArduinoDmode, SIGNAL(finished()), threadArduinoDmode, SLOT(deleteLater()));

        arduino->moveToThread(threadArduinoDmode);
        InstructonMonitor->setPlainText("Starting from time slot: " + QString::number(tableDmode->getSlider()->value()));
        threadArduinoDmode->start();
    }
    else{
        StartButton->setEnabled(false);
        QMessageBox::warning(this,tr("Arduino"), tr("WARNING! Arduino not Connected!"));
    }
}

void MainWindow::on_SplitButton_clicked()
{
    printToInstructionMonitor("Please click on the droplet you want to split\n");
    CancelButton->setVisible(true);
    CancelButton->setEnabled(true);
    DispenceButton->setEnabled(false);
    SplitMode = true;
    getUserInput(3);
}

void MainWindow::on_PreviewButton_clicked()
{
    CancelPreviewButton->setEnabled(true);
    CancelPreviewButton->setVisible(true);
    Preview(tableDmode,time, true);
    CancelPreviewButton->setEnabled(false);
    CancelPreviewButton->setVisible(false);
}

void MainWindow::on_DispenceButton_clicked()
{
    printToInstructionMonitor("Please click on the droplet that you want to dispense from.\n\nThen, choose the adjacent electrodes the droplet\n"
                              "will dispense on\n\nAfter that, click on Begin Dispensing");
    DisableSignals();
    //TODO ASK USER FOR NUMBER OF INPUTS OR USE A VECTOR
    BeginButton->setEnabled(true);
    BeginButton->setVisible(true);
    CancelButton->setVisible(true);
    CancelButton->setEnabled(true);
    SplitButton->setEnabled(false);
    DispenceMode = true;
    getUserInput(1000);
}

void MainWindow::on_New_Layout_triggered(){

    LayoutDesign *layoutdesign = new LayoutDesign();
    layoutdesign->exec();

    if(layoutdesign->Done){
        if(ElectrodeLayout->count() != 0) mylayout->ClearLayout();
    LayoutExists = true;

    int column = layoutdesign->getColumns();
    int row = layoutdesign->getRows();

    mylayout = new Layout(ElectrodeLayout,row,column);
    mylayout->InsertDesign(layoutdesign->returnDesign());

    InitializeUI(true);
    connectSignals();
    connect(mylayout, SIGNAL(addDropletFromLayout(Droplet*)), this, SLOT(addDropToTable(Droplet*)));
    connect(mylayout, SIGNAL(addDropletFromLayout(Droplet*)), this, SLOT(addToDList(Droplet*)));
    mylayout->Neighbors();
    }
}

void MainWindow::on_CancelButton_clicked()
{
    printToInstructionMonitor("Input canceled by user\n");
    clickhandler->deleteLater();
    thread->deleteLater();
    delete clickhandler;

    SplitMode = false;
    DispenceMode = false;
    SplitButton->setEnabled(true);
    DispenceButton->setEnabled(true);
    CancelButton->setVisible(false);
    CancelButton->setEnabled(false);
    BeginButton->setEnabled(false);
    BeginButton->setVisible(false);
}

void MainWindow::on_Connect_triggered()
{
    arduino = new Arduino();
    arduino->Connect();
    if(arduino->isConnected()){
        StartButton->setEnabled(true);
        StartEmodeButton->setEnabled(true);
        IterationBox->setEnabled(true);
        IterationDelayText->setEnabled(true);
        ActuationText->setEnabled(true);
        setActuation->setEnabled(true);
        printToInstructionMonitor("Arduino Connected!");
    }else{
        StartButton->setEnabled(false);
        StartEmodeButton->setEnabled(false);
        QMessageBox::warning(this,tr("Arduino"), tr("WARNING! Arduino not Connected!"));
    }
}

void MainWindow::on_Save_Layout_triggered(){
    if(ElectrodeLayout->count() != 0)
        mylayout->SaveLayout(this);
    else QMessageBox::warning(this,tr("Save Error"), tr("There is no layout to save!"));
}

void MainWindow::on_Open_Layout_triggered(){

    mylayout->OpenLayout(this,ElectrodeLayout);
    if(ElectrodeLayout->count() != 0){
        LayoutExists = true;
        AddDroplet->setEnabled(true);
        RemoveDroplet->setEnabled(true);

        InitializeUI(true);
        connectSignals();
        connect(mylayout, SIGNAL(addDropletFromLayout(Droplet*)), this, SLOT(addDropToTable(Droplet*)));
        connect(mylayout, SIGNAL(addDropletFromLayout(Droplet*)), this, SLOT(addToDList(Droplet*)));
        mylayout->Neighbors();
    }
}

void MainWindow::InitializeTable()
{
    //Setup Tables
    TimeSpinner->setMinimum(0);
    TimeSpinner->setValue(0);
    DropletTable->clear();
    tableDmode = new Table(DropletTable);
    tableDmode->CreateTable(this);
    ui->currentStepText->setText(QString::number(0));
}

void MainWindow::InitializeTableEmode()
{
    //Setup Tables
    TimeSpinnerEmode->setMinimum(0);
    TimeSpinnerEmode->setValue(0);
    DropletTableEmode->clear();
    tableEmode = new Table(DropletTableEmode);
    tableEmode->InitializeTableEmode(this);
    ui->currentStepText_Emode->setText(QString::number(0));
}
void MainWindow::addDropToTable(Droplet *drop)
{
    tableDmode->addDropToTable(drop,listdrop,time->CurrentTime());
}

void MainWindow::removeDropFromTable(Droplet *drop)
{
    tableDmode->removeDropFromTable(drop);
}

void MainWindow::updateTable(Electrode *elec)
{
    tableDmode->updateTable(elec,time->CurrentTime());
}

void MainWindow::on_dropTime_valueChanged(int arg1)
{
    SpinboxValueChanged(arg1, tableDmode, TimeSpinner, 2);
}

//This is called when you're scrolling through time using the slider
//It ensures that you set droplets at their specified time
void MainWindow::selectColumn(int value)        //Value is the value of the tableslider
{
    if(TabButton->currentIndex()==0){
        ui->currentStepText->setText(QString::number(value));
        foreach(Droplet* drop, listdrop){
            //First check if the Time to be checked is contained in the droplet Information
            //If it isn't then set Time to be checked to be it's last index
            int evaluatedTime = value;
            if(value<=drop->getDropletInfo().length()-1){
            }
            else{
                if(drop->getDropletInfo().length()>0){
                    evaluatedTime = drop->getDropletInfo().length()-1;
                }
            }
            //If the droplet information contains an electrode at that given time, set the droplet to that electrode
            //If it is supposed to be merged, absent or split at that given time, do not set the droplet
            foreach(Info inf, drop->getDropletInfo()){
                if(inf.time == evaluatedTime){
                    if(inf.status!="merged" && inf.status != "absent" && inf.status!= "split"){
                            inf.elec->setDroplet(drop);        
                   }
                }
            }
        }
    }
    else if(TabButton->currentIndex()==1){
        ui->currentStepText_Emode->setText(QString::number(value));
        //Access the electrodes based on their numbers, set their color to blue indicating that they're turned on
        for(int i = 2; i<tableEmode->getRow();i++){
            if(tableEmode->getItem(i,tableEmode->getSlider()->value()+1)){
                Electrode* el = mylayout->elecFromText(tableEmode->getItem(i,tableEmode->getSlider()->value()+1)->text());
                el->setStyleSheet("background-color:blue");
            }
        }
    }
}

//Remove droplets from their electrodes at the specified time
//This is called when you're scrolling through time, it ensures that you remove droplets at previous times
void MainWindow::timeChange(int value)
{
    if(value >= 1 && value <= 8){
        if(value!=8){
            time->setPreviousTime();
        }
        if(TabButton->currentIndex() == 0){
            int evaluatedTime;
            //Remove droplets from all previous times
            //If the droplet doesn't contain information at the specified time, set the evaluated time to be the last index
            foreach(Droplet* drop, listdrop){
                if(time->getPreviousTime() > drop->getDropletInfo().length()-1){
                    evaluatedTime = drop->getDropletInfo().length()-1;
                }
                else{
                    evaluatedTime = time->getPreviousTime();
                }
                //If the has an associated electrode at that time, remove it from that electrode
                foreach(Info inf, drop->getDropletInfo()){
                    if(inf.status!="merged" && inf.status!="absent" && inf.status!="split" && inf.time == evaluatedTime){
                       if(inf.elec->getDroplet()){
                           inf.elec->removeDroplet();
                        }
                    }
                }
            }
        }
        else if (TabButton->currentIndex() == 1){
            //If the has an associated electrode at that time, set that electrode to grey (turned off)
            for(int i = 2; i<tableEmode->getRow();i++){
                if(tableEmode->getItem(i,tableEmode->getSlider()->value()+1)){              //Need to account for +1 offset in the table
                    Electrode* el = mylayout->elecFromText(tableEmode->getItem(i,tableEmode->getSlider()->value()+1)->text());
                    el->setStyleSheet("background-color:grey");
                }
            }
        }
    }
}

void MainWindow::addToDList(Droplet* addD){
    listdrop.append(addD);
}


void MainWindow::on_BeginButton_clicked()
{
    clickhandler->Done();
    BeginButton->setVisible(false);
    BeginButton->setEnabled(false);
    CancelButton->setVisible(false);
    CancelButton->setEnabled(false);
}

void MainWindow::on_Increment_EmodeButton_clicked()
{
    timeEmode->setPreviousTime();
    timeChange(8);
    timeEmode->increaseTime(TimeSpinnerEmode);
}



void MainWindow::on_Start_EmodeButton_clicked()
{

    DisableSignals();
    pathHandler = new PathHandler();
    pathHandler->setPathListEmode(tableEmode);

    arduino->setPathHandler(pathHandler);
    arduino->setStartTime(tableEmode->getSlider()->value());
    arduino->StopArduino(false);
    arduino->setIterations(IterationBox->value());
    arduino->setIterationDelay(IterationDelayText->text().toInt());


    if(arduino->isConnected()){
        CancelStartEmodeButton->setEnabled(true);
        CancelStartEmodeButton->setVisible(true);

        QThread* threadArduinoEmode = new QThread;
        connect(threadArduinoEmode, SIGNAL(started()), arduino, SLOT(SendSequence()));
        connect(arduino,SIGNAL(Done()),this, SLOT(on_CancelStart_EmodeButton_clicked()));
        connect(this,SIGNAL(stopArduino(bool)),arduino, SLOT(StopArduino(bool)));
        connect(this,SIGNAL(deleteArduinoThread()),threadArduinoEmode, SLOT(deleteLater()));
        connect(threadArduinoEmode, SIGNAL(finished()), threadArduinoEmode, SLOT(deleteLater()));

        arduino->moveToThread(threadArduinoEmode);
        InstructonMonitor->setPlainText("Starting from time slot: " + QString::number(tableEmode->getSlider()->value()));
        threadArduinoEmode->start();
    }
    else{
        StartButton->setEnabled(false);
        QMessageBox::warning(this,tr("Arduino"), tr("WARNING! Arduino not Connected!"));
    }
}

void MainWindow::on_turnOn_EmodeButton_clicked(bool checked)
{
    DisableSignals();
    if(checked){
        TurnOnButton->setChecked(true);
        turnOn = true;
    }
}

void MainWindow::on_turnOff_EmodeButton_clicked(bool checked)
{
    DisableSignals();
    if(checked){
        TurnOffButton->setChecked(true);
        turnOff = true;
    }
}

void MainWindow::DisableSignals(){
    DispenceMode = false;
    SplitMode = false;
    turnOn = false;
    turnOff = false;   
    RealTimeActuate = false;
    TurnOnButton->setChecked(false);
    TurnOffButton->setChecked(false);
    AddDroplet->setChecked(false);
    RemoveDroplet->setChecked(false);
    RealTimeActuationButton->setChecked(false);

}

void MainWindow::on_ModeButtonTab_tabBarClicked(int index)
{
    //When changing tabs, clear the colors of the layout
    mylayout->ResetColors();
    DisableSignals();
    if(index==0){
        TabTable->setCurrentIndex(0);
    }
    else if(index==1){
        TabTable->setCurrentIndex(1);
        TurnOnButton->setChecked(true);
        turnOn = true;
    }
}

void MainWindow::on_ModeTableTab_tabBarClicked(int index)
{
    mylayout->ResetColors();
    DisableSignals();
    if(index==0){
        TabButton->setCurrentIndex(0);
    }
    else if(index==1){
        TabButton->setCurrentIndex(1);
        TurnOnButton->setChecked(true);
        turnOn = true;
    }
}

void MainWindow::SpinboxValueChanged(int value, Table* table,QSpinBox* timespin, int offset){
    //Increase the size of the table according to the TimeSpinner
    int origCol = table->getColumn();
    int increaseSize = 0;
    if (value+offset >= table->getColumn()){         //Need to account for +1 offset in the columns
        table->setColumn(value+(offset+1));
        for (int i=origCol;i<table->getColumn();i++){
            table->setColumnW(i,25);
            increaseSize +=25;
        }
        //Increase Span of headers and Slider, increase size of Slider accordingly
        table->setSp(1,offset,1,table->getColumn()-1);
        table->setSp(0,offset,1,table->getColumn()-1);
        table->getSlider()->setMaximum(table->getColumn()-(offset+1));
    }
    timespin->setMinimum(value);
}

void MainWindow::on_dropTimeEmode_valueChanged(int arg1)
{
    SpinboxValueChanged(arg1, tableEmode, TimeSpinnerEmode, 1);
}

void MainWindow::on_addDrop_clicked(bool checked)
{
    DisableSignals();
    if(checked){
        AddDroplet->setChecked(true);
    }
}

void MainWindow::on_removedrop_clicked(bool checked)
{
    DisableSignals();
    if(checked){
        RemoveDroplet->setChecked(true);
    }
}

void MainWindow::Preview(Table* tablemode, Time* timemode, bool Dmode)
{    
    CancelpreviewEMode = false;
    CancelpreviewMode = false;
    Time* preview = new Time(tablemode->getSlider());
    QThread* threadPreview = new QThread;
    QLabel* tempLabel = new QLabel();
    int previewSpeed  = 500;  //500ms

    preview->moveToThread(threadPreview);
    connect(this, SIGNAL(increment()), preview, SLOT(timeDelay()));
    connect(preview, SIGNAL(timeDelayPreview(QString)), tempLabel, SLOT(setText(QString)));
    connect(threadPreview, SIGNAL(finished()), threadPreview, SLOT(deleteLater()));
    threadPreview->start();
    InstructonMonitor->setPlainText("Preview started at a refresh rate of " + QString::number(previewSpeed) + " ms");

    //First bring the slider back to 0, remove the droplets at the last slider position
    timemode->setPreviousTime();
    timeChange(8);
    tablemode->getSlider()->setValue(0);

    //Start incrementing the TableSlider, add and remove droplets in the process
    int k = 0;
    while(k<=tablemode->getSlider()->maximum()){
        timemode->setPreviousTime();
        if(!Dmode){
            timeChange(8);
            if(CancelpreviewEMode){
                threadPreview->deleteLater();
                return;
            }
        }
        tablemode->getSlider()->setValue(k);
        if(Dmode){
            timeChange(8);
            if(CancelpreviewMode){
                threadPreview->deleteLater();
                return;
            }
        }
        selectColumn(tablemode->getSlider()->value());
        emit increment();
        qApp->processEvents();
        k = tempLabel->text().toInt();
    }
    threadPreview->deleteLater();
}


void MainWindow::on_preview_EmodeButton_clicked()
{
    CancelPreviewEmodeButton->setEnabled(true);
    CancelPreviewEmodeButton->setVisible(true);
    Preview(tableEmode,timeEmode, false);
    CancelPreviewEmodeButton->setEnabled(false);
    CancelPreviewEmodeButton->setVisible(false);
}

void MainWindow::on_Save_Sequence_triggered()
{
    if(TabButton->currentIndex()==0){
        mylayout->saveDroplets(this,listdrop);
    }
    else if(TabButton->currentIndex()==1){
        mylayout->saveElectrodeModeSequence(this,tableEmode);
    }
    //TODO if they load a list in the middle-->reset first
    //FIXME does not work as intended
   //QList<Droplet*> test = mylayout->openDroplets(this);
   //mylayout->saveDroplets(this,test);
}

void MainWindow::on_Open_Sequence_triggered()
{    if(TabButton->currentIndex()==0){

        QList<Droplet*> temp;
        mylayout->ResetColors();
        temp = mylayout->openDroplets(this);
        if(!temp.isEmpty()){
            listdrop.clear();
            listdrop = temp;
            InitializeTable();
            time = new Time(tableDmode->getSlider());

//            foreach(Droplet *a , listdrop){
//                //InstructonMonitor->insertPlainText(QString::number(b.status) + " , ");
//                //InstructonMonitor->insertPlainText(a->getName());
//                foreach (Info b, a->getDropletInfo()){
//                    //InstructonMonitor->insertPlainText(b.status + " , ");
//                    //InstructonMonitor->insertPlainText(b.position + " , ");
//                    //InstructonMonitor->insertPlainText(QString::number(b.time) + " , ");
//                }
//                InstructonMonitor->insertPlainText("\n");
//            }
            int tableLength =1;
            foreach(Droplet* drop,listdrop){
                if(tableLength < drop->getDropletInfo().length()){
                    tableLength = drop->getDropletInfo().length();
                }
            }
            TimeSpinner->setValue(tableLength-1);
            if(!listdrop.isEmpty()){
                tableDmode->setupDroplets(listdrop);
            }
        }
    }
    else if(TabButton->currentIndex()==1){
        InitializeTableEmode();
        mylayout->ResetColors();
        timeEmode = new Time(tableEmode->getSlider());
        connect(mylayout,SIGNAL(setColumn(int)),this,SLOT(setupOpenSequenceEmode(int)));
        mylayout->openElectrodeModeSequence(this,tableEmode);
    }
}


void MainWindow::on_CancelPreviwEmodeButton_clicked()
{
    CancelpreviewEMode = true;
    CancelPreviewEmodeButton->setEnabled(false);
    CancelPreviewEmodeButton->setVisible(false);    
    printToInstructionMonitor("Input canceled by user\n");
}

void MainWindow::on_CancelPreviwButton_clicked()
{
    CancelpreviewMode = true;
    CancelPreviewButton->setEnabled(false);
    CancelPreviewButton->setVisible(false);    
    printToInstructionMonitor("Input canceled by user\n");
}

void MainWindow::on_RealTimeActuationBox_clicked(bool checked)
{
    DisableSignals();
    if(checked){
        RealTimeActuationButton->setChecked(true);
        RealTimeActuate = true;
    }
}

void MainWindow::on_CancelStartButton_clicked()
{
    CancelStartButton->setEnabled(false);
    CancelStartButton->setVisible(false);
    arduino->StopArduino(true);
    emit stopArduino(true);
    emit deleteArduinoThread();
}

void MainWindow::on_CancelStart_EmodeButton_clicked()
{
    CancelStartEmodeButton->setEnabled(false);
    CancelStartEmodeButton->setVisible(false);
    arduino->StopArduino(true);
    emit stopArduino(true);
    emit deleteArduinoThread();
}

void MainWindow::on_setActuationButton_clicked()
{
    if(arduino->isConnected() && arduino->isWritable()){
        InstructonMonitor->setPlainText("The actuation time was set to: " + ActuationText->text() + " ms");
        arduino->SendSingleCommand("delay", ActuationText->text());
    }
    else{
        printToInstructionMonitor("Communication Error\nArduino is not connected or is busy");
    }
}

void MainWindow::on_setVoltageButton_clicked()
{
    float voltageValue = VoltageText->text().toFloat();
    InstructonMonitor->setPlainText("The voltage was set to: " + QString::number(voltageValue) + " mV");
    //funcgen->send_funcgenInfo(1,voltageValue,0);
}

void MainWindow::setupOpenSequenceEmode(int value)
{
    SpinboxValueChanged(value, tableEmode, TimeSpinnerEmode, 1);
}

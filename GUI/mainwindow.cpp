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

    //Electrode Mode Widgets
    IncrementButton = ui->Increment_EmodeButton;
    TurnOnButton = ui->turnOn_EmodeButton;
    TurnOffButton = ui->turnOff_EmodeButton;
    StartEmodeButton = ui->Start_EmodeButton;
    TimeSpinnerEmode = ui->dropTimeEmode;
    DropletTableEmode = ui->dropTableEmode;

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


    //Hide and Show certain buttons
    CancelButton->setEnabled(false);
    CancelButton->setVisible(false);
    BeginButton->setEnabled(false);
    BeginButton->setVisible(false);
    StartButton->setEnabled(true);


    //Initialize Tables, Arduino and GridLayout
//    InitializeTable();
    InitializeUI(false);
    arduino = new Arduino();
    mylayout = new Layout(ElectrodeLayout);
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

    InitializeTable();
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
    //TODO add to path
    Electrode *electrode = qobject_cast<Electrode*>(QObject::sender());

    if(AddDroplet->isChecked()){                    //if "add droplet" option is selected
        if(electrode->isEmpty()){
            Droplet *NewDroplet = new Droplet(tableDmode->getSlider()->value());
            if(NewDroplet->Selected){
                electrode->setDroplet(NewDroplet);
                electrode->setToolTip("Name: " + NewDroplet->getName() + "\nVolume: " + QString::number(NewDroplet->getVolume()));
                electrode->getDroplet()->updateInfo(electrode->text(), tableDmode->getSlider()->value(), electrode, "update");
                //TODO NEW
                listdrop.append(NewDroplet);
                addDropToTable(NewDroplet);
            }
        }
    }
    else if(RemoveDroplet->isChecked()){           //if the "Remove droplet" option is selected
        if(!(electrode->isEmpty())){
            listdrop.removeOne(electrode->getDroplet());
            removeDropFromTable(electrode->getDroplet());
            electrode->removeDroplet();
        }
    }
    else if(SplitMode){}
    else if(DispenceMode){}
    else if(turnOn){
        electrode->setStyleSheet("background-color: blue");
        tableEmode->updateTableEmode("add",electrode);
    }
    else if (turnOff){
        electrode->setStyleSheet("background-color: grey");
        tableEmode->updateTableEmode("remove",electrode);
    }
    else{                                              //if the user just want to move the droplet
        //TODO NEW
        time->setPreviousTime();
        time->increaseTime(TimeSpinner);
        mylayout->CheckSurroundingElectrodes(electrode,time->CurrentTime());
        if(electrode->getDroplet()){
            updateTable(electrode->getDroplet());
        }
        timeChange(8);
        selectColumn(tableDmode->getSlider()->value());
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

    clickhandler->deleteLater();
    thread->deleteLater();

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
        updateTable(initialDrop);
        timeChange(8);
        time->setPreviousTime();
        time->increaseTime(TimeSpinner);
        Droplet* drop = new Droplet(elecList.at(0)->getDroplet()->getName()+ "-D",elecList.at(0)->getDroplet()->getColor(),1111111,time->CurrentTime());
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
            updateTable(elecList.at(i)->getDroplet());
            timeChange(8);
        }

        //Update the reservoir to actuate simulatenously, this breaks off the two droplets
        initialDrop->updateInfo(elecList.at(0)->text(),time->CurrentTime(),elecList.at(0),"update");
        updateTable(initialDrop);
        selectColumn(tableDmode->getSlider()->value());
        QMessageBox::warning(this,tr("DONE"), tr("DONE!"));
    }
    else{
        QMessageBox::warning(this,tr("Warning"), tr("There is no droplet on the first Electrode"));
    }
}

//BANANA
//list with 3 Elements, first being the electrode with the droplet followed by two adjacent electrodes
void MainWindow::SplitDroplet(QList<Electrode*> elecList){

    CancelButton->setVisible(false);
    CancelButton->setEnabled(false);

    Droplet* temp;
    //if there is a droplet on the first electrode
    if(elecList.at(0)->getAvailability() == 0){
        temp = elecList.at(0)->getDroplet();
        bool fail = false;

        foreach(Electrode* elec, elecList.at(1)->getNeighbors()){
            if(elec->getAvailability() == 0 ){
                if(elec->getDroplet() != temp){
                    QMessageBox::warning(this,tr("Warning"), tr("split failed, there are more droplets around"));
                    fail = true;
                }
            }
        }
        foreach(Electrode* elec, elecList.at(2)->getNeighbors()){
            if(elec->getAvailability() == 0 ){
                if(elec->getDroplet() != temp ){
                    QMessageBox::warning(this,tr("Warning"), tr("split failed, there are more droplets around"));
                    fail = true;
                }
            }
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
            elecList.at(0)->getDroplet()->updateInfo("", time->CurrentTime(), elecList.at(0), "split");
            elecList.at(0)->removeDroplet();
            cout<<listdrop.size()<<endl;

            //finish splitting mode
            SplitMode = false;
        }
    }
    else{
        QMessageBox::warning(this,tr("Warning"), tr("No droplet was selected!"));
    }
}

void MainWindow::on_StartButton_clicked()
{
    //KIWI
    //if(arduino->isConnected()){
    //For display purposes only
        pathHandler = new PathHandler(listdrop);      
        pathHandler->setPathList();
        if(pathHandler->getPathList().length()>0){
            for(int i = 0; i<pathHandler->getPathList().length(); i++){
                InstructonMonitor->insertPlainText(pathHandler->getPathList().at(i));
                qApp->processEvents();
                Sleep(700);
                InstructonMonitor->clear();
            }
        }
        arduino->SendSequence(pathHandler);
    //  }
    /*
    else{
        StartButton->setEnabled(false);
        QMessageBox::warning(this,tr("Arduino"), tr("WARNING! Arduino not Connected!"));
    }
    */
}

void MainWindow::on_SplitButton_clicked()
{
    printToInstructionMonitor("Please click on the droplet you want to split\n");
    CancelButton->setVisible(true);
    CancelButton->setEnabled(true);
    SplitMode = true;
    getUserInput(3);
}

void MainWindow::on_PreviewButton_clicked()
{
    //TODO implement
    //First bring the slider back to 0, remove the droplets at the last slider position
    time->setPreviousTime();
    timeChange(8);
    tableDmode->getSlider()->setValue(0);

    //Start incrementing the TableSlider, add and remove droplets in the process
    for(int k = 0; k<=tableDmode->getSlider()->maximum();k++){
        time->setPreviousTime();
        tableDmode->getSlider()->setValue(k);
        timeChange(8);
        selectColumn(tableDmode->getSlider()->value());
        qApp->processEvents();
        Sleep(500);         //Specify the speed of preview
    }
}

void MainWindow::on_DispenceButton_clicked()
{
    DisableSignals();
    //TODO ASK USER FOR NUMBER OF INPUTS OR USE A VECTOR
    BeginButton->setEnabled(true);
    BeginButton->setVisible(true);
    CancelButton->setVisible(true);
    CancelButton->setEnabled(true);
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
    //BANANA
    mylayout->Neighbors();

    connect(mylayout, SIGNAL(Lsignal(Droplet*)), this, SLOT(addDropToTable(Droplet*)));
    connect(mylayout, SIGNAL(Lsignal(Droplet*)), this, SLOT(addToDList(Droplet*)));


    connectSignals();
    InitializeUI(true);
    }
}

void MainWindow::on_CancelButton_clicked()
{
    printToInstructionMonitor("Input canceled by user\n");
    clickhandler->deleteLater();
    thread->deleteLater();
    CancelButton->setVisible(false);
    CancelButton->setEnabled(false);
    BeginButton->setEnabled(false);
    BeginButton->setVisible(false);
}

void MainWindow::on_Connect_triggered()
{
    arduino->Connect();
    if(arduino->isConnected()){

        StartButton->setEnabled(true);
        printToInstructionMonitor("Arduino Connected!");
    }else{

        StartButton->setEnabled(false);
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

        //BANANA
        mylayout->Neighbors();

        AddDroplet->setEnabled(true);
        RemoveDroplet->setEnabled(true);
        InitializeUI(true);
        connectSignals();
        connect(mylayout, SIGNAL(Lsignal(Droplet*)), this, SLOT(addDropToTable(Droplet*)));
        connect(mylayout, SIGNAL(Lsignal(Droplet*)), this, SLOT(addToDList(Droplet*)));


    }
}


//TODO NEW
void MainWindow::InitializeTable()
{
    //Setup Tables
    TimeSpinnerEmode->setMinimum(0);
    TimeSpinner->setMinimum(0);
    TimeSpinnerEmode->setValue(0);
    TimeSpinner->setValue(0);

    DropletTable->clear();
    DropletTableEmode->clear();

    tableDmode = new Table(DropletTable);
    tableDmode->CreateTable(this);
    tableEmode = new Table(DropletTableEmode);
    tableEmode->InitializeTableEmode(this);
    ui->currentStepText->setText(QString::number(0));
    ui->currentStepText_Emode->setText(QString::number(0));
    InstructonMonitor->setPlainText(QString::number(tableDmode->getSlider()->width()));
}

//TODO NEW
void MainWindow::addDropToTable(Droplet *drop)
{
    tableDmode->addDropToTable(drop,listdrop,time->CurrentTime());
}

void MainWindow::removeDropFromTable(Droplet *drop)
{
    tableDmode->removeDropFromTable(drop);
}

void MainWindow::updateTable(Droplet *drop)
{
    tableDmode->updateTable(drop,time->CurrentTime());
}

void MainWindow::on_dropTime_valueChanged(int arg1)
{
    int origCol = tableDmode->getColumn();
    int increaseSize = 0;

    //Increase the size of the table according to the TimeSpinner
    if (arg1+2 >= tableDmode->getColumn()){         //Need to account for +2 offset in the columns
        tableDmode->setColumn(arg1+3);
        for (int i=origCol;i<tableDmode->getColumn();i++){
            tableDmode->setColumnW(i,20);
            increaseSize +=20;
        }
        //Increase Span of headers and Slider, increase size of Slider accordingly
        tableDmode->setSp(1,2,1,tableDmode->getColumn()-1);
        tableDmode->setSp(0,2,1,tableDmode->getColumn()-1);
        tableDmode->getSlider()->setMaximum(tableDmode->getColumn()-3);
        //tableDmode->getSlider()->setFixedWidth(tableDmode->getSlider()->width()+increaseSize);
    }    
    TimeSpinner->setMinimum(arg1);
    InstructonMonitor->setPlainText(QString::number(tableDmode->getSlider()->width()));
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
        //QList <Electrode*> addElecs;
        //Access the electrodes based on their numbers, set their color to blue indicating that they're turned on
        for(int i = 2; i<tableEmode->getRow();i++){
            if(tableEmode->getItem(i,tableEmode->getSlider()->value()+1)){
                Electrode* el = mylayout->elecFromText(tableEmode->getItem(i,tableEmode->getSlider()->value()+1)->text());
                //removeElecs.append(el);
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
            //QList <Electrode*> removeElecs;
            //If the has an associated electrode at that time, set that electrode to grey (turned off)
            for(int i = 2; i<tableEmode->getRow();i++){
                if(tableEmode->getItem(i,tableEmode->getSlider()->value()+1)){              //Need to account for +1 offset in the table
                    Electrode* el = mylayout->elecFromText(tableEmode->getItem(i,tableEmode->getSlider()->value()+1)->text());
                    //removeElecs.append(el);
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

//    //KIWI
//    //if(arduino->isConnected()){
    pathHandler = new PathHandler();
    pathHandler->setPathListEmode(tableEmode);
    //For display purposes only
    if(pathHandler->getPathList().length()>0){
        for(int i = 0; i<pathHandler->getPathList().length(); i++){
            InstructonMonitor->insertPlainText(pathHandler->getPathList().at(i));
            qApp->processEvents();
            Sleep(700);
            InstructonMonitor->clear();
        }
    }
//    arduino->SendSequence(pathHandler);
//    //  }
//    /*
//    else{
//        StartButton->setEnabled(false);
//        QMessageBox::warning(this,tr("Arduino"), tr("WARNING! Arduino not Connected!"));
//    }
//    */
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
    TurnOnButton->setChecked(false);
    TurnOffButton->setChecked(false);
    AddDroplet->setChecked(false);
    RemoveDroplet->setChecked(false);

}

void MainWindow::on_ModeButtonTab_tabBarClicked(int index)
{
    //When changing tabs, clear the colors of the layout
    mylayout->ResetColors();
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
    if(index==0){
        TabButton->setCurrentIndex(0);
    }
    else if(index==1){
        TabButton->setCurrentIndex(1);
        TurnOnButton->setChecked(true);
        turnOn = true;
    }
}

void MainWindow::on_dropTimeEmode_valueChanged(int arg1)
{
    //Identical to the other DropTime function => will eventually merge
    int origCol = tableEmode->getColumn();
    int increaseSize = 0;
    if (arg1+1 >= tableEmode->getColumn()){         //Need to account for +1 offset in the columns
        tableEmode->setColumn(arg1+2);
        for (int i=origCol;i<tableEmode->getColumn();i++){
            tableEmode->setColumnW(i,20);
            increaseSize +=20;
        }
        tableEmode->setSp(1,1,1,tableEmode->getColumn()-1);
        tableEmode->setSp(0,1,1,tableEmode->getColumn()-1);
        tableEmode->getSlider()->setMaximum(tableEmode->getColumn()-2);
        tableEmode->getSlider()->setFixedWidth(tableEmode->getSlider()->width()+increaseSize);
    }
    TimeSpinnerEmode->setMinimum(arg1);
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


void MainWindow::on_preview_EmodeButton_clicked()
{
    //Similar to preview in Droplet Mode => Will eventually merge
    timeEmode->setPreviousTime();
    timeChange(8);
    tableEmode->getSlider()->setValue(0);
    //Start incrementing the TableSlider, add and remove droplets in the process
    for(int k = 0; k<=tableEmode->getSlider()->maximum();k++){
        timeEmode->setPreviousTime();
        timeChange(8);
        tableEmode->getSlider()->setValue(k);

        selectColumn(tableEmode->getSlider()->value());
        qApp->processEvents();
        Sleep(500);         //Specify the speed of preview
    }
}

void MainWindow::on_Save_Sequence_triggered()
{
    if(TabButton->currentIndex()==0){
        pathHandler = new PathHandler(listdrop);
        pathHandler->setPathList();
        pathHandler->savePath(this);
    }
    else if(TabButton->currentIndex()==1){
    }
}

void MainWindow::on_Open_Sequence_triggered()
{
    if(TabButton->currentIndex()==0){
        pathHandler = new PathHandler();
        pathHandler->openPath(this);
    }
    else if(TabButton->currentIndex()==1){
    }
}

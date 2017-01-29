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

    ElectrodeLayout = ui->electrodeLayout;
    SplitButton = ui->SplitButton;
    DispenceButton = ui->DispenceButton;
    PreviewButton = ui->PreviewButton ;
    StartButton = ui->StartButton;
    InstructonMonitor = ui->InstructonMonitor;
    CancelButton = ui->CancelButton;
    AddDroplet = ui->addDrop;
    RemoveDeroplet = ui->removedrop;
    BeginButton = ui->BeginButton;

    DropletTable = ui->dropTable;
    TimeSpinner = ui->dropTime;
    TimeSlider = ui->dropSlider;

    InitializeTable();

    DispenceMode = false;
    SplitMode = false;
    LayoutExists = false;

    InitializeUI(false);

    CancelButton->setEnabled(false);
    CancelButton->setVisible(false);
    BeginButton->setEnabled(false);
    BeginButton->setVisible(false);

    StartButton->setEnabled(true);

    arduino = new Arduino();
    mylayout = new Layout(ElectrodeLayout);
}

MainWindow::~MainWindow(){
    delete ui;
    //TODO delete all pointers and qlists
}

void MainWindow::InitializeUI(bool enable){

    SplitButton->setEnabled(enable);
    PreviewButton->setEnabled(enable);
    DispenceButton->setEnabled(enable);
    InstructonMonitor->setEnabled(enable);
    AddDroplet->setEnabled(enable);
    RemoveDeroplet->setEnabled(enable);
    time = new Time(tab->getSlider());
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
            Droplet *NewDroplet = new Droplet(tab->getSlider()->value());
            if(NewDroplet->Selected){
                electrode->setDroplet(NewDroplet);
                electrode->setToolTip("Name: " + NewDroplet->getName() + "\nVolume: " + QString::number(NewDroplet->getVolume()));
                electrode->getDroplet()->updateInfo(electrode->text(), tab->getSlider()->value(), electrode, "update");
                listdrop.append(NewDroplet);
                addDropToTable(NewDroplet);
                AddDroplet->setChecked(false);
            }
        }
    }
    else if(RemoveDeroplet->isChecked()){           //if the "Remove droplet" option is selected
        if(!(electrode->isEmpty())){
            listdrop.removeOne(electrode->getDroplet());
            removeDropFromTable(electrode->getDroplet());
            electrode->removeDroplet();
            RemoveDeroplet->setChecked(false);
        }
    }
    else if(SplitMode){}
    else if(DispenceMode){}
    else{                                              //if the user just want to move the droplet

        time->setPreviousTime();
        time->increaseTime(TimeSpinner);
        //QMessageBox::warning(this,tr("Arduino"), tr("WARNING! Arduino not Connected!"));
        mylayout->CheckSurroundingElectrodes(electrode,time->CurrentTime());
        updateTable(electrode->getDroplet());
        timeChange(8);   //MAY NOT NEED TRIGGER IS ALREADY HAPPENING
        selectColumn(tab->getSlider()->value());
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
    SplitButton->setEnabled(true);
    DispenceButton->setEnabled(true);
    DispenceMode = false;

    Electrode *last;
    Electrode* current;
    Droplet *reservoir = elecList.at(0)->getDroplet();

    if(elecList.at(0)->getAvailability() == 0 ){
    //if the electrodes are not empty at any poit, break
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
//FIXME crashes????
        //at this point everything should be ok, else the function should have broken out of the loop

//        time->setPreviousTime();
//        time->increaseTime(TimeSpinner);
//        Droplet* initialDrop = elecList.at(0)->getDroplet();
//        initialDrop->updateInfo(elecList.at(0)->text(),time->CurrentTime(),elecList.at(0),"update");
//        updateTable(initialDrop);
//        timeChange(8);

//        time->setPreviousTime();
//        time->increaseTime(TimeSpinner);
//        Droplet* drop = new Droplet(elecList.at(0)->getDroplet()->getName()+ "-D",elecList.at(0)->getDroplet()->getColor(),1111111,time->CurrentTime());
//        drop->updateInfo(elecList.at(1)->text(),time->CurrentTime(),elecList.at(1),"update");
//        elecList.at(1)->setDroplet(drop);
//        listdrop.append(drop);
//        addDropToTable(drop);
//        timeChange(8);
//        for(int i = 2; i<elecList.size();i++){
//            time->setPreviousTime();
//            time->increaseTime(TimeSpinner);
//            elecList.at(i)->setDroplet(drop);
//            drop->updateInfo(elecList.at(i)->text(),time->CurrentTime(),elecList.at(i),"update");
//            updateTable(elecList.at(i)->getDroplet());
//            timeChange(8);
//        }

//        initialDrop->updateInfo(elecList.at(0)->text(),time->CurrentTime(),elecList.at(0),"update");
//        updateTable(initialDrop);
//        selectColumn(TableSlider->value());
        QMessageBox::warning(this,tr("DONE"), tr("DONE!"));

    }else{
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
    //if there is a droplet on the first electrode
    if(parent->getAvailability() == 0){
      Droplet* temp = parent->getDroplet();

        foreach(Electrode* elec, elecList.at(1)->getNeighbors()){
            if(elec == parent){
                sharedNeighbor++;
            }
            if(elec->getAvailability() == 0 ){
                if(elec->getDroplet() != temp){
                    QMessageBox::warning(this,tr("Warning"), tr("split failed, there are more droplets around"));
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
                    QMessageBox::warning(this,tr("Warning"), tr("split failed, there are more droplets around"));
                    return;
                }
            }
        }
        if(sharedNeighbor != 1){
            QMessageBox::warning(this,tr("Warning"), tr("Electrode 2 is not adajecnt to the parent droplet"));
            return;
        }

        time->increaseTime(TimeSpinner);
        //if all the surrounding electrodes are empty, create two new droplets
        Droplet* split1 = new Droplet(temp->getName()+"-S1",temp->getColor(),temp->getVolume()/2, tab->getSlider()->value());
        split1->updateInfo(elecList.at(1)->text(),time->CurrentTime(),elecList.at(1),"update");
        elecList.at(1)->setDroplet(split1);
        listdrop.append(split1);
        addDropToTable(split1);

        Droplet* split2 = new Droplet(temp->getName()+"-S2",temp->getColor(),temp->getVolume()/2, tab->getSlider()->value());
        split2->updateInfo(elecList.at(2)->text(),time->CurrentTime(),elecList.at(2),"update");
        elecList.at(2)->setDroplet(split2);
        listdrop.append(split2);
        addDropToTable(split2);

        parent->getDroplet()->updateInfo("", time->CurrentTime(), parent, "split");
        parent->removeDroplet();
        cout<<listdrop.size()<<endl;
    }
    else{
        QMessageBox::warning(this,tr("Warning"), tr("No droplet was selected!"));
    }
}

void MainWindow::on_StartButton_clicked(){

        pathHandler = new PathHandler(listdrop);
        pathHandler->setPathList();
        if(pathHandler->getPathList().length()>0){
            for(int i = 0; i<pathHandler->getPathList().length(); i++){
                ui->lineEdit->setText(pathHandler->getPathList().at(i));
                qApp->processEvents();
                Sleep(700);
            }
        }
        arduino->SendSequence(pathHandler);
}

void MainWindow::on_BeginButton_clicked(){

    clickhandler->Done();
    BeginButton->setVisible(false);
    BeginButton->setEnabled(false);
    CancelButton->setVisible(false);
    CancelButton->setEnabled(false);
}

void MainWindow::on_SplitButton_clicked()
{
    CancelButton->setVisible(true);
    CancelButton->setEnabled(true);
    DispenceButton->setEnabled(false);
    SplitMode = true;
    getUserInput(3);   
}

void MainWindow::on_PreviewButton_clicked()
{
    //First bring the slider back to 0, remove the droplets at the last slider position
    time->setPreviousTime();
    timeChange(8);
    tab->getSlider()->setValue(0);

    //Start incrementing the TableSlider, add and remove droplets in the process
    for(int k = 0; k<=tab->getSlider()->maximum();k++){
        time->setPreviousTime();
        tab->getSlider()->setValue(k);
        timeChange(8);
        selectColumn(tab->getSlider()->value());
        qApp->processEvents();
        Sleep(200);         //Specify the speed of preview
    }
}

void MainWindow::on_DispenceButton_clicked()
{
    BeginButton->setEnabled(true);
    BeginButton->setVisible(true);
    CancelButton->setVisible(true);
    CancelButton->setEnabled(true);
    SplitButton->setEnabled(false);
    DispenceMode = true;
    getUserInput(1000);
}

void MainWindow::on_CancelButton_clicked()
{

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

void MainWindow::on_addDrop_clicked(){
    RemoveDeroplet->setChecked(false);
}

void MainWindow::on_removedrop_clicked(){
    AddDroplet->setChecked(false);
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

    connect(mylayout, SIGNAL(Lsignal(Droplet*)), this, SLOT(addDropToTable(Droplet*)));
    connect(mylayout, SIGNAL(Lsignal(Droplet*)), this, SLOT(addToDList(Droplet*)));

    connectSignals();
    InitializeUI(true);

    mylayout->Neighbors();
    }
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

        AddDroplet->setEnabled(true);
        RemoveDeroplet->setEnabled(true);
        InitializeUI(true);
        connectSignals();
        connect(mylayout, SIGNAL(Lsignal(Droplet*)), this, SLOT(addDropToTable(Droplet*)));
        connect(mylayout, SIGNAL(Lsignal(Droplet*)), this, SLOT(addToDList(Droplet*)));
        mylayout->Neighbors();
    }
}

void MainWindow::addDropToTable(Droplet *drop){

    tab->addDropToTable(drop,listdrop,time->CurrentTime());
}

void MainWindow::removeDropFromTable(Droplet *drop){

    tab->removeDropFromTable(drop);
}

void MainWindow::InitializeTable()
{
    //Setup Table
    tab = new Table(DropletTable);
    tab->CreateTable(this);
    ui->currentStepText->setText(QString::number(0));
}

void MainWindow::updateTable(Droplet *drop)
{
    tab->updateTable(drop,time->CurrentTime());
}

void MainWindow::on_dropTime_valueChanged(int arg1)
{
    //Increase the size of the table according to the TimeSpinner
    if (arg1+2 >= tab->getColumn()){         //Need to account for +2 offset in the columns
        tab->setColumn(arg1+3);
        for (int i=2;i<tab->getColumn();i++){
            tab->setColumnW(i,20);
        }
        tab->setSp(1,2,1,tab->getColumn()-1);
        tab->setSp(0,2,1,tab->getColumn()-1);
        tab->getSlider()->setMaximum(tab->getColumn()-3);
        tab->getSlider()->setFixedWidth(tab->getSlider()->width()+20);
    }
}

void MainWindow::selectColumn(int value)        //Value is the value of the tableslider
{
    ui->currentStepText->setText(QString::number(value));
    foreach(Droplet* drop, listdrop){
        int evaluatedTime = value;
        if(value<=drop->getDropletInfo().length()-1){
        }
        else{
            if(drop->getDropletInfo().length()>0){
                evaluatedTime = drop->getDropletInfo().length()-1;
            }
        }
        foreach(Info inf, drop->getDropletInfo()){
            if(inf.time == evaluatedTime){
                if(inf.status!="merged" && inf.status != "absent" && inf.status!= "split"){
                        inf.elec->setDroplet(drop);
               }
            }
        }
    }
}

void MainWindow::timeChange(int value)
{
    if(value >= 1 && value <= 8){
        if(value!=8){
            time->setPreviousTime();
        }       
        int evaluatedTime;
        //Remove droplets from all previous times
        foreach(Droplet* drop, listdrop){
            if(time->getPreviousTime() > drop->getDropletInfo().length()-1){
                evaluatedTime = drop->getDropletInfo().length()-1;
            }
            else{
                evaluatedTime = time->getPreviousTime();
            }
            foreach(Info inf, drop->getDropletInfo()){
                if(inf.status!="merged" && inf.status!="absent" && inf.status!="split" && inf.time == evaluatedTime){
                   if(inf.elec->getDroplet()){
                       inf.elec->removeDroplet();
                    }
                }
            }
        }
    }
}

void MainWindow::addToDList(Droplet* addD){

    listdrop.append(addD);
}


void MainWindow::on_actionSave_Droplets_triggered()
{
    mylayout->saveDroplets(this,listdrop);
}

void MainWindow::on_actionLoad_Droplets_triggered()
{
   listdrop = mylayout->openDroplets(this);

}

#include "LayoutDesign.h"
#include "ui_LayoutDesign.h"
#include <NewLayout.h>
#include <QMessageBox>
#include <mainwindow.h>

LayoutDesign::LayoutDesign(QWidget *parent): QDialog(parent), ui(new Ui::LayoutDesign){

    ui->setupUi(this);

    Designgrid = ui->DesignGrid;
    AcceptButton = ui->AcceptButton;
    CreateButton = ui->CreateButton;
    EditMode = true;

    AcceptButton->setEnabled(true);
    CreateButton->setEnabled(false);
    CreateButton->setVisible(false);

    TopFrame = ui->TopFrame;
    BottomFrame = ui->BottomFrame;
    LeftFrame = ui->LeftFrame;

    TopFrame->setSpacing(0);
    TopFrame->setSizeConstraint(QGridLayout::SetFixedSize);
    TopFrame->setMargin(0);

    BottomFrame->setSpacing(0);
    BottomFrame->setSizeConstraint(QGridLayout::SetFixedSize);
    BottomFrame->setMargin(0);

    LeftFrame->setSpacing(0);
    LeftFrame->setSizeConstraint(QGridLayout::SetFixedSize);
    LeftFrame->setMargin(0);

    DesignLayout();
    ConnectSignals();

    QMessageBox::warning(this,tr("GridDesign"), tr("Please make the shape of the DMF chip"));
}

LayoutDesign::~LayoutDesign(){
    qDeleteAll(contactPads);
    contactPads.clear();
    delete ui;
}

void LayoutDesign::DesignLayout(){

    NewLayout *newLayout = new NewLayout();
    newLayout->exec();

    inputRows = newLayout->getRows();
    inputColumns = newLayout->getColumns();

    QGridLayout *layout = Designgrid;
    mylayout = new Layout(layout,inputRows,inputColumns);
    mylayout->CreateLayout();
}

void LayoutDesign::ConnectSignals(){

    int totalColumns = Designgrid->columnCount();
    int totalRows = Designgrid->rowCount();
    for(int i=0; i<totalRows;i++){
        for(int j=0; j<totalColumns;j++){
            QLayoutItem* item = Designgrid->itemAtPosition(i,j);
            QWidget* widget = item->widget();
            Electrode* electrode = dynamic_cast<Electrode*>(widget);
            connect(electrode,SIGNAL(clicked()),this,SLOT(Edit()));           
        }
    }
}

//when the user is creating their desired pattern, this method changes the color of the electrodes clicked
void LayoutDesign::Edit(){

    Electrode *obj = qobject_cast<Electrode*>(QObject::sender());
    bool clicked = obj->getState();

    if(EditMode){
        if(!clicked){
            obj->setStyleSheet("background-color: orange");
            obj->setState(true);
            clicked = true;
        }else{
            obj->setStyleSheet("background-color: grey");
            obj->setState(false);
            clicked = false;
        }
    }
    else{       
       electrode = obj;
       electrode->setStyleSheet("background-color: orange; border-style: outset ;border-width: 4px; border-color: blue");
    }
}

//add the contact pads to the surrounding frames
void LayoutDesign::AddContactPads(){
int topcount = 1;
int botcount = 58;
int leftcount = 48;

    for(int i=0; i<2; i++){
        for(int j=0; j<24; j++){
            if(topcount != 48){
            QPushButton *contactpad = new QPushButton;
            std::string name = std::to_string(topcount);
            contactpad->setText(QString::fromStdString(name));
            contactpad->setMinimumSize(30,30);
            connect(contactpad,SIGNAL(clicked(bool)),this,SLOT(SetElectrodeNumber()));
            TopFrame->addWidget(contactpad,i,j);
            contactPads.append(contactpad);
            topcount++;
            }
        }
    }

    for(int i=2; i>0; i--){
        for(int j=0; j<24; j++){
            if(botcount != 105){
                QPushButton *contactpad = new QPushButton;
                std::string name = std::to_string(botcount);
                contactpad->setText(QString::fromStdString(name));
                contactpad->setMinimumSize(30,30);
                connect(contactpad,SIGNAL(clicked(bool)),this,SLOT(SetElectrodeNumber()));
                BottomFrame->addWidget(contactpad,i,j);
                contactPads.append(contactpad);
                botcount++;
            }
        }
    }

    for(int i=0; i<10; i++){
        QPushButton *contactpad = new QPushButton;
        std::string name = std::to_string(leftcount);
        contactpad->setText(QString::fromStdString(name));
        contactpad->setMinimumSize(30,30);
        connect(contactpad,SIGNAL(clicked(bool)),this,SLOT(SetElectrodeNumber()));
        LeftFrame->addWidget(contactpad,i,0);
        contactPads.append(contactpad);
        leftcount++;
   }
}

//match the electrode number clicked with the contact pad clicked
void LayoutDesign::SetElectrodeNumber(){
    if(electrode){
        QPushButton *obj = qobject_cast<QPushButton*>(QObject::sender()); //get the refrence to the object that provoked this SLOT
        electrode->setText(obj->text());
        electrode->setStyleSheet("background-color: orange");
        std::string number = obj->text().toStdString();
        electrode->setNumber(number);
    }
}

void LayoutDesign::on_AcceptButton_clicked(){

    CreateButton->setEnabled(true);
    CreateButton->setVisible(true);
    AcceptButton->setVisible(false);
    AcceptButton->setEnabled(false);
    EditMode = false;
    mylayout->FinalizeLayout();
    AddContactPads();
    QMessageBox::warning(this,tr("ContactPad Numbering"), tr("Please connect the contact pads to the electrodes by clicking on the electrode and then the desired contact pad"));
}

void LayoutDesign::on_CreateButton_clicked(){

    if(checkDuplicates() && checkName() ){
        Done = true;
        QDialog::accept();
        this->close();
    }
    else{
        QMessageBox::warning(this,tr("Error"), tr("There is either a contact pad connected to two electrodes or an electrode is missing a contact pad"));
    }
}

bool LayoutDesign::checkName(){

    for (int i=0; i<Designgrid->rowCount();i++){
        for(int j=0; j<Designgrid->columnCount();j++){
            QLayoutItem* item = Designgrid->itemAtPosition(i,j);
            QWidget* widget = item->widget();
            Electrode* electrode = dynamic_cast<Electrode*>(widget);
            if (electrode->getState() == true && electrode->getNumber() == "") return false;
        }
    }
    return true;
}

bool LayoutDesign::checkDuplicates(){
    //TODO implement
    return true;
}

QGridLayout* LayoutDesign::returnDesign(){
    return Designgrid;
}

int LayoutDesign::getColumns(){
    return inputColumns;
}

int LayoutDesign::getRows(){
    return inputRows;
}

#include "DropletSelector.h"
#include "ui_DropletSelector.h"

DropletSelector::DropletSelector(QWidget *parent):QDialog(parent),ui(new Ui::DropletSelector){

    ui->setupUi(this);
    NameEditor = ui->nameedit;
    VolumeEditor = ui->voledit;
    ColorSelector = ui->colorbox;
    NameEditor->setText("Name");
    VolumeEditor->setText("1");

    QStringList ColorList = QStringList() << "green"<<"red"<<"yellow"<<"blue"<<"pink"<<"white"<<"cyan"<<"magenta"<<"black";
    ColorSelector->addItems(ColorList);
}

DropletSelector::~DropletSelector(){
    delete ui;
}

QString DropletSelector::getName(){
    return NameEditor->text();
}

QString DropletSelector::getColor(){
    return ColorSelector->currentText();
}

double DropletSelector::getVolume(){
    QString temp = VolumeEditor->text();
    double vol = temp.toDouble(false);
    return vol;
}

void DropletSelector::on_OK_clicked(){

    if(this->getName().length()>10 ){
        QMessageBox::warning(this,tr("Warning"), tr("Please choose a name with less than ten characters"));
    }
    else if(this->getName().length()==0){

        QMessageBox::warning(this,tr("Warning"), tr("Please fill out the name text box"));
    }
    else if(!this->VolumeEditor->text().toInt()>0){
        QMessageBox::warning(this,tr("Warning"), tr("Please specify an integer for the volume"));
    }
    else{
        Done = true;
        QDialog::accept();
    }
}

void DropletSelector::on_Cancel_clicked(){

    QDialog::close();
}

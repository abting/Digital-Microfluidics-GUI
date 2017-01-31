#include "DropletSelector.h"
#include "ui_DropletSelector.h"
#include <QMessageBox>

DropletSelector::DropletSelector(QWidget *parent):QDialog(parent),ui(new Ui::DropletSelector){

    ui->setupUi(this);
    NameEditor = ui->nameedit;
    VolumeEditor = ui->voledit;
    ColorSelector = ui->colorbox;
    NameEditor->setText("Drop");
    VolumeEditor->setText("100");

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

bool DropletSelector::isDuplicate(QList<Droplet *> list, QString name){
    foreach(Droplet* drop, list){
        if(drop->getName() == name){
            QMessageBox::warning(this,tr("Duplicate"), tr("Droplet name is a duplicate!"));
            return true;
        }
    }
    return false;
}

double DropletSelector::getVolume(){
    QString temp = VolumeEditor->text();
    double vol = temp.toDouble(false);
    return vol;
}

void DropletSelector::on_OK_clicked(){
    //set volume range
    QString temp = VolumeEditor->text();
    double vol = temp.toDouble(false);
    //FIXME add list somehow
    //if(!isDuplicate(list ,NameEditor->text())){

        if(vol>0 && NameEditor->text() != NULL){
            Done = true;
            QDialog::accept();
        }
    }
//}

void DropletSelector::on_Cancel_clicked(){

    QDialog::close();
}

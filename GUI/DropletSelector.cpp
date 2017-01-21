#include "DropletSelector.h"
#include "ui_DropletSelector.h"

DropletSelector::DropletSelector(QWidget *parent):QDialog(parent),ui(new Ui::DropletSelector){

    ui->setupUi(this);
    NameEditor = ui->nameedit;
    VolumeEditor = ui->voledit;
    ColorSelector = ui->colorbox;

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

    Done = true;
    QDialog::accept();
}

void DropletSelector::on_Cancel_clicked(){

    QDialog::close();
}

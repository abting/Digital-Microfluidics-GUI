#include "NewLayout.h"
#include "ui_NewLayout.h"

NewLayout::NewLayout(QWidget *parent) : QDialog(parent), ui(new Ui::NewLayout)
{
    this->setFixedSize(251,217);
    this->setWindowTitle("New Layout");
    ui->setupUi(this);
}

NewLayout::~NewLayout()
{
    delete ui;
}

int NewLayout::getRows(){
    return Rows;
}

int NewLayout::getColumns(){
    return Columns;
}

void NewLayout::on_Ok_clicked()
{
    Rows = (ui->rowEdit->text()).toInt();
    Columns = (ui->columnEdit->text()).toInt();
    if(Rows >0 && Columns >0){
        QDialog::accept();
        this->close();
    }
}

void NewLayout::on_Cancel_clicked()
{
    QDialog::destroy();
}

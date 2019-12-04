#include "dialogdelyana.h"
#include "ui_dialogdelyana.h"

DialogDelyana::DialogDelyana(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDelyana),
    valya(0,10000,this)
{
    ui->setupUi(this);

    ui->priceLineEdit->setValidator(&valya);
    ui->cpdLineEdit->setValidator(&valya);
    ui->currentLineEdit->setValidator(&valya);
}

DialogDelyana::~DialogDelyana()
{
    delete ui;
}

int DialogDelyana::getCurr(){
    return ui->currentLineEdit->text().toInt();
}

int DialogDelyana::getCpd(){
    return ui->cpdLineEdit->text().toInt();
}

int DialogDelyana::getPrice(){
    return ui->priceLineEdit->text().toInt();
}

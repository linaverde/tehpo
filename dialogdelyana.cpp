#include "dialogdelyana.h"
#include "ui_dialogdelyana.h"

#include <QIntValidator>

DialogDelyana::DialogDelyana(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDelyana),
    valya(0,10000,this)
{
    this->parent = parent;
    ui->setupUi(this);

    ui->priceLineEdit->setValidator(&valya);
    ui->cpdLineEdit->setValidator(&valya);
    ui->currentLineEdit->setValidator(&valya);
}

DialogDelyana::~DialogDelyana()
{
    delete ui;
}

unsigned int DialogDelyana::getCurr(){
    return ui->currentLineEdit->text().toInt();
}

unsigned int DialogDelyana::getCpd(){
    return ui->cpdLineEdit->text().toInt();
}

unsigned int DialogDelyana::getPrice(){
    return ui->priceLineEdit->text().toInt();
}

#include "dialogdelyana.h"
#include "ui_dialogdelyana.h"

#include <QIntValidator>

DialogDelyana::DialogDelyana(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDelyana)
{
    //ui->priceLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->priceLineEdit));
    //ui->cpdLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->cpdLineEdit));
    //ui->currentLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->currentLineEdit));
    this->parent = parent;
    ui->setupUi(this);

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

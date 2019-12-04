#include "dialogroad.h"
#include "ui_dialogroad.h"

DialogRoad::DialogRoad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRoad),
    valya(0,10000,this)
{
    ui->setupUi(this);

    ui->kmLineEdit->setValidator(&valya);
    ui->priceLineEdit->setValidator(&valya);
}

DialogRoad::~DialogRoad()
{
    delete ui;
}

int DialogRoad::getKm(){
    return ui->kmLineEdit->text().toInt();
}

int DialogRoad::getPrice(){
    return ui->priceLineEdit->text().toInt();
}

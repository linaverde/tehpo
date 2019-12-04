#include "dialogroad.h"
#include "ui_dialogroad.h"

DialogRoad::DialogRoad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRoad)
{
    ui->setupUi(this);
}

DialogRoad::~DialogRoad()
{
    delete ui;
}

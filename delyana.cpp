#include "delyana.h"

#include <iostream>

Delyana::Delyana(QPoint pos, int cpd, int currCount, int price)
{
    this->pos = pos;
    this->cpd = cpd;
    this->currentCount = currCount;
    this->price = price;
    this->setToolTip(QString::number(currCount) + " ед. леса<br>Цена за ед.: "
                     + QString::number(price) + "руб<br>Выработка " + QString::number(cpd) + "ед. в день");
}

Delyana::~Delyana(){

}

void Delyana::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QPixmap pixmap;
    if (pixmap.load(":images/tree.jpg"))
    {
        QRect r (0, 0, 20, 30);
        painter->drawPixmap(r, pixmap);
        this->setPos(pos);
    }
}

QRectF Delyana::boundingRect() const{
    QRectF r(0, 0, 20, 30);
    return r;
}

QPoint Delyana::getPos(){
    return pos;
}

QVector <Road*> Delyana::getRoads(){
    return roads;
}

void Delyana::addRoad(Road* r){
    roads.push_back(r);
}

int Delyana::getCurrentCount(){
    return currentCount;
}

int Delyana::getPrice(){
    return price;
}

void Delyana::increaceStatment(){
    this->currentCount += this->cpd;
    this->setToolTip(QString::number(currentCount) + " ед. леса<br>Цена за ед.: "
                     + QString::number(price) + "руб<br>Выработка " + QString::number(cpd) + "ед. в день");
}

void Delyana::contOrder(unsigned int nForest){
    this->currentCount -= nForest;
    this->setToolTip(QString::number(currentCount) + " ед. леса<br>Цена за ед.: "
                     + QString::number(price) + "руб<br>Выработка " + QString::number(cpd) + "ед. в день");
}


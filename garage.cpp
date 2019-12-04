#include "garage.h"

Garage::Garage(QPoint pos)
{
    this->pos = pos;
}

Garage::~Garage(){

}


void Garage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QPixmap pixmap;
    if (pixmap.load("D:/qt/projects/tehrazpo/garage.jfif"))
    {
        QRect r (0, 0, 50, 30);
        painter->drawPixmap(r, pixmap);
        this->setPos(pos);
    }
}

QRectF Garage::boundingRect() const{
    return QRectF(0, 0, 50, 30);
}

QPoint Garage::getPos(){
    return pos;
}


QVector <Road*> Garage::getRoads(){
    return roads;
}

void Garage::addRoad(Road* r){
    roads.push_back(r);
}

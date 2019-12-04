#include "emptypoint.h"

EmptyPoint::EmptyPoint(){

}

EmptyPoint::EmptyPoint(QPoint pos)
{
    this->pos = QPoint(pos.x()-5, pos.y()-5);
}

EmptyPoint::~EmptyPoint(){

}

void EmptyPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QRect r(0,0, 10,10);
    painter->drawEllipse(r);
    this->setPos(pos);
}

QRectF EmptyPoint::boundingRect() const{
    return QRectF(0, 0, 10, 10);
}

QPoint EmptyPoint::getPos(){
    return pos;
}


QVector <Road*> EmptyPoint::getRoads(){
    return roads;
}

void EmptyPoint::addRoad(Road* r){
    roads.push_back(r);
}

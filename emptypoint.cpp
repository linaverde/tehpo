#include "emptypoint.h"

EmptyPoint::EmptyPoint(){

}

EmptyPoint::EmptyPoint(QPoint pos)
{
    this->pos = pos;
}

EmptyPoint::~EmptyPoint(){

}

void EmptyPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QRect r(0,0, 10,10);
    painter->setBrush(Qt::black);
    QPen pen(Qt::white, 2);
    painter->setPen(pen);
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

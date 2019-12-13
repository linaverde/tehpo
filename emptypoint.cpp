#include "emptypoint.h"

EmptyPoint::EmptyPoint() : QObject(){

}

EmptyPoint::EmptyPoint(QPoint pos) : QObject()
{
    this->pos = pos;
}

EmptyPoint::EmptyPoint(const EmptyPoint& e) : QObject(){
    this->pos = e.pos;
    this->roads = e.roads;
}

EmptyPoint::~EmptyPoint(){

}

void EmptyPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QRect r(0,0, 10,10);
    painter->setBrush(Qt::black);
    QPen pen1(Qt::white, 2);
    painter->setPen(pen1);
    painter->drawEllipse(r);
    QPen pen2(Qt::black, 2);
    painter->setPen(pen2);
    painter->drawText(QPoint(0, 0), QString::number(number));
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

void EmptyPoint::setNumber(unsigned int number){
    this->number = number;
}

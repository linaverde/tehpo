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
    /*QPen pen(Qt::red, 4);
    painter->setPen(pen);
    painter->draw; */

    QRect r(0,0, 10,10);
    painter->drawEllipse(r);
    this->setPos(pos);
}

QRectF EmptyPoint::boundingRect() const{
    return QRectF(0, 0, 10, 10);
}

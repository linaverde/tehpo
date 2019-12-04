#include "road.h"


Road::Road(EmptyPoint* start, EmptyPoint* end, unsigned int km, unsigned int price)
{
    this->start = start;
    this->end = end;
    this->km = km;
    this->price = price;
    this->setToolTip(QString::number(km) + " километров<br>Цена проезда: " + QString::number(price) + "руб");
}

Road::~Road(){

}

void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::red, 2);
    painter->setPen(pen);
    //this->setPos(QPoint(qMin(start->getPos().x(), end->getPos().x()), qMin(start->getPos().y(), end->getPos().y())));
    painter->drawLine(start->getPos(), end->getPos());

}

QRectF Road::boundingRect() const
{
    return QRectF(0, 0, abs(start->getPos().x() - end->getPos().x()), abs(start->getPos().y() - end->getPos().y()));
}

void Road::updateTip(){
    this->setToolTip(QString::number(km) + " километров<br>Цена проезда: " + QString::number(price) + "руб");
}

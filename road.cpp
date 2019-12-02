#include "road.h"


Road::Road(QPoint start, QPoint end, unsigned int km, unsigned int price)
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
    //QRectF rect = boundingRect();

    QPen pen(Qt::red, 4);
    painter->setPen(pen);
    painter->drawLine(start, end);

}

QRectF Road::boundingRect() const
{
    // outer most edges
    return QRectF(qMin(start.x(), end.x()), qMin(start.y(), end.y()), qMax(start.x(), end.x()), qMax(start.y(), end.y()));
}

void Road::updateTip(){
    this->setToolTip(QString::number(km) + " километров<br>Цена проезда: " + QString::number(price) + "руб");
}

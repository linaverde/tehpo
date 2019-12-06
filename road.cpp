#include "road.h"


Road::Road(EmptyPoint* start, EmptyPoint* end, QPoint startP, QPoint endP, int km, int price)
{
    this->start = start;
    this->end = end;
    this->s = startP;
    this->e = endP;
    this->km = km;
    this->price = price;
    this->setToolTip(QString::number(km) + " километров<br>Цена проезда: " + QString::number(price) + "руб");
}

Road::Road(const Road& r){
    this->start = r.start;
    this->end = r.end;
    this->s = r.s;
    this->e = r.e;
    this->km = r.km;
    this->price = r.price;
}

Road::~Road(){

}

void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::blue, 2);
    painter->setPen(pen);
    painter->drawLine(s, e);
    //this->setPos(QPoint(qMin(s.x(), e.x()), qMin(s.y(), e.y()))); - эта херобора все ломает, но без нее всплывающее окно уезжает

}

QRectF Road::boundingRect() const
{
    return QRectF(0, 0, abs(s.x() - e.x()), abs(s.y() - e.y()));
}

void Road::updateTip(){
    this->setToolTip(QString::number(km) + " километров<br>Цена проезда: " + QString::number(price) + "руб");
}

EmptyPoint* Road::getStartPoint(){
    return start;
}

EmptyPoint* Road::getEndPoint(){
    return end;
}

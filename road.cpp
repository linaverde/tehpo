#include "road.h"


Road::Road(int x1, int y1, int x2, int y2, unsigned int km, unsigned int price)
{
    start = QPoint(x1, y1);
    end = QPoint(x2, y2);
    //setFlag(ItemIsMovable);
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
    return QRectF(0, 0, abs(end.x() - start.x()), abs(end.y() - start.y()));
}

void Road::updateTip(){
    this->setToolTip(QString::number(km) + " километров<br>Цена проезда: " + QString::number(price) + "руб");
}

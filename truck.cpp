#include "truck.h"

Truck::Truck(){

}

Truck::Truck(Garage* garagePosition, unsigned int speedPerDay, unsigned int capacity)
{
    this->homeGarage = garagePosition;
    this->speedPerDay = speedPerDay;
    this->capacity = capacity;
}

QRectF Truck::boundingRect() const {
    return QRectF(0, 0, 40, 30);
}

void Truck::paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
                  QWidget * widget){
    QPixmap pixmap;
    if (pixmap.load("D:/qt/projects/tehrazpo/truck.png"))
    {
        QRect r (0, 0, 40, 30);
        painter->drawPixmap(r, pixmap);
        this->setPos(pos);
    }
}

void Truck::setPosition(QPoint pos){
    this->setPos(pos);
}

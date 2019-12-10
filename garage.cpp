#include "garage.h"

Garage::Garage(QPoint pos)
{
    this->pos = pos;
    trucks.push_back(new Truck(this, 100, 50));
    trucks.push_back(new Truck(this, 80, 70));
    trucks.push_back(new Truck(this, 60, 100));
    trucks.push_back(new Truck(this, 40, 150));
}

Garage::Garage(const Garage& g){
    this->pos = g.pos;
    this->roads = g.roads;
    this->trucks = g.trucks;
}

Garage::~Garage(){

}


void Garage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QPixmap pixmap;
    if (pixmap.load(":images/garage.jfif"))
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

QVector<Truck*> Garage::getTrucks(){
    return trucks;
}

void Garage::getOrder(Office *office, int nForest){
    //выбираем грузовик из свободных
    //передаем заказ ему
}

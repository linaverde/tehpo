#include "garage.h"

Garage::Garage(QPoint pos)
{
    this->pos = pos;
    trucks.push_back(new Truck(this, 100, 500));
}

Garage::Garage(const Garage& g): EmptyPoint(g){
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

void Garage::getOrder(const Office& office, unsigned int nForest){
    Truck* bestTruck = trucks.at(0);
    for (Truck* t: this->trucks) {
        if (t->getCapacity() >= nForest && t->getCapacity() < bestTruck->getCapacity() && t->getTruckStatus() == 0){
            bestTruck = t;
        }
    }
    if (bestTruck->getCapacity() >= nForest && bestTruck->getTruckStatus() == 0){
        Office o = office;
        bestTruck->getOrder(&o, nForest);
    }
}

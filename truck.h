#ifndef TRUCK_H
#define TRUCK_H

#include "emptypoint.h"
#include "delyana.h"
#include "dialogdelyana.h"
#include "dialogroad.h"
#include "office.h"
#include "garage.h"

class Garage;

class Truck : public QGraphicsItem, public QObject
{

private:
    enum status {rest, out};
    status s;
    unsigned int speedPerDay;
    unsigned int capacity;
    QPoint pos;
    Road* currentRoad;
    EmptyPoint* currentPoint;
    Garage* homeGarage;
    QList <EmptyPoint*>* currentWay;
    Office *currDestinationOffice;

public:
    Truck ();
    Truck (const Truck& t);
    explicit Truck(Garage* garagePosition, unsigned int speedPerDay, unsigned int capacity);

    void setPosition(QPoint pos);

    Road* getCurrentRoad();
    EmptyPoint* getCurrentPoint();

    QRectF boundingRect() const override;

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget) override;

    QList <EmptyPoint*>* createWayToDelyana(unsigned int nForest);

    void IncreaceStatment();

};

#endif // TRUCK_H

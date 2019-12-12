#ifndef TRUCK_H
#define TRUCK_H

#include <QGraphicsScene>
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
    unsigned int speed;
    unsigned int capacity;
    QPoint pos;
    Garage* homeGarage;

    int currentOrderSum;
    unsigned int nForest;
    QList <QPoint> currentWay;
    Delyana *currDestinationDelyana;
    Office *currDestinationOffice;

    QList <EmptyPoint*> createWayToDelyana(unsigned int nForest);

    QList <EmptyPoint*> createWayToOffice(EmptyPoint* lastP);

    QList <QPoint> calculateCurrWayPoints(QList <EmptyPoint*> way);

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

    void getOrder(Office *office, unsigned int nForest);

    Truck increaceStatment(QGraphicsScene *scene);

    unsigned getCapacity();

    status getTruckStatus();

};

#endif // TRUCK_H

#ifndef GARAGE_H
#define GARAGE_H

#include "emptypoint.h"
#include "truck.h"

class Truck;


class Garage: public EmptyPoint
{
    Q_OBJECT
public:
    Garage(QPoint pos);
    Garage(const Garage& g);
    ~Garage();
    QRectF boundingRect() const override;

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget) override;

    QPoint getPos() override;
    QVector <Road*> getRoads() override;
    void addRoad(Road* r) override;
    void setNumber(unsigned int number) override;

    QVector<Truck*> getTrucks();

private:
    unsigned int number;
    QPoint pos;
    QVector <Road*> roads;
    QVector <Truck*> trucks;

public Q_SLOTS:
    void getOrder(Office* office, unsigned int nForest);

};

#endif // GARAGE_H

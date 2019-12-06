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
    ~Garage();
    QRectF boundingRect() const override;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget) override;

    QPoint getPos() override;
    QVector <Road*> getRoads() override;
    void addRoad(Road* r) override;

    QVector<Truck*> getTrucks();

private:
    QPoint pos;
    QVector <Road*> roads;
    QVector <Truck*> trucks;

public slots:
    void getOrder();

};

#endif // GARAGE_H

#ifndef GARAGE_H
#define GARAGE_H

#include "emptypoint.h"


class Garage: public EmptyPoint
{
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

private:
    QPoint pos;
    QVector <Road*> roads;

};

#endif // GARAGE_H

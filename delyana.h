#ifndef DELYANA_H
#define DELYANA_H

#include "emptypoint.h"

class Delyana : public EmptyPoint
{
public:
    explicit Delyana(QPoint pos, int cpd, int currCount, int price);
    ~Delyana() override;

    QRectF boundingRect() const override;

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget) override;

    QPoint getPos() override;
    QVector <Road*> getRoads() override;
    void addRoad(Road* r) override;
    int getCurrentCount();
    int getPrice();
    void increaceStatment();
    void contOrder(unsigned int nForest);

private:
    QPoint pos;
    QVector <Road*> roads;
    int cpd;
    int currentCount;
    int price;

};

#endif // DELYANA_H

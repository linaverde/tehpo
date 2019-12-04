#ifndef OFFICE_H
#define OFFICE_H

#include "emptypoint.h"

class Office: public EmptyPoint
{
public:
    explicit Office(QPoint pos);
    ~Office();

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

#endif // OFFICE_H

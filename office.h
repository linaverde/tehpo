#ifndef OFFICE_H
#define OFFICE_H

#include "emptypoint.h"

class Office: public EmptyPoint
{
public:
    explicit Office(QPoint pos);
    ~Office();

    QRectF boundingRect() const;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

    QPoint getPos();
    QVector <Road*> getRoads();
    void addRoad(Road* r);

private:
    QPoint pos;
    QVector <Road*> roads;

};

#endif // OFFICE_H

#ifndef DELYANA_H
#define DELYANA_H

#include "emptypoint.h"

class Delyana : public EmptyPoint
{
public:
    explicit Delyana(QPoint pos, int cpd, int currCount, int price);
    ~Delyana();

    QRectF boundingRect() const;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

private:
    QPoint pos;
    int cpd;
    int currentCount;
    int price;
};

#endif // DELYANA_H

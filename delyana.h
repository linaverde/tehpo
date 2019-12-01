#ifndef DELYANA_H
#define DELYANA_H

#include "emptypoint.h"

class Delyana : public EmptyPoint
{
public:
    explicit Delyana(QPoint pos, unsigned int cpd, unsigned int currCount, unsigned int price);
    ~Delyana();

    QRectF boundingRect() const;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

private:
    QRectF m_boundRect;
    QPoint pos;
    unsigned int cpd;
    unsigned int currentCount;
    unsigned int price;
};

#endif // DELYANA_H

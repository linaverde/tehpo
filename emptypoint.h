#ifndef EMPTYPOINT_H
#define EMPTYPOINT_H

#include <QGraphicsItem>
#include <QGraphicsView>

class EmptyPoint: public QGraphicsItem
{
public:
    EmptyPoint(QPoint pos);
    ~EmptyPoint();

    QRectF boundingRect() const;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

private:
    QPoint pos;
};

#endif // EMPTYPOINT_H

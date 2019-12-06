#ifndef EMPTYPOINT_H
#define EMPTYPOINT_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QMenu>
#include "road.h"

class Road;

class EmptyPoint: public QGraphicsItem
{
    Q_OBJECT
public:
    EmptyPoint();
    explicit EmptyPoint(QPoint pos);
    ~EmptyPoint();

    QRectF boundingRect() const;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

    virtual QPoint getPos();
    virtual QVector <Road*> getRoads();
    virtual void addRoad(Road* r);

private:
    QPoint pos;
    QVector <Road*> roads;

public slots:

};

#endif // EMPTYPOINT_H

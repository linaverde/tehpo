#ifndef EMPTYPOINT_H
#define EMPTYPOINT_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QMenu>
#include "road.h"

#define MAX_ORDER 150
#define MIN_ORDER 25

class Road;

class EmptyPoint: public QObject,  public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    EmptyPoint();
    EmptyPoint(const EmptyPoint& e);
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

};

#endif // EMPTYPOINT_H

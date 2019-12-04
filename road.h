#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include "emptypoint.h"

class EmptyPoint;

class Road : public QGraphicsItem
{
public:
    Road();
    explicit Road(EmptyPoint* start, EmptyPoint* end, unsigned int km, unsigned int price);
    ~Road();

    QRectF boundingRect() const;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

private:
    EmptyPoint* start;
    EmptyPoint* end;
    unsigned int price;
    unsigned int km;


protected:
  bool eventFilter(QObject *, QEvent *);
  void updateTip();
};

#endif // ROAD_H

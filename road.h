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
    Road(const Road& r);
    explicit Road(EmptyPoint* start, EmptyPoint* end, QPoint startP, QPoint endP,  int km, int price);
    ~Road();

    QRectF boundingRect() const override;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget) override;

    EmptyPoint* getStartPoint();
    EmptyPoint* getEndPoint();

private:
    EmptyPoint* start, *end;
    QPoint s, e;
    int price;
    int km;


protected:
  bool eventFilter(QObject *, QEvent *);
  void updateTip();
};

#endif // ROAD_H

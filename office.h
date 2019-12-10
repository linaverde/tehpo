#ifndef OFFICE_H
#define OFFICE_H

#include "emptypoint.h"

class Office: public EmptyPoint
{
    Q_OBJECT
public:
    Office();
    Office(const Office& o);
    explicit Office(QPoint pos);
    ~Office();

    QRectF boundingRect() const override;

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget) override;

    QPoint getPos() override;
    QVector <Road*> getRoads() override;
    void addRoad(Road* r) override;

    void IncreaceOrder();

private:
    QPoint pos;
    QVector <Road*> roads;
    int newOrder;
    int orderTime;

signals:
    void createOrder(Office* office, int nForest);

};

#endif // OFFICE_H

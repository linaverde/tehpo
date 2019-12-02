#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItem>
#include <QGraphicsView>


class Road : public QGraphicsItem
{
public:
    Road(QPoint start, QPoint end, unsigned int km, unsigned int price);
    ~Road();

    QRectF boundingRect() const;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

private:
    QPoint start;
    QPoint end;
    unsigned int price;
    unsigned int km;


protected:
  bool eventFilter(QObject *, QEvent *);
  void updateTip();
};

#endif // ROAD_H

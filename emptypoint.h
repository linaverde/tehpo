#ifndef EMPTYPOINT_H
#define EMPTYPOINT_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QMenu>

class EmptyPoint: public QGraphicsItem
{
public:
    EmptyPoint();
    explicit EmptyPoint(QPoint pos);
    ~EmptyPoint();

    QRectF boundingRect() const;

    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

private:
    QPoint pos;


public slots:
    //void contextMenuEvent ( QGraphicsSceneContextMenuEvent * event );
};

#endif // EMPTYPOINT_H

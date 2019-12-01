#ifndef MYGRAPHVIEW_H
#define MYGRAPHVIEW_H

#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QMenu>
#include "road.h"
#include "emptypoint.h"
#include "delyana.h"


class MyGraphView : public QGraphicsView
{
     Q_OBJECT
public:
    MyGraphView();
    ~MyGraphView();

    void addRoad(Road *road);
    void addPoint(EmptyPoint *point);


private:
    QGraphicsScene *scene;
    QVector <Road*> roads;
    QVector <EmptyPoint*> points;

    QPoint lastClicked;

public slots:
    void showContextMenu(const QPoint &pos);
    void addPointSlot();

};

#endif // MYGRAPHVIEW_H

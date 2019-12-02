#ifndef MYGRAPHVIEW_H
#define MYGRAPHVIEW_H

#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QMenu>
#include "road.h"
#include "emptypoint.h"
#include "delyana.h"
#include "dialogdelyana.h"


class MyGraphView : public QGraphicsView
{
     Q_OBJECT
public:
    MyGraphView();
    ~MyGraphView();

    void addRoad(Road *road);
    void addPoint(EmptyPoint *point);
    void deletePoint(QPoint pos);
    void addDelyan(Delyana *d);


private:
    enum Status {free, waitingForRoadEndPoint};
    Status status;
    QGraphicsScene *scene;
    QVector <Road*> roads;
    QVector <QGraphicsItem *> points;

    QPoint lastClickedRightMouseButtonPos;

public slots:
    void showContextMenu(const QPoint &pos);
    void addPointSlot();
    void deletePointSlot();
    void delyanaDialogSlot();
    void addRoadSlot();
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // MYGRAPHVIEW_H

#ifndef MYGRAPHVIEW_H
#define MYGRAPHVIEW_H

#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QMenu>
#include "emptypoint.h"
#include "delyana.h"
#include "dialogdelyana.h"
#include "dialogroad.h"
#include "office.h"
#include "garage.h"


class MyGraphView : public QGraphicsView
{
     Q_OBJECT
public:
    MyGraphView();
    ~MyGraphView();

    void addRoad(Road *);
    void addPoint(EmptyPoint *p);
    void addOffice(Office *o);
    void deletePoint(QPoint pos);
    void addDelyan(Delyana *d);
    void addGarage(Garage *g);


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
    void addOfficeSlot();
    void deletePointSlot();
    void delyanaDialogSlot();
    void addRoadSlot();
    void addGarageSlot();
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // MYGRAPHVIEW_H

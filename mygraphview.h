#ifndef MYGRAPHVIEW_H
#define MYGRAPHVIEW_H

#include <QSpinBox>
#include <QPushButton>
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QMenu>
#include "emptypoint.h"
#include "delyana.h"
#include "dialogdelyana.h"
#include "dialogroad.h"
#include "office.h"
#include "garage.h"
#include "truck.h"

#define MAX_DAY 500

class MyGraphView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphView(QSpinBox *spin, QPushButton* btn);
    ~MyGraphView();

    void addRoad(Road *);
    void addPoint(EmptyPoint *p);
    void addOffice(Office *o);
    void deletePoint(QPoint pos);
    void addDelyan(Delyana *d);
    void addGarage(Garage *g);


private:

    QGraphicsScene *scene;
    QVector <Road*> roads;
    QVector <QGraphicsItem*> points;
    QVector <Office*> offices;
    QVector <Truck*> trucks;
    Garage *g;
    QPoint lastClickedRightMouseButtonPos;
    QSpinBox *spin;
    QPushButton* btn;

    void updateNumbers();

public Q_SLOTS:
    void showContextMenu(const QPoint &pos);
    void addPointSlot();
    void addOfficeSlot();
    void deletePointSlot();
    void delyanaDialogSlot();
    void addGarageSlot();
    void setSceneStatusVector();
    void updateSceneStatus(int i);
};

#endif // MYGRAPHVIEW_H

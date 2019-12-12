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


class MyGraphView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphView(QSpinBox *s, QPushButton* btn);
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

    struct SceneStatus {
        QVector <EmptyPoint> points;
        QVector <Truck> trucks;
    };

    QGraphicsScene *scene;
    QVector <Road*> roads;
    QVector <QGraphicsItem*> points;
    QVector <Office*> offices;
    QVector <Truck*> trucks;
    QVector <SceneStatus> sceneStatus;
    Garage *g;
    QPoint lastClickedRightMouseButtonPos;
    QSpinBox *s;
    QPushButton* btn;



public Q_SLOTS:
    void showContextMenu(const QPoint &pos);
    void addPointSlot();
    void addOfficeSlot();
    void deletePointSlot();
    void delyanaDialogSlot();
    void addRoadSlot();
    void addGarageSlot();
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void setSceneStatusVector();
    void updateSceneStatus(int i);
};

#endif // MYGRAPHVIEW_H

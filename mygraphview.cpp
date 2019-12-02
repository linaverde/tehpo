#include "mygraphview.h"
#include <iostream>

MyGraphView::MyGraphView()
{
    status = free;
    /* Немного поднастроим отображение виджета и его содержимого */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignLeft|Qt::AlignTop);                        // Делаем привязку содержимого
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));

    scene = new QGraphicsScene();   // Инициализируем сцену для отрисовки
    this->setScene(scene);          // Устанавливаем сцену в виджет

}

MyGraphView::~MyGraphView(){

}

void MyGraphView::addRoad(Road *road){
    roads.push_back(road);
    this->scene->addItem(road);
    scene->update();
}

void MyGraphView::addPoint(EmptyPoint *point){
    points.push_back(point);
    this->scene->addItem(point);
    scene->update();
}

void MyGraphView::deletePoint(QPoint pos){
    QGraphicsItem *item = scene->itemAt(pos, QTransform());
    for(int i = 0; i < points.length(); i++){
        if (points.at(i) == item){
            points.remove(i);
            break;
        }
    }
    scene->removeItem(item);
    delete item;
    scene->update();
}

void MyGraphView::showContextMenu(const QPoint &pos){
    lastClickedRightMouseButtonPos = pos;
    if (status == free){
        QGraphicsItem *item = scene->itemAt(pos, QTransform());
        if (item == nullptr || !points.contains(item)){
            QMenu contextMenu(tr("Context menu"), this);
            QAction addPoint("Добавить вершину", this);
            QAction addDelyana("Добавить деляну", this);
            connect(&addPoint, SIGNAL(triggered()), this, SLOT(addPointSlot()));
            connect(&addDelyana, SIGNAL(triggered()), this, SLOT(delyanaDialogSlot()));
            contextMenu.addAction(&addPoint);
            contextMenu.addAction(&addDelyana);
            contextMenu.exec(mapToGlobal(pos));
        } else if (points.contains(item)){
            QMenu contextMenu(tr("Context menu"), this);
            QAction createRoad("Создать дорогу", this);
            QAction remove("Удалить", this);
            connect(&remove, SIGNAL(triggered()), this, SLOT(deletePointSlot()));
            connect(&createRoad, SIGNAL(triggered()), this, SLOT(addRoadSlot()));
            contextMenu.addAction(&createRoad);
            contextMenu.addAction(&remove);
            contextMenu.exec(mapToGlobal(pos));
        }
    }
}

void MyGraphView::addRoadSlot(){
    status = waitingForRoadEndPoint;

}

void MyGraphView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->pos());
    if (item != nullptr && status == waitingForRoadEndPoint) {
        addRoad(new Road(lastClickedRightMouseButtonPos, event->pos(), 99, 9));
        status = free;
    }
}

void MyGraphView::addPointSlot(){
    addPoint(new EmptyPoint(lastClickedRightMouseButtonPos));
}

void MyGraphView::deletePointSlot(){
    deletePoint(lastClickedRightMouseButtonPos);
}

void MyGraphView::delyanaDialogSlot(){
    DialogDelyana *d = new DialogDelyana(this);
    if (d->exec() == QDialog::Accepted){
        addDelyan(new Delyana(lastClickedRightMouseButtonPos, d->getCpd(), d->getCurr(), d->getPrice()));
    }
}

void MyGraphView::addDelyan(Delyana *d){
    scene->addItem(d);
    points.push_back(d);
    scene->update();
}

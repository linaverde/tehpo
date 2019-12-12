#include "mygraphview.h"
#include <iostream>
#include <QErrorMessage>

MyGraphView::MyGraphView(QSpinBox *s, QPushButton* btn)
{
    this->status = free;
    this->g = nullptr;
    this->s = s;
    this->btn = btn;
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

bool hasRoad(EmptyPoint* p, QVector <Road*> roads){
    for (Road* r: roads) {
        if(r->getPoints().first == p || r->getPoints().second == p){
            return true;
        }
    }
    return false;
}

void MyGraphView::addRoad(Road *r){
    roads.push_back(r);
    this->scene->addItem(r);
    scene->update();
}

void MyGraphView::addPoint(EmptyPoint *p){
    points.push_back(p);
    this->scene->addItem(p);
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
            QAction addOffice("Добавить контору", this);
            QAction addGarage("Добавить гараж", this);
            connect(&addPoint, SIGNAL(triggered()), this, SLOT(addPointSlot()));
            connect(&addOffice, SIGNAL(triggered()), this, SLOT(addOfficeSlot()));
            connect(&addDelyana, SIGNAL(triggered()), this, SLOT(delyanaDialogSlot()));
            contextMenu.addAction(&addPoint);
            contextMenu.addAction(&addOffice);
            contextMenu.addAction(&addDelyana);
            if (this->g == nullptr){
                contextMenu.addAction(&addGarage);
                connect(&addGarage, SIGNAL(triggered()), this, SLOT(addGarageSlot()));
            }
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
    if (EmptyPoint *end = dynamic_cast<EmptyPoint*>(itemAt(event->pos()))){
        if (end != nullptr && status == waitingForRoadEndPoint) {
            EmptyPoint *start = dynamic_cast<EmptyPoint*>(itemAt(lastClickedRightMouseButtonPos));
            if (start != end){
                if (!hasRoad(end, start->getRoads())){
                    DialogRoad *d = new DialogRoad(this);
                    if (d->exec() == QDialog::Accepted){
                        Road *r = new Road(start, end, lastClickedRightMouseButtonPos, event->pos(), d->getKm(), d->getPrice());
                        addRoad(r);
                        start->addRoad(r);
                        end->addRoad(r);
                        scene->removeItem(start);
                        scene->addItem(start);
                        scene->removeItem(end);
                        scene->addItem(end);
                        scene->update();
                    }
                } else {
                    QErrorMessage *e = new QErrorMessage(this);
                    e->setWindowTitle("Ошибка создания дороги");
                    e->showMessage("Такая дорога уже существует!");
                }
            } else {
                QErrorMessage *e = new QErrorMessage(this);
                e->setWindowTitle("Ошибка создания дороги");
                e->showMessage("Нельзя провести дорогу в ту же точку");
            }
        }
    }
    status = free;
}

void MyGraphView::addPointSlot(){
    addPoint(new EmptyPoint(lastClickedRightMouseButtonPos));
}

void MyGraphView::deletePointSlot(){
    deletePoint(lastClickedRightMouseButtonPos);
}

void MyGraphView::addOfficeSlot(){
    addOffice(new Office(lastClickedRightMouseButtonPos));
}

void MyGraphView::addGarageSlot(){
    addGarage(new Garage(lastClickedRightMouseButtonPos));
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

void MyGraphView::addOffice(Office *o){
    scene->addItem(o);
    offices.push_back(o);
    points.push_back(o);
    scene->update();
}

void MyGraphView::addGarage(Garage *g){
    scene->addItem(g);
    points.push_back(g);
    this->g = g;
    scene->update();
}


void MyGraphView::setSceneStatusVector(){
    scene->addItem(g->getTrucks().at(0));
    if (this->g == nullptr){
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle("Ошибка запуска приложения");
        e->showMessage("На карте нет гаража!");
    } else {
        s->setEnabled(true);
        btn->setEnabled(false);
        connect(this->s, SIGNAL(valueChanged(int)), this, SLOT(updateSceneStatus(int)));
        for (Office *f: offices){
            connect(f, SIGNAL(createOrder(const Office&, unsigned int)), g, SLOT(getOrder(const Office&, unsigned int)));
        }
        for (int i = 0; i < 100; i++){
            SceneStatus s;
            for(Office *o: offices){
                s.points.push_back(o->increaceStatement());
            }
            for(Truck *t: g->getTrucks()){
                s.trucks.push_back(t->increaceStatment());
            }
            sceneStatus.push_back(s);
        }
    }
}

void MyGraphView::updateSceneStatus(int i){
    for(QGraphicsItem *item: scene->items()){
        if (dynamic_cast<Truck*>(item) || dynamic_cast<Office*>(item)){
            scene->removeItem(item);
            scene->update();
        }
    }

    SceneStatus current = sceneStatus.at(i);
    for (EmptyPoint p : current.points){
        EmptyPoint *point = &p;
        scene->addItem(point);
        scene->update();
    }
    for (Truck t: current.trucks){
        if (t.getTruckStatus() == 1){
            Truck* tr = &t;
            scene->addItem(tr);
             scene->update();
        }
    }

    scene->update();
}

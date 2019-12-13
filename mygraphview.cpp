#include "mygraphview.h"
#include <iostream>
#include <QErrorMessage>
#include "roadlengthtabledialog.h"
#include "roadpricetabledialog.h"

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

MyGraphView::MyGraphView(QSpinBox *s, QPushButton* btn)
{
    this->g = nullptr;
    this->spin = s;
    spin->setMaximum(MAX_DAY);
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
    if (dynamic_cast<Garage*>(item)){
        g = nullptr;
    }
    delete item;
    scene->update();
}

void MyGraphView::updateNumbers(){
    for (int i = 0; i < scene->items().length(); i++){
        EmptyPoint *e = dynamic_cast<EmptyPoint*>(scene->items().at(i));
        e->setNumber(i+1);
    }
    scene->update();
}

void MyGraphView::showContextMenu(const QPoint &pos){
    lastClickedRightMouseButtonPos = pos;
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
        QAction remove("Удалить", this);
        connect(&remove, SIGNAL(triggered()), this, SLOT(deletePointSlot()));
        contextMenu.addAction(&remove);
        contextMenu.exec(mapToGlobal(pos));
    }

}


void MyGraphView::addPointSlot(){
    addPoint(new EmptyPoint(lastClickedRightMouseButtonPos));
    updateNumbers();
}

void MyGraphView::deletePointSlot(){
    deletePoint(lastClickedRightMouseButtonPos);
    updateNumbers();
}

void MyGraphView::addOfficeSlot(){
    addOffice(new Office(lastClickedRightMouseButtonPos));
    updateNumbers();
}

void MyGraphView::addGarageSlot(){
    addGarage(new Garage(lastClickedRightMouseButtonPos));
    updateNumbers();
}


void MyGraphView::delyanaDialogSlot(){
    DialogDelyana *d = new DialogDelyana(this);
    if (d->exec() == QDialog::Accepted){
        addDelyan(new Delyana(lastClickedRightMouseButtonPos, d->getCpd(), d->getCurr(), d->getPrice()));
    }
    updateNumbers();
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
    if (this->g == nullptr){

        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle("Ошибка запуска приложения");
        e->showMessage("На карте нет гаража!");

    } else {

        QList <EmptyPoint*>* list = new QList <EmptyPoint*>;

        for (QGraphicsItem *item: scene->items()){

            if (dynamic_cast<EmptyPoint*>(item)){
                EmptyPoint* e = dynamic_cast<EmptyPoint*>(item);
                list->push_back(e);
            }
        }

        int * count = new int;
        *count = list->length();

        RoadLengthTableDialog *roadLengthDialog = new RoadLengthTableDialog(nullptr, count);
        if (roadLengthDialog->exec() == QDialog::Accepted){

            QVector<QVector<int>> kmMatrix = roadLengthDialog->getKmMatrix();
            RoadPriceTableDialog *roadPriceDialog = new RoadPriceTableDialog(nullptr, &kmMatrix, count);

            if (roadPriceDialog->exec() == QDialog::Accepted){

                QVector<QVector<int>> priceMatrix  = roadPriceDialog->getPriceMatrix();

                for (int i = 1; i < list->length(); i++){
                    for (int j = 0; j < i; j ++){
                        if (kmMatrix.at(i).at(j) != 0){
                            addRoad(new Road(list->at(i), list->at(j), list->at(i)->getPos(), list->at(j)->getPos(), kmMatrix.at(i).at(j), priceMatrix.at(i).at(j)));
                        }
                    }
                }

                spin->setEnabled(true);
                btn->setEnabled(false);
                connect(this->spin, SIGNAL(valueChanged(int)), this, SLOT(updateSceneStatus(int)));

                for (Office *f: offices){
                    connect(f, SIGNAL(createOrder(Office*, unsigned int)), g, SLOT(getOrder(Office*, unsigned int)));
                }
                for (Truck *t: g->getTrucks()){
                    scene->addItem(t);
                    t->setVisible(false);
                }
            }
        }
    }
}

void MyGraphView::updateSceneStatus(int i){
    spin->setMinimum(i);

    for (QGraphicsItem *item: scene->items()){
        if (dynamic_cast<Office*>(item)){
            Office *o = dynamic_cast<Office*>(item);
            o->increaceStatement();
        } else if (dynamic_cast<Truck*>(item)){
            Truck *t = dynamic_cast<Truck*>(item);
            t->increaceStatment(scene);
        } else if (dynamic_cast<Delyana*>(item)){
            Delyana *d = dynamic_cast<Delyana*>(item);
            d->increaceStatment();
        }
    }

    scene->update();
}

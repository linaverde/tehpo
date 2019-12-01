#include "mygraphview.h"

MyGraphView::MyGraphView()
{
    /* Немного поднастроим отображение виджета и его содержимого */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignLeft|Qt::AlignTop);                        // Делаем привязку содержимого
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));

    scene = new QGraphicsScene();   // Инициализируем сцену для отрисовки
    this->setScene(scene);          // Устанавливаем сцену в виджет

    Delyana *d = new Delyana(QPoint(200,200), 40, 200, 150);
    scene->addItem(d);

    //Road *firstRoad = new Road(10, 10, 180, 180, 120, 80);
    //scene->addItem(firstRoad);
    //EmptyPoint *firstPoint = new EmptyPoint(QPoint(20, 20));
    //scene->addItem(firstPoint);
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

void MyGraphView::showContextMenu(const QPoint &pos){
    lastClicked = pos;
    QMenu contextMenu(tr("Context menu"), this);
    QAction addPoint("Добавить вершину", this);
    connect(&addPoint, SIGNAL(triggered()), this, SLOT(addPointSlot()));
    contextMenu.addAction(&addPoint);

    contextMenu.exec(mapToGlobal(pos));
}

void MyGraphView::addPointSlot(){
    addPoint(new EmptyPoint(lastClicked));
}

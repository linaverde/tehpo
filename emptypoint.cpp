#include "emptypoint.h"

EmptyPoint::EmptyPoint(){

}

EmptyPoint::EmptyPoint(QPoint pos)
{
    this->pos = pos;
}

EmptyPoint::~EmptyPoint(){

}

void EmptyPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QRect r(0,0, 10,10);
    painter->drawEllipse(r);
    this->setPos(pos);
}

QRectF EmptyPoint::boundingRect() const{
    return QRectF(0, 0, 10, 10);
}

//void EmptyPoint::contextMenuEvent ( QGraphicsSceneContextMenuEvent * event ){
//    QMenu menu;
//    QAction *removePoint = menu.addAction("Удалить вершину");
//    QAction *addRoad = menu.addAction("Добавить дорогу");
//    menu.exec(QCursor::pos());
//    //contextMenu.exec(mapToGlobal(pos));
//}

//void EmptyPoint::showContextMenu(QPoint *pos){
//    QMenu menu;
//    QAction *removePoint = menu.addAction("Удалить вершину");
//    QAction *addRoad = menu.addAction("Добавить дорогу");
//    menu.exec(QCursor::pos());
//}

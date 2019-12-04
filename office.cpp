#include "office.h"

Office::Office(QPoint pos)
{
    this->pos = pos;
}

Office::~Office(){

}

void Office::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QPixmap pixmap;
    if (pixmap.load("D:/qt/projects/tehrazpo/office.jpg"))
    {
        QRect r (0, 0, 30, 30);
        painter->drawPixmap(r, pixmap);
        this->setPos(pos);
    }
}

QRectF Office::boundingRect() const{
    return QRectF(0, 0, 30, 30);
}

QPoint Office::getPos(){
    return pos;
}


QVector <Road*> Office::getRoads(){
    return roads;
}

void Office::addRoad(Road* r){
    roads.push_back(r);
}

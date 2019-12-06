#include "office.h"
#include "garage.h"

Office::Office(){

}
Office::Office(QPoint pos)
{
    this->pos = pos;
    newOrder =  (qrand() % ((25 + 1) - 0) + 0);
    orderTime = (qrand() % ((100 + 1) - 0) + 0);
    //Garage* g;
    //connect (this, SIGNAL(createOrder()), g, SLOT(getOrder)));
}

Office::Office(const Office& o){
    this->pos = o.pos;
    this->newOrder = o.newOrder;
    this->orderTime = o.orderTime;
    this->roads = o.roads;
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

void Office::IncreaceOrder(){
    orderTime += newOrder;
    if (orderTime >= 100){
        orderTime -= 100;
        emit createOrder();
    }
}

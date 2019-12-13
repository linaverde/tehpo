#include "office.h"
#include "garage.h"

Office::Office(){

}
Office::Office(QPoint pos)
{
    this->pos = pos;
    newOrder =  (qrand() % ((25 + 1) - 1) + 1);
    orderTime = (qrand() % ((100 + 1) - 1) + 1);
    //Garage* g;
    //connect (this, SIGNAL(createOrder()), g, SLOT(getOrder)));
}

Office::Office(const Office& o) : EmptyPoint (o){
    this->pos = o.pos;
    this->newOrder = o.newOrder;
    this->orderTime = o.orderTime;
    this->roads = o.roads;
}

Office::~Office(){

}

void Office::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QPixmap pixmap;
    if (pixmap.load(":images/office.jpg"))
    {
        QRect r (0, 0, 30, 30);
        painter->drawPixmap(r, pixmap);
        QPen pen(Qt::black, 2);
        painter->setPen(pen);
        painter->drawText(QPoint(0, 0), QString::number(number));
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

Office Office::increaceStatement(){
    this -> orderTime = this->orderTime + this->newOrder;
    if (this->orderTime >= 100){
        this->orderTime -= 100;
        unsigned int order = (qrand() % ((MAX_ORDER + 1) - MIN_ORDER) + MIN_ORDER);
        createOrder(this, order);
    }
    return *this;
}

void Office::setNumber(unsigned int number){
    this->number = number;
}


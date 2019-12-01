#include "delyana.h"

#include <iostream>

Delyana::Delyana(QPoint pos, unsigned int cpd, unsigned int currCount, unsigned int price)
{
    this->pos = pos;
    this->cpd = cpd;
    this->currentCount = currCount;
    this->price = price;
    this->setToolTip(QString::number(currCount) + " ед. леса<br>Цена за ед.: "
                     + QString::number(price) + "руб<br>Выработка " + QString::number(cpd) + "ед. в день");
}

Delyana::~Delyana(){

}

void Delyana::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    /*QPen pen(Qt::red, 4);
    painter->setPen(pen);
    painter->draw; */

    QPixmap pixmap;
    if (pixmap.load("D:/qt/projects/tehrazpo/tree.jpg"))
    {
        QRect r (0, 0, 20, 30);
        r.moveTopLeft(pos);
        painter->drawPixmap(r, pixmap);
        this->setToolTip(QString::number(currentCount) + " ед. леса<br>Цена за ед.: "
                         + QString::number(price) + "руб<br>Выработка " + QString::number(cpd) + "ед. в день");
    }
}

QRectF Delyana::boundingRect() const{
    return QRectF(0, 0, 20, 30);
}
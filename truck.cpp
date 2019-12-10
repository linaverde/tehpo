#include "truck.h"
#include <QList>
#include <QPair>

Truck::Truck(){

}
Truck::Truck (const Truck& t){
    this->s = t.s;
    this->pos = t.pos;
    this->capacity = t.capacity;
    this->homeGarage = t.homeGarage;
    this->currentRoad = t.currentRoad;
    this->speedPerDay = t.speedPerDay;
}

Truck::Truck(Garage* garagePosition, unsigned int speedPerDay, unsigned int capacity)
{
    this->homeGarage = garagePosition;
    this->speedPerDay = speedPerDay;
    this->capacity = capacity;
}

QRectF Truck::boundingRect() const {
    return QRectF(0, 0, 40, 30);
}

void Truck::paint(QPainter * painter,
                  const QStyleOptionGraphicsItem * option,
                  QWidget * widget){
    QPixmap pixmap;
    if (pixmap.load(":images/truck.png"))
    {
        QRect r (0, 0, 40, 30);
        painter->drawPixmap(r, pixmap);
        this->setPos(pos);
    }
}

void Truck::setPosition(QPoint pos){
    this->setPos(pos);
}

QList <EmptyPoint*>* Truck::createWayToDelyana(unsigned int nForest){
    EmptyPoint* currentPoint = this->currentPoint;
    QVector<std::tuple<QList<EmptyPoint*>, int, bool>> possibleWay;

    //добавление первых вариантов вне цикла
    foreach (Road *r, currentPoint->getRoads()) { //для каждой дороги в текущей точке

        QList<EmptyPoint*> l; //создаем список
        l.push_back(currentPoint); //помещаем в список текущую вершину
        EmptyPoint* nextPoint;
        r->getPoints().first == currentPoint ? nextPoint = r->getPoints().second : nextPoint = r->getPoints().first; //выбираем вторую вершину помимо текущей для каждой дороги
        l.push_back(nextPoint); //помещаем её в список
        possibleWay.push_back(std::make_tuple(l, r->getPrice(), false)); //добавляем список в вектор, цена это проезд по дороге, путь не проложен до конца

        if (dynamic_cast<Delyana*>(nextPoint)){ //если вершина окончания пути - это деляна
            Delyana* nextD = dynamic_cast<Delyana*>(nextPoint); //кастуем вершину к деляне

            if (nextD->getCurrentCount() <= nForest){ //проверяем, что в деляне хватает дерева

                std::tuple<QList<EmptyPoint*>, int, bool> crossroad = possibleWay.last(); //копируем проложенный путь
                std::get<1>(possibleWay.last()) = std::get<1>(possibleWay.last()) + nForest*nextD->getPrice(); // прибавляем к стоимости пути закупку леса в деляне
                std::get<2>(possibleWay.last()) = true; //оставляем пометку, что маршрут проложен
                possibleWay.push_back(crossroad); //добавляем в вектор развилку
            }
        }
    }

    bool hasCalculatedWay = false;

    while (!hasCalculatedWay){ //в цикле продолжаем построение маршрутов
        auto currentState = possibleWay; //создаем копию вектора во избежание добавления во время пробега по нему
        foreach (auto t, currentState){ //выбираем каждый из существующих

            if (std::get<2>(t) == false){ //если маршрут проложен не до конца

                currentPoint = std::get<0>(t).last(); //берем вершину списка за текущее положение
                foreach(Road* r, currentPoint->getRoads()){
                    EmptyPoint* nextPoint;
                    r->getPoints().first == currentPoint ? nextPoint = r->getPoints().second : nextPoint = r->getPoints().first; //выбираем вторую вершину

                    if(!std::get<0>(t).contains(nextPoint)){ //если вторая вершина не пройдена

                        auto newWay = t; //копируем возможный путь
                        std::get<0>(newWay).push_back(nextPoint); //добавляем в него новую вершину
                        std::get<1>(newWay) = std::get<1>(newWay) + r->getPrice(); //прибавляем к цене стоимость проезда

                        if (dynamic_cast<Delyana*>(nextPoint)){ //новая вершина - деляна

                            Delyana* nextD = dynamic_cast<Delyana*>(nextPoint); //кастуем вершину к деляне

                            if (nextD->getCurrentCount() <= nForest){ //проверяем, что в деляне хватает дерева

                                std::tuple<QList<EmptyPoint*>, int, bool> crossroad = newWay; //копируем проложенный путь
                                std::get<1>(newWay) = std::get<1>(newWay) + nForest*nextD->getPrice(); // прибавляем к стоимости пути закупку леса в деляне
                                std::get<2>(newWay) = true; //оставляем пометку, что маршрут проложен
                                possibleWay.push_back(crossroad); //добавляем в вектор развилку, где путь проложен только до деляны
                            }

                        }

                        possibleWay.push_back(newWay); //добавляем в вектор новый путь с +1 вершиной
                    }
                    possibleWay.removeOne(t); //удаляем путь, так как добавили все возможные его продолжения
                }
                //возможно вторая ветка не нужна
            } else { //если выбранный маршрут в векторе проложен до конца

                if(!dynamic_cast<Delyana*>(std::get<0>(t).last())){ //если последняя вершина в пути не кастуется в деляну
                    possibleWay.removeOne(t); //убираем её из списка возможных путей
                }
            }

            //условие для выхода из цикла
            foreach(auto way, possibleWay){
                //проверяем, что еще существуют пути, не проложенные до конца
                hasCalculatedWay = true;
                if (std::get<2>(way) == false){
                    hasCalculatedWay = false;
                    break;
                }

            }
        }
    }

    if (possibleWay.isEmpty()){
        return nullptr;
    }

    //выбор минимального по стоимости пути из возможных и возврат его
    auto min = possibleWay.at(0);
    foreach(auto t, possibleWay){
        if (std::get<1>(t) < std::get<1>(min)){
            min = t;
        }
    }

    return &std::get<0>(min);
}




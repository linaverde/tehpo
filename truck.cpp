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
    this->speed = t.speed;
}

Truck::Truck(Garage* garagePosition, unsigned int speedPerDay, unsigned int capacity)
{
    this->homeGarage = garagePosition;
    this->speed = speedPerDay;
    this->capacity = capacity;
    this->s = rest;
    this->pos = homeGarage->getPos();
    this->setVisible(false);

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
    this->pos = pos;
    this->setPos(this->pos);
}

Truck::status Truck::getTruckStatus(){
    return s;
}

Truck Truck::increaceStatment(QGraphicsScene *scene){
    if (!currentWay.isEmpty()){
        this->setPosition(currentWay.at(0));
        if (scene->itemAt(currentWay.at(0), QTransform()) == currDestinationDelyana){
            currDestinationDelyana->contOrder(nForest);
        }
        currentWay.removeAt(0);
        this->setToolTip("Заказ на " + QString::number(this->nForest) + " ед. леса <br>Сумма за поездку: "+ QString::number(this->currentOrderSum));
    } else {
        this->s = rest;
        this->setVisible(false);
        this->setPosition(homeGarage->getPos());
    }
    return *this;
}

unsigned int Truck::getCapacity(){
    return capacity;
}

void Truck::getOrder(Office *office, unsigned int nForest){
    currentOrderSum = 0;
    currDestinationOffice = office;
    QList<EmptyPoint*> way= createWayToDelyana(nForest);
    if (!way.isEmpty()){
        currDestinationDelyana = dynamic_cast<Delyana*>(way.last());
        QList <EmptyPoint*> wayBack = createWayToOffice(way.last());
        if (!wayBack.isEmpty()){
            way += wayBack;
            currentWay = calculateCurrWayPoints(way);
            s = out;
            this->nForest = nForest;
            this->setVisible(true);
        }
    }
}

}

QPoint calculatePoint (QPoint s, QPoint e, float percent){
    //рассчет положения грузовика мать его за ногу по формулам из геометрии за 7-8-9 класс я бы хотела их забыть нафиг
    //Тут нужно немного вспомнить начальную геометрию
    //Если взять линию из первой точки до последней за гипотенузу,
    //сможем "дорисовать" из линии прямоугольный треугольник, получим его "ширину" и "высоту"
    int triangleWidth = e.x() - s.x();
    int triangleHeight = e.y() - s.y();
    //Очевидно (из теоремы Пифагора), что если оба катета умножить на одно число,
    //то и гипотенуза увеличится в такое же количесвто раз
    //Находим катеты для текущей длины линии
    float currentWidth = triangleWidth * percent;
    float currentHeight = triangleHeight * percent;
    //Ну и тут уже получаем текущие координаты конца линии.
    QPoint resultPoint(s.x() + currentWidth, s.y() + currentHeight);
    return resultPoint;
}

QList <QPoint> Truck::calculateCurrWayPoints(QList<EmptyPoint*> way){
    int i = 1;
    QList <QPoint> l;
    bool cycle = true;
    float roadPercent = 0;
    float percentForIteration;

    QPoint s = way.at(0)->getPos(); //старт отсчета
    QPoint e = way.at(1)->getPos(); //конец отсчета

    Road *road;
    for (Road *r:  way.at(0)->getRoads()){
        if (r->getPoints().first == way.at(1) || r->getPoints().second == way.at(1)){
            road = r;
            break;
        }
    }

    percentForIteration = (float) this->speed / (float) road->getKm();

    while (cycle){
        roadPercent += percentForIteration;
        if (roadPercent < 1) {
            l.push_back(calculatePoint(s, e, roadPercent));
        } else {
            if ((i + 1) < way.length()) {
                i++;
                roadPercent = 0;
                s = way.at(i-1)->getPos();
                e = way.at(i)->getPos();
                for (Road *r:  way.at(i-1)->getRoads()){
                    if (r->getPoints().first == way.at(i) || r->getPoints().second == way.at(i)){
                        road = r;
                        break;
                    }
                }
                percentForIteration = (float) this->speed / (float) road->getKm();
                l.push_back(calculatePoint(s, e, roadPercent));
            } else {
                roadPercent = 1;
                l.push_back(calculatePoint(s, e, roadPercent));
                cycle = false;
            }
        }
    }

    return l;
}

QList <EmptyPoint*> Truck::createWayToDelyana(unsigned int nForest){

    EmptyPoint* currentPoint = homeGarage;
    QVector<std::tuple<QList<EmptyPoint*>, int, bool>> possibleWay;

    //добавление первых вариантов вне цикла
    for(Road *r: currentPoint->getRoads()) { //для каждой дороги в текущей точке

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
        for (auto t: currentState){ //выбираем каждый из существующих

            if (std::get<2>(t) == false){ //если маршрут проложен не до конца

                currentPoint = std::get<0>(t).last(); //берем вершину списка за текущее положение
                for(Road* r: currentPoint->getRoads()){
                    EmptyPoint* nextPoint;
                    r->getPoints().first == currentPoint ? nextPoint = r->getPoints().second : nextPoint = r->getPoints().first; //выбираем вторую вершину

                    if(!std::get<0>(t).contains(nextPoint)){ //если вторая вершина не пройдена

                        auto newWay = t; //копируем возможный путь
                        std::get<0>(newWay).push_back(nextPoint); //добавляем в него новую вершину
                        std::get<1>(newWay) = std::get<1>(newWay) + r->getPrice(); //прибавляем к цене стоимость проезда
                        std::get<2>(newWay) = false;

                        if (dynamic_cast<Delyana*>(nextPoint)){ //новая вершина - деляна

                            Delyana* nextD = dynamic_cast<Delyana*>(nextPoint); //кастуем вершину к деляне

                            if (nextD->getCurrentCount() >= nForest){ //проверяем, что в деляне хватает дерева

                                std::tuple<QList<EmptyPoint*>, int, bool> crossroad = newWay; //копируем проложенный путь
                                std::get<1>(newWay) = std::get<1>(newWay) + nForest*nextD->getPrice(); // прибавляем к стоимости пути закупку леса в деляне
                                std::get<2>(newWay) = true; //оставляем пометку, что маршрут проложен
                                possibleWay.push_back(crossroad); //добавляем в вектор развилку, где путь проложен только до деляны
                            }

                        }

                        possibleWay.push_back(newWay); //добавляем в вектор новый путь с +1 вершиной
                    }

                }
                possibleWay.removeOne(t); //удаляем путь, так как добавили все возможные его продолжения
            } else { //если выбранный маршрут в векторе проложен до конца

                if(!dynamic_cast<Delyana*>(std::get<0>(t).last())){ //если последняя вершина в пути не кастуется в деляну
                    possibleWay.removeOne(t); //убираем её из списка возможных путей
                }
            }

            //условие для выхода из цикла
            for(auto way: possibleWay){
                //проверяем, что еще существуют пути, не проложенные до конца
                hasCalculatedWay = true;
                if (std::get<2>(way) == false){
                    hasCalculatedWay = false;
                    break;
                }

            }
        }
    }

    QList <EmptyPoint*> resultWay;

    if (possibleWay.isEmpty()){
        return resultWay;
    }

    //выбор минимального по стоимости пути из возможных и возврат его
    auto min = possibleWay.at(0);
    for(auto t: possibleWay){
        if (std::get<1>(t) < std::get<1>(min)){
            min = t;
        }
    }

    resultWay = std::get<0>(min);
    currentOrderSum += std::get<1>(min);

    return resultWay;
}

QList <EmptyPoint*> Truck::createWayToOffice(EmptyPoint* lastP){
    EmptyPoint* currentPoint = lastP;
    QVector<std::tuple<QList<EmptyPoint*>, int, bool>> possibleWay;

    //добавление первых вариантов вне цикла
    for(Road *r: currentPoint->getRoads()) { //для каждой дороги в текущей точке

        QList<EmptyPoint*> l; //создаем список
        l.push_back(currentPoint); //помещаем в список текущую вершину
        EmptyPoint* nextPoint;
        r->getPoints().first == currentPoint ? nextPoint = r->getPoints().second : nextPoint = r->getPoints().first; //выбираем вторую вершину помимо текущей для каждой дороги
        l.push_back(nextPoint); //помещаем её в список
        possibleWay.push_back(std::make_tuple(l, r->getPrice(), false)); //добавляем список в вектор, цена это проезд по дороге, путь не проложен до конца

        if (dynamic_cast<Office*>(nextPoint)){ //если вершина окончания пути - это контора
            Office* office = dynamic_cast<Office*>(nextPoint); //кастуем вершину к деляне

            if (office == currDestinationOffice){ //проверяем, что это необходимая нам контора

                std::tuple<QList<EmptyPoint*>, int, bool> crossroad = possibleWay.last(); //копируем проложенный путь
                std::get<2>(possibleWay.last()) = true; //оставляем пометку, что маршрут проложен
                possibleWay.push_back(crossroad); //добавляем в вектор развилку
            }
        }
    }

    bool hasCalculatedWay = false;

    while (!hasCalculatedWay){ //в цикле продолжаем построение маршрутов
        auto currentState = possibleWay; //создаем копию вектора во избежание добавления во время пробега по нему
        for (auto t: currentState){ //выбираем каждый из существующих

            if (std::get<2>(t) == false){ //если маршрут проложен не до конца

                currentPoint = std::get<0>(t).last(); //берем вершину списка за текущее положение
                for(Road* r: currentPoint->getRoads()){
                    EmptyPoint* nextPoint;
                    r->getPoints().first == currentPoint ? nextPoint = r->getPoints().second : nextPoint = r->getPoints().first; //выбираем вторую вершину

                    if(!std::get<0>(t).contains(nextPoint)){ //если вторая вершина не пройдена

                        auto newWay = t; //копируем возможный путь
                        std::get<0>(newWay).push_back(nextPoint); //добавляем в него новую вершину
                        std::get<1>(newWay) = std::get<1>(newWay) + r->getPrice(); //прибавляем к цене стоимость проезда
                        std::get<2>(newWay) = false;

                        if (dynamic_cast<Office*>(nextPoint)){ //новая вершина - контора

                            Office* office = dynamic_cast<Office*>(nextPoint); //кастуем вершину к конторе

                            if (office->getPos() == currDestinationOffice->getPos()){ //проверяем, что эта контора назначения

                                std::tuple<QList<EmptyPoint*>, int, bool> crossroad = newWay; //копируем проложенный путь
                                std::get<2>(newWay) = true; //оставляем пометку, что маршрут проложен
                                possibleWay.push_back(crossroad); //добавляем в вектор развилку, где путь проложен только до деляны
                            }

                        }

                        possibleWay.push_back(newWay); //добавляем в вектор новый путь с +1 вершиной
                    }

                }
                possibleWay.removeOne(t); //удаляем путь, так как добавили все возможные его продолжения
            } else { //если выбранный маршрут в векторе проложен до конца

                if(!dynamic_cast<Office*>(std::get<0>(t).last())){ //если последняя вершина в пути не кастуется в контору
                    possibleWay.removeOne(t); //убираем её из списка возможных путей
                }
            }

            //условие для выхода из цикла
            for(auto way: possibleWay){
                //проверяем, что еще существуют пути, не проложенные до конца
                hasCalculatedWay = true;
                if (std::get<2>(way) == false){
                    hasCalculatedWay = false;
                    break;
                }

            }
        }
    }

    QList <EmptyPoint*> resultWay;

    if (possibleWay.isEmpty()){
        return resultWay;
    }

    //выбор минимального по стоимости пути из возможных и возврат его
    auto min = possibleWay.at(0);
    for(auto t: possibleWay){
        if (std::get<1>(t) < std::get<1>(min)){
            min = t;
        }
    }

    currentOrderSum += std::get<1>(min);
    resultWay = std::get<0>(min);
    resultWay.removeAt(0); //убираем последнюю, так как она уже сохранена в пути на предыдущем этапе рассчетов

    return resultWay;
}




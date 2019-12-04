#ifndef DIALOGROAD_H
#define DIALOGROAD_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class DialogRoad;
}

class DialogRoad : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRoad(QWidget *parent = nullptr);
    ~DialogRoad();

    int getKm();
    int getPrice();

private:
    Ui::DialogRoad *ui;
    QIntValidator valya;
};

#endif // DIALOGROAD_H

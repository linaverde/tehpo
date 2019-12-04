#ifndef DIALOGROAD_H
#define DIALOGROAD_H

#include <QDialog>

namespace Ui {
class DialogRoad;
}

class DialogRoad : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRoad(QWidget *parent = nullptr);
    ~DialogRoad();

private:
    Ui::DialogRoad *ui;
};

#endif // DIALOGROAD_H

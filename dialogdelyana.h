#ifndef DIALOGDELYANA_H
#define DIALOGDELYANA_H

#include <QDialog>
#include "delyana.h"

namespace Ui {
class DialogDelyana;
}

class DialogDelyana : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDelyana(QWidget *parent = nullptr);
    ~DialogDelyana();
    unsigned int getCurr();
    unsigned int getCpd();
    unsigned int getPrice();

private:
    Ui::DialogDelyana *ui;
    QWidget *parent;

};

#endif // DIALOGDELYANA_H

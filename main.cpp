#include "mainwindow.h"

#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Office>();
    qsrand(QTime::currentTime().elapsed());
    MainWindow w;
    w.show();
    return a.exec();
}

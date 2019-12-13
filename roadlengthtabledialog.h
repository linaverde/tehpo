#ifndef ROADLENGTHTABLEDIALOG_H
#define ROADLENGTHTABLEDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include "emptypoint.h"

namespace Ui {
class RoadLengthTableDialog;
}

class RoadLengthTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RoadLengthTableDialog(QWidget *parent = nullptr, int* n = nullptr);
    ~RoadLengthTableDialog();

    QVector <QVector<int>> getKmMatrix();

private:
    Ui::RoadLengthTableDialog *ui;
    QTableWidget* table;
    int n;

    void createTable();

};

#endif // ROADLENGTHTABLEDIALOG_H

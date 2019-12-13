#ifndef ROADPRICETABLEDIALOG_H
#define ROADPRICETABLEDIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class RoadPriceTableDialog;
}

class RoadPriceTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RoadPriceTableDialog(QWidget *parent = nullptr, QVector<QVector<int>>* lenghtMatrix = nullptr, int* n = nullptr);
    ~RoadPriceTableDialog();

    QVector<QVector<int>> getPriceMatrix();

private:
    Ui::RoadPriceTableDialog *ui;
    QTableWidget* table;
    QVector<QVector<int>> matrix;
    int n;

    void createTable();
};

#endif // ROADPRICETABLEDIALOG_H

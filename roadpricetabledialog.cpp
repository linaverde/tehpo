#include "roadpricetabledialog.h"
#include "ui_roadpricetabledialog.h"

#include <QLineEdit>

RoadPriceTableDialog::RoadPriceTableDialog(QWidget *parent, QVector<QVector<int>>* lengthMatrix, int* n) :
    QDialog(parent),
    ui(new Ui::RoadPriceTableDialog)
{
    ui->setupUi(this);
    this->table = ui->tableWidget_2;
    this->matrix = *lengthMatrix;
    this->n = *n;
    createTable();
}

RoadPriceTableDialog::~RoadPriceTableDialog()
{
    delete ui;
}

void RoadPriceTableDialog::createTable(){
    QStringList headers;
    for (int i = 0; i < n; i++){
        headers.push_back(QString::number(i+1));
    }
    table->setRowCount(n);
    table->setColumnCount(n);

    table->setVerticalHeaderLabels(headers);
    table->setHorizontalHeaderLabels(headers);

    for (int i  = 0; i < n; i ++){
        for (int j = 0; j < i; j ++){
            QLineEdit *edit = new QLineEdit("0", nullptr);
            if (matrix.at(i).at(j) != 0){
                edit->setValidator(new QIntValidator(1, 1000, edit));
            } else {
                edit->setEnabled(false);
            }
            table->setCellWidget(i, j, edit);
        }
        for (int j = i; j < n; j++){
            QLineEdit *edit = new QLineEdit("0", nullptr);
            edit->setEnabled(false);
            table->setCellWidget(i, j, edit);
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j ++){
            if (j != i){
                if (dynamic_cast<QLineEdit*>(table->cellWidget(i, j)) && dynamic_cast<QLineEdit*>(table->cellWidget(i, j))){
                    QLineEdit* edit1 = dynamic_cast<QLineEdit*>(table->cellWidget(i, j));
                    QLineEdit* edit2 = dynamic_cast<QLineEdit*>(table->cellWidget(j, i));
                    connect(edit1, SIGNAL(textChanged(QString)), edit2, SLOT(setText(QString)));
                }
            }
        }
    }
}

QVector<QVector<int>> RoadPriceTableDialog::getPriceMatrix(){
    QVector <QVector<int>> matrix;
    for (int i = 0; i < n; i++){
        QVector<int> tempVector;
        for (int j = 0; j < i; j++){
            if (dynamic_cast<QLineEdit*>(table->cellWidget(i, j))){
                QLineEdit *edit = dynamic_cast<QLineEdit*>(table->cellWidget(i, j));
                QString line = edit->text();
                tempVector.push_back(line.toInt());
            }
        }
        matrix.push_back(tempVector);
    }
    return matrix;
}

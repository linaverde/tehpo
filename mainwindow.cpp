#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "road.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new MyGraphView(ui->spinDate, ui->startBtn);
    connect(ui->startBtn, SIGNAL(clicked()), view, SLOT(setSceneStatusVector()));
    ui->gridLayout->addWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_item_array(){

}


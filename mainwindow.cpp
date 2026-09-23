#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingwidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->resetButton, &QPushButton::clicked,
    ui->drawingWidget, &DrawingWidget::reset);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // this widget gonna be sticked to MainWindow object.
    widget_central = new CentralWidget(this);
    setCentralWidget(widget_central);
}

MainWindow::~MainWindow()
{
}


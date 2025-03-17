#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "centralwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:

    CentralWidget *widget_central;
};
#endif // MAINWINDOW_H

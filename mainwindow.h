#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenu>

#include "centralwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    CentralWidget   *widget_central;
    // File menu.
    QMenu           *menu_file;
    QAction         *action_exit;
    // Help menu.
    QMenu           *menu_help;
    QAction         *action_about;
    void add_menu_bar();
    void show_about();
};
#endif // MAINWINDOW_H

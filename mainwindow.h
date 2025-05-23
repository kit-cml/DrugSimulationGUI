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
    // Edit menu.
    QMenu           *menu_edit;
    QMenu           *menu_change_theme;
    QAction         *action_theme_default;
    QAction         *action_theme_fusion_dark;
    QAction         *action_theme_fusion_light;
    QAction         *action_theme_nord;
    // Help menu.
    QMenu           *menu_help;
    QAction         *action_about;
    void add_menu_bar();
    void show_about();
    void apply_qss_theme(QString theme_name);
};
#endif // MAINWINDOW_H

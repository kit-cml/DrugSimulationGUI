#include "mainwindow.h"

#include <QMenuBar>
#include <QMessageBox>

#include "guiconstants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // this widget gonna be sticked to MainWindow object.
    widget_central = new CentralWidget(this);
    setCentralWidget(widget_central);

    add_menu_bar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::add_menu_bar()
{
    menu_file = this->menuBar()->addMenu(cmlgui::text::menu::MENU_FILE);
    action_exit = new QAction(cmlgui::text::menu::MENU_ACTION_EXIT, this);
    menu_file->addAction(action_exit);
    connect(action_exit, &QAction::triggered, this, &QMainWindow::close);

    menu_help = this->menuBar()->addMenu(cmlgui::text::menu::MENU_HELP);
    action_about = new QAction(cmlgui::text::menu::MENU_ACTION_ABOUT, this);
    menu_help->addAction(action_about);
    connect(action_about, &QAction::triggered, this, &MainWindow::show_about);
}

void MainWindow::show_about()
{
    QMessageBox::about(nullptr, cmlgui::text::window::WINDOW_POPUP_ABOUT_TITLE, cmlgui::text::message::ABOUT_MESSAGE);
}

#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

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

    menu_edit = this->menuBar()->addMenu(cmlgui::text::menu::MENU_EDIT);
    menu_change_theme = menu_edit->addMenu(cmlgui::text::menu::MENU_CHANGE_THEME);
    action_theme_default = new QAction(cmlgui::text::menu::MENU_ACTION_THEME_DEFAULT, this);
    action_theme_fusion_dark = new QAction(cmlgui::text::menu::MENU_ACTION_THEME_FUSION_DARK, this);
    action_theme_fusion_light = new QAction(cmlgui::text::menu::MENU_ACTION_THEME_FUSION_LIGHT, this);
    action_theme_nord = new QAction(cmlgui::text::menu::MENU_ACTION_THEME_NORD, this);
    menu_change_theme->addAction(action_theme_default);
    menu_change_theme->addAction(action_theme_fusion_dark);
    menu_change_theme->addAction(action_theme_fusion_light);
    menu_change_theme->addAction(action_theme_nord);
    connect(action_theme_default, &QAction::triggered, this, [this]() {
        qApp->setStyleSheet("");
    });
    connect(action_theme_fusion_dark, &QAction::triggered, this, [this]() {
        apply_qss_theme(cmlgui::text::menu::MENU_ACTION_THEME_FUSION_DARK);
    });
    connect(action_theme_fusion_light, &QAction::triggered, this, [this]() {
        apply_qss_theme(cmlgui::text::menu::MENU_ACTION_THEME_FUSION_LIGHT);
    });
    connect(action_theme_nord, &QAction::triggered, this, [this]() {
        apply_qss_theme(cmlgui::text::menu::MENU_ACTION_THEME_NORD);
    });

    menu_help = this->menuBar()->addMenu(cmlgui::text::menu::MENU_HELP);
    action_about = new QAction(cmlgui::text::menu::MENU_ACTION_ABOUT, this);
    menu_help->addAction(action_about);
    connect(action_about, &QAction::triggered, this, &MainWindow::show_about);
}

void MainWindow::show_about()
{
    QMessageBox::about(nullptr, cmlgui::text::window::WINDOW_POPUP_ABOUT_TITLE, cmlgui::text::message::ABOUT_MESSAGE);
}

void MainWindow::apply_qss_theme(QString theme_name)
{
    QString theme_file_name = cmlgui::directory::QSS_THEME_DIRECTORY + "/" + theme_name + ".qss";
    QFile theme_file(theme_file_name);
    if (!theme_file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "Could not open QSS file:" << theme_file_name;
        return;
    }

    QTextStream stream(&theme_file);
    QString qss_string = stream.readAll();
    qApp->setStyleSheet(qss_string);
}

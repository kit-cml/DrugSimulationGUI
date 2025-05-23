#include "mainwindow.h"

#include <QDir>
#include <QApplication>

#include "guiconstants.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(cmlgui::size::WINDOW_MAIN_WIDTH, cmlgui::size::WINDOW_MAIN_HEIGHT);
    window.setWindowTitle(cmlgui::text::window::WINDOW_MAIN_TITLE);
    window.show();
    qDebug() << QDir::currentPath();
    return app.exec();
}

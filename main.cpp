#if 1

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // w.hide();
    return a.exec();
}

#else

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    auto icon = QIcon(":/icon.ico");
    auto tray = QSystemTrayIcon();
    tray.setIcon(icon);
    tray.setVisible(true);
    tray.show();
    auto menu = QMenu();
    auto action = QAction("A menu item");
    menu.addAction(&action);
    auto quit = QAction("Quit");
    QObject::connect(&quit, &QAction::triggered, qApp, &QCoreApplication::quit);
    menu.addAction(&quit);
    tray.setContextMenu(&menu);
    return a.exec();
}

#endif
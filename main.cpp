#if 0

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

// Converted from test.py
#include <QObject>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>

int main(int argc, char** argv)
{
    QApplication app { argc, argv };
    app.setQuitOnLastWindowClosed(false);
    QIcon icon(QIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart)));
    auto* tray = new QSystemTrayIcon();
    tray->setIcon(icon);
    tray->setVisible(true);
    auto* menu = new QMenu();
    auto* action = new QAction("A menu item");
    menu->addAction(action);
    auto* quit = new QAction("Quit");
    QObject::connect(quit, &QAction::triggered, qApp, &QCoreApplication::quit);
    menu->addAction(quit);
    tray->setContextMenu(menu);
    return app.exec();
}

#endif
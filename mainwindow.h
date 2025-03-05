#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "entity.h"
#include <QMainWindow>
#include <QString>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void icon_activated(QSystemTrayIcon::ActivationReason reason_);

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow* ui;
    bool is_streaming_;
    std::map<QString, entity::MonitorSettings> resolution_map_;
    entity::Config config_;
    QSystemTrayIcon* tray_icon_;
    QMenu* tray_icon_menu_;

    void load_config();
    void setup_system_tray_();
};
#endif // MAINWINDOW_H

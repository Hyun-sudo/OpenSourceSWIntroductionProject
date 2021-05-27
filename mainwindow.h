#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

#include "SystemInfoPage.h"

#include <vector>
#include "i2c_smbus/i2c_smbus.h"
#include "RGBController/RGBController.h"

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AddI2CToolsPage();

    void setMode(unsigned char mode_val);

private:
    // 페이지 포인터


    bool ShowI2CTools = false;

    // 시스템 트레이 아이콘, 메뉴
    QSystemTrayIcon * trayIcon;
    QMenu * profileMenu;

    // 유저 인터페이스
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

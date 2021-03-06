#ifndef RGBDIALOG01_H
#define RGBDIALOG01_H

#include "ui_rgbdialog01.h"

#include <vector>
#include "i2c_smbus.h"
#include "RGBController.h"

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>

namespace Ui {
class RGBDialog01;
}

class RGBDialog01 : public QMainWindow
{
    Q_OBJECT

public:
    explicit RGBDialog01(std::vector<i2c_smbus_interface *>& bus, std::vector<RGBController *>& control, QWidget *parent = nullptr);
    ~RGBDialog01();

    void show();
    void setMode(unsigned char mode_val);

protected:
    std::vector<i2c_smbus_interface *>& busses;
    std::vector<RGBController *>& controllers;

private:
    Ui::RGBDialog01Ui *ui;

private slots:
    void on_ButtonRed_clicked();
    void on_ButtonYellow_clicked();
    void on_ButtonGreen_clicked();
    void on_ButtonCyan_clicked();
    void on_ButtonBlue_clicked();
    void on_ButtonMagenta_clicked();

    void on_ButtonSetAll_clicked();

    void on_ButtonSetDevice_clicked();

    void on_ButtonSetZone_clicked();

    void on_ButtonSetLED_clicked();

    void on_ComboDevices_currentIndexChanged();

    void on_ComboModes_currentIndexChanged();

};

#endif // RGBDIALOG01_H

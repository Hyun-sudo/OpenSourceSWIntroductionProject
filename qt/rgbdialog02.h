#ifndef RGBDIALOG02_H
#define RGBDIALOG02_H

#include "ui_rgbdialog02.h"

#include <vector>
#include "i2c_smbus.h"
#include "RGBController.h"
#include "ProfileManager.h"

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>

namespace Ui {
class RGBDialog02;
}

class RGBDialog02 : public QMainWindow
{
    Q_OBJECT

public:
    explicit RGBDialog02(std::vector<i2c_smbus_interface *>& bus, std::vector<RGBController *>& control, ProfileManager& manager, QWidget *parent = nullptr);
    ~RGBDialog02();

    void show();
    void setMode(unsigned char mode_val);

protected:
    std::vector<i2c_smbus_interface *>& busses;
    std::vector<RGBController *>&       controllers;
    ProfileManager&                     profile_manager;

private:
    Ui::RGBDialog02Ui *ui;
    QSystemTrayIcon* trayIcon;
    QMenu* profileMenu;
    void RefreshProfileList();

private slots:
    void on_Exit();
    void on_LightsOff();
    void on_QuickRed();
    void on_QuickYellow();
    void on_QuickGreen();
    void on_QuickCyan();
    void on_QuickBlue();
    void on_QuickMagenta();
    void on_QuickWhite();
    void on_SetAllDevices(unsigned char red, unsigned char green, unsigned char blue);
    void on_SaveSizeProfile();
    void on_ShowHide();
    void on_ProfileSelected();
    void on_ButtonSaveProfile_clicked();
    void on_ButtonLoadProfile_clicked();
    void on_ButtonDeleteProfile_clicked();
};

#endif // RGBDIALOG02_H

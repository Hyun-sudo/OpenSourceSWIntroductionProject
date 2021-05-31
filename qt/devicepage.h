#ifndef DEVICEPAGE_H
#define DEVICEPAGE_H

#include "ui_devicepage.h"
#include "RGBController.h"

#include <QFrame>

namespace Ui {
class DevicePage;
}

class DevicePage : public QFrame
{
    Q_OBJECT

public:
    explicit DevicePage(RGBController *dev, QWidget *parent = nullptr);
    ~DevicePage();

    void SetDevice(unsigned char red, unsigned char green, unsigned char blue);
    void SetCustomMode();
    void UpdateDevice();
    void UpdateMode();
    void UpdateModeUi();

private:
    Ui::DevicePageUi *ui;
    RGBController *device;

    bool UpdatingColor = false;
    bool InvertedSpeed = false;

    void updateRGB();

    void updateHSV();

private slots:
    void on_ButtonRed_clicked();
    void on_ButtonYellow_clicked();
    void on_ButtonGreen_clicked();
    void on_ButtonCyan_clicked();
    void on_ButtonBlue_clicked();
    void on_ButtonMagenta_clicked();
    void on_ZoneBox_currentIndexChanged();
    void on_LEDBox_currentIndexChanged(int index);
    void on_ModeBox_currentIndexChanged(int index);
    void on_SetDeviceButton_clicked();
    void on_SetZoneButton_clicked();
    void on_SetLEDButton_clicked();
    void on_RedSpinBox_valueChanged(int arg1);
    void on_HueSpinBox_valueChanged(int arg1);
    void on_GreenSpinBox_valueChanged(int arg1);
    void on_SatSpinBox_valueChanged(int arg1);
    void on_BlueSpinBox_valueChanged(int arg1);
    void on_ValSpinBox_valueChanged(int arg1);

    void on_SetAllButton_clicked();

    void on_RandomCheck_clicked();

    void on_SpeedSlider_valueChanged(int value);

    void on_DirectionBox_currentIndexChanged(int index);

    void on_PerLEDCheck_clicked();

    void on_ModeSpecificCheck_clicked();

    void on_ResizeButton_clicked();

signals:
    void SetAllDevices(unsigned char red, unsigned char green, unsigned char blue);
    void SaveSizeProfile();
};

#endif // DEVICEPAGE_H

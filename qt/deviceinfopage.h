#ifndef DEVICEINFOPAGE_H
#define DEVICEINFOPAGE_H

#include "RGBController.h"
#include "ui_deviceinfopage.h"

#include <QFrame>


namespace Ui {
class DeviceInfoPage;
}

class DeviceInfoPage : public QFrame
{
    Q_OBJECT

public:
    explicit DeviceInfoPage(RGBController *dev, QWidget *parent = nullptr);
    ~DeviceInfoPage();

private:
    Ui::DeviceInfoPageUi *ui;
};

#endif // DEVICEINFOPAGE_H

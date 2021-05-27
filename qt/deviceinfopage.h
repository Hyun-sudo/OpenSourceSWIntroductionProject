#ifndef DEVICEINFOPAGE_H
#define DEVICEINFOPAGE_H

#include <QFrame>
#include "RGBController/RGBController.h"
#include "ui_DeviceInfoPage.h"

namespace Ui {
class DeviceInfoPage;
}

class DeviceInfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceInfoPage(QWidget *parent = nullptr);
    ~DeviceInfoPage();

    RGBController * GetController();

private:
    RGBController * controller;
    Ui::DeviceInfoPage *ui;
};

#endif // DEVICEINFOPAGE_H

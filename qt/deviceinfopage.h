#ifndef DEVICEINFOPAGE_H
#define DEVICEINFOPAGE_H

#include <QWidget>

namespace Ui {
class DeviceInfoPage;
}

class DeviceInfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceInfoPage(QWidget *parent = nullptr);
    ~DeviceInfoPage();

private:
    Ui::DeviceInfoPage *ui;
};

#endif // DEVICEINFOPAGE_H

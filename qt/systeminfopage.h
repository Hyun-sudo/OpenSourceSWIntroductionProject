#ifndef SYSTEMINFOPAGE_H
#define SYSTEMINFOPAGE_H

#include "ui_systeminfopage.h"
#include "i2c_smbus.h"

#include <QFrame>

namespace Ui {
class SystemInfoPage;
}

class SystemInfoPage : public QFrame
{
    Q_OBJECT

public:
    explicit SystemInfoPage(std::vector<i2c_smbus_interface *>& bus, QWidget *parent = nullptr);
    ~SystemInfoPage();

private:
    Ui::SystemInfoPageUi *ui;
    std::vector<i2c_smbus_interface *>& busses;

private slots:
    void on_DetectButton_clicked();

    void on_DumpButton_clicked();
};

#endif // SYSTEMINFOPAGE_H

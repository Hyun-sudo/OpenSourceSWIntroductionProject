#ifndef SUPPORTEDDEVICEPAGE_H
#define SUPPORTEDDEVICEPAGE_H

#include "DetectorTableModel.h"

#include <QWidget>

namespace Ui {
class SupportedDevicePage;
}

class SupportedDevicePage : public QWidget
{
    Q_OBJECT

public:
    explicit SupportedDevicePage(QWidget *parent = nullptr);
    ~SupportedDevicePage();

private:
    Ui::SupportedDevicePage *ui;
};

#endif // SUPPORTEDDEVICEPAGE_H

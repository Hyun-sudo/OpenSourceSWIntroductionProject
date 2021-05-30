#ifndef RGBDIALOG01_H
#define RGBDIALOG01_H

#include <QMainWindow>

namespace Ui {
class RGBDialog01;
}

class RGBDialog01 : public QMainWindow
{
    Q_OBJECT

public:
    explicit RGBDialog01(QWidget *parent = nullptr);
    ~RGBDialog01();

private:
    Ui::RGBDialog01 *ui;
};

#endif // RGBDIALOG01_H

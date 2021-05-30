#ifndef RGBDIALOG02_H
#define RGBDIALOG02_H

#include <QMainWindow>

namespace Ui {
class RGBDialog02;
}

class RGBDialog02 : public QMainWindow
{
    Q_OBJECT

public:
    explicit RGBDialog02(QWidget *parent = nullptr);
    ~RGBDialog02();

private:
    Ui::RGBDialog02 *ui;
};

#endif // RGBDIALOG02_H

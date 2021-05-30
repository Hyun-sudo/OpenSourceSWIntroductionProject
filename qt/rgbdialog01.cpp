#include "rgbdialog01.h"
#include "ui_rgbdialog01.h"

RGBDialog01::RGBDialog01(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RGBDialog01)
{
    ui->setupUi(this);
}

RGBDialog01::~RGBDialog01()
{
    delete ui;
}

#include "rgbdialog02.h"
#include "ui_rgbdialog02.h"

RGBDialog02::RGBDialog02(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RGBDialog02)
{
    ui->setupUi(this);
}

RGBDialog02::~RGBDialog02()
{
    delete ui;
}

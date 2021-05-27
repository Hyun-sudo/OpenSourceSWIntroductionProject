#include "rgbdialog.h"
#include "ui_rgbdialog.h"

RGBDialog::RGBDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RGBDialog)
{
    ui->setupUi(this);
}

RGBDialog::~RGBDialog()
{
    delete ui;
}

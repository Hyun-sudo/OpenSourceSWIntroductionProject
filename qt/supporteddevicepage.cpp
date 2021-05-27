#include "supporteddevicepage.h"
#include "ui_supporteddevicepage.h"

SupportedDevicePage::SupportedDevicePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupportedDevicePage)
{
    ui->setupUi(this);
}

SupportedDevicePage::~SupportedDevicePage()
{
    delete ui;
}

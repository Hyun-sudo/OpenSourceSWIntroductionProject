#include "deviceinfopage.h"
#include "ui_deviceinfopage.h"

DeviceInfoPage::DeviceInfoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceInfoPage)
{
    ui->setupUi(this);
}

DeviceInfoPage::~DeviceInfoPage()
{
    delete ui;
}

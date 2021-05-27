#include "deviceinfopage.h"
#include "ui_DeviceInfoPage.h"

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

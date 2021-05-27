#include "systeminfopage.h"
#include "ui_systeminfopage.h"

SystemInfoPage::SystemInfoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemInfoPage)
{
    ui->setupUi(this);
}

SystemInfoPage::~SystemInfoPage()
{
    delete ui;
}

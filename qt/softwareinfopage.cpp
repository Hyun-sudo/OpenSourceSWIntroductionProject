#include "softwareinfopage.h"
#include "ui_softwareinfopage.h"

SoftwareInfoPage::SoftwareInfoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoftwareInfoPage)
{
    ui->setupUi(this);
}

SoftwareInfoPage::~SoftwareInfoPage()
{
    delete ui;
}

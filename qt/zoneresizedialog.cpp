#include "zoneresizedialog.h"
#include "ui_zoneresizedialog.h"

ZoneResizeDialog::ZoneResizeDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoneResizeDialog)
{
    ui->setupUi(this);
}

ZoneResizeDialog::~ZoneResizeDialog()
{
    delete ui;
}

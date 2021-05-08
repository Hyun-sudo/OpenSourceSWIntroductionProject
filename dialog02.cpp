#include "dialog02.h"
#include "ui_dialog02.h"

Dialog02::Dialog02(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dialog02)
{
    ui->setupUi(this);
}

Dialog02::~Dialog02()
{
    delete ui;
}

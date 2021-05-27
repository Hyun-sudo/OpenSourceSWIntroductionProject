#include "profilesavedialog.h"
#include "ui_profilesavedialog.h"

ProfileSaveDialog::ProfileSaveDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileSaveDialog)
{
    ui->setupUi(this);
}

ProfileSaveDialog::~ProfileSaveDialog()
{
    delete ui;
}

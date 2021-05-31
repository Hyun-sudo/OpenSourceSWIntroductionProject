#include "profilesavedialog.h"

ProfileSaveDialog::ProfileSaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileSaveDialogUi)
{
    ui->setupUi(this);
}

ProfileSaveDialog::~ProfileSaveDialog()
{
    delete ui;
}

std::string ProfileSaveDialog::show()
{
    std::string return_string;

    int result = this->exec();

    if(result == QDialog::Rejected)
    {
        return_string = "";
    }
    else
    {
        return_string = ui->lineEdit->text().toStdString();
    }

    return(return_string);
}

#include "softwareinfopage.h"

SoftwareInfoPage::SoftwareInfoPage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SoftwareInfoPageUi)
{
    ui->setupUi(this);

    ui->VersionValue->setText(VERSION_STRING);
    ui->BuildDateValue->setText(BUILDDATE_STRING);
    ui->GitCommitIDValue->setText(GIT_COMMIT_ID);
    ui->GitCommitDateValue->setText(GIT_COMMIT_DATE);
    ui->GitBranchValue->setText(GIT_BRANCH);
}

SoftwareInfoPage::~SoftwareInfoPage()
{
    delete ui;
}

/********************************************************************************
** Form generated from reading UI file 'softwareinfopage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOFTWAREINFOPAGE_H
#define UI_SOFTWAREINFOPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SoftwareInfoPageUi
{
public:
    QGridLayout *gridLayout;
    QLabel *VersionLabel;
    QLabel *VersionValue;
    QLabel *BuildDateLabel;
    QLabel *BuildDateValue;
    QLabel *GitCommitIDLabel;
    QLabel *GitCommitIDValue;
    QLabel *GitCommitDateLabel;
    QLabel *GitCommitDateValue;
    QLabel *GitBranchLabel;
    QLabel *GitBranchValue;

    void setupUi(QWidget *SoftwareInfoPageUi)
    {
        if (SoftwareInfoPageUi->objectName().isEmpty())
            SoftwareInfoPageUi->setObjectName(QString::fromUtf8("SoftwareInfoPageUi"));
        SoftwareInfoPageUi->resize(500, 300);
        gridLayout = new QGridLayout(SoftwareInfoPageUi);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        VersionLabel = new QLabel(SoftwareInfoPageUi);
        VersionLabel->setObjectName(QString::fromUtf8("VersionLabel"));

        gridLayout->addWidget(VersionLabel, 0, 0, 1, 1);

        VersionValue = new QLabel(SoftwareInfoPageUi);
        VersionValue->setObjectName(QString::fromUtf8("VersionValue"));

        gridLayout->addWidget(VersionValue, 0, 1, 1, 1);

        BuildDateLabel = new QLabel(SoftwareInfoPageUi);
        BuildDateLabel->setObjectName(QString::fromUtf8("BuildDateLabel"));

        gridLayout->addWidget(BuildDateLabel, 1, 0, 1, 1);

        BuildDateValue = new QLabel(SoftwareInfoPageUi);
        BuildDateValue->setObjectName(QString::fromUtf8("BuildDateValue"));

        gridLayout->addWidget(BuildDateValue, 1, 1, 1, 1);

        GitCommitIDLabel = new QLabel(SoftwareInfoPageUi);
        GitCommitIDLabel->setObjectName(QString::fromUtf8("GitCommitIDLabel"));

        gridLayout->addWidget(GitCommitIDLabel, 2, 0, 1, 1);

        GitCommitIDValue = new QLabel(SoftwareInfoPageUi);
        GitCommitIDValue->setObjectName(QString::fromUtf8("GitCommitIDValue"));

        gridLayout->addWidget(GitCommitIDValue, 2, 1, 1, 1);

        GitCommitDateLabel = new QLabel(SoftwareInfoPageUi);
        GitCommitDateLabel->setObjectName(QString::fromUtf8("GitCommitDateLabel"));

        gridLayout->addWidget(GitCommitDateLabel, 3, 0, 1, 1);

        GitCommitDateValue = new QLabel(SoftwareInfoPageUi);
        GitCommitDateValue->setObjectName(QString::fromUtf8("GitCommitDateValue"));

        gridLayout->addWidget(GitCommitDateValue, 3, 1, 1, 1);

        GitBranchLabel = new QLabel(SoftwareInfoPageUi);
        GitBranchLabel->setObjectName(QString::fromUtf8("GitBranchLabel"));

        gridLayout->addWidget(GitBranchLabel, 4, 0, 1, 1);

        GitBranchValue = new QLabel(SoftwareInfoPageUi);
        GitBranchValue->setObjectName(QString::fromUtf8("GitBranchValue"));

        gridLayout->addWidget(GitBranchValue, 4, 1, 1, 1);


        retranslateUi(SoftwareInfoPageUi);

        QMetaObject::connectSlotsByName(SoftwareInfoPageUi);
    } // setupUi

    void retranslateUi(QWidget *SoftwareInfoPageUi)
    {
        SoftwareInfoPageUi->setWindowTitle(QCoreApplication::translate("SoftwareInfoPageUi", "Form", nullptr));
        VersionLabel->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Version:", nullptr));
        VersionValue->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Version Value", nullptr));
        BuildDateLabel->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Build Date:", nullptr));
        BuildDateValue->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Build Date Value", nullptr));
        GitCommitIDLabel->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Git Commit ID:", nullptr));
        GitCommitIDValue->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Git Commit ID Value", nullptr));
        GitCommitDateLabel->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Git Commit Date:", nullptr));
        GitCommitDateValue->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Git Commit Date Value", nullptr));
        GitBranchLabel->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Git Branch:", nullptr));
        GitBranchValue->setText(QCoreApplication::translate("SoftwareInfoPageUi", "Git Branch Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SoftwareInfoPageUi: public Ui_SoftwareInfoPageUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOFTWAREINFOPAGE_H

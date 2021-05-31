/********************************************************************************
** Form generated from reading UI file 'profilesavedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILESAVEDIALOG_H
#define UI_PROFILESAVEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfileSaveDialogUi
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *ProfileSaveDialogUi)
    {
        if (ProfileSaveDialogUi->objectName().isEmpty())
            ProfileSaveDialogUi->setObjectName(QString::fromUtf8("ProfileSaveDialogUi"));
        ProfileSaveDialogUi->resize(400, 160);
        lineEdit = new QLineEdit(ProfileSaveDialogUi);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 70, 341, 20));
        label = new QLabel(ProfileSaveDialogUi);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 341, 16));
        buttonBox = new QDialogButtonBox(ProfileSaveDialogUi);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 120, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(ProfileSaveDialogUi);

        QMetaObject::connectSlotsByName(ProfileSaveDialogUi);
    } // setupUi

    void retranslateUi(QWidget *ProfileSaveDialogUi)
    {
        ProfileSaveDialogUi->setWindowTitle(QCoreApplication::translate("ProfileSaveDialogUi", "Form", nullptr));
        label->setText(QCoreApplication::translate("ProfileSaveDialogUi", "New Profile Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProfileSaveDialogUi: public Ui_ProfileSaveDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILESAVEDIALOG_H

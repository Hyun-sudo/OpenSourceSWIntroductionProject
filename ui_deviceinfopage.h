/********************************************************************************
** Form generated from reading UI file 'deviceinfopage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEINFOPAGE_H
#define UI_DEVICEINFOPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceInfoPageUi
{
public:
    QGridLayout *gridLayout;
    QLabel *NameLabel;
    QLabel *NameValue;
    QLabel *TypeLabel;
    QLabel *TypeValue;
    QLabel *DescriptionLabel;
    QLabel *DescriptionValue;
    QLabel *VersionLabel;
    QLabel *VersionValue;
    QLabel *LocationLabel;
    QLabel *LocationValue;
    QLabel *SerialLabel;
    QLabel *SerialValue;

    void setupUi(QWidget *DeviceInfoPageUi)
    {
        if (DeviceInfoPageUi->objectName().isEmpty())
            DeviceInfoPageUi->setObjectName(QString::fromUtf8("DeviceInfoPageUi"));
        DeviceInfoPageUi->resize(500, 300);
        gridLayout = new QGridLayout(DeviceInfoPageUi);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        NameLabel = new QLabel(DeviceInfoPageUi);
        NameLabel->setObjectName(QString::fromUtf8("NameLabel"));

        gridLayout->addWidget(NameLabel, 0, 0, 1, 1);

        NameValue = new QLabel(DeviceInfoPageUi);
        NameValue->setObjectName(QString::fromUtf8("NameValue"));

        gridLayout->addWidget(NameValue, 0, 1, 1, 1);

        TypeLabel = new QLabel(DeviceInfoPageUi);
        TypeLabel->setObjectName(QString::fromUtf8("TypeLabel"));

        gridLayout->addWidget(TypeLabel, 1, 0, 1, 1);

        TypeValue = new QLabel(DeviceInfoPageUi);
        TypeValue->setObjectName(QString::fromUtf8("TypeValue"));

        gridLayout->addWidget(TypeValue, 1, 1, 1, 1);

        DescriptionLabel = new QLabel(DeviceInfoPageUi);
        DescriptionLabel->setObjectName(QString::fromUtf8("DescriptionLabel"));

        gridLayout->addWidget(DescriptionLabel, 2, 0, 1, 1);

        DescriptionValue = new QLabel(DeviceInfoPageUi);
        DescriptionValue->setObjectName(QString::fromUtf8("DescriptionValue"));

        gridLayout->addWidget(DescriptionValue, 2, 1, 1, 1);

        VersionLabel = new QLabel(DeviceInfoPageUi);
        VersionLabel->setObjectName(QString::fromUtf8("VersionLabel"));

        gridLayout->addWidget(VersionLabel, 3, 0, 1, 1);

        VersionValue = new QLabel(DeviceInfoPageUi);
        VersionValue->setObjectName(QString::fromUtf8("VersionValue"));

        gridLayout->addWidget(VersionValue, 3, 1, 1, 1);

        LocationLabel = new QLabel(DeviceInfoPageUi);
        LocationLabel->setObjectName(QString::fromUtf8("LocationLabel"));

        gridLayout->addWidget(LocationLabel, 4, 0, 1, 1);

        LocationValue = new QLabel(DeviceInfoPageUi);
        LocationValue->setObjectName(QString::fromUtf8("LocationValue"));

        gridLayout->addWidget(LocationValue, 4, 1, 1, 1);

        SerialLabel = new QLabel(DeviceInfoPageUi);
        SerialLabel->setObjectName(QString::fromUtf8("SerialLabel"));

        gridLayout->addWidget(SerialLabel, 5, 0, 1, 1);

        SerialValue = new QLabel(DeviceInfoPageUi);
        SerialValue->setObjectName(QString::fromUtf8("SerialValue"));

        gridLayout->addWidget(SerialValue, 5, 1, 1, 1);


        retranslateUi(DeviceInfoPageUi);

        QMetaObject::connectSlotsByName(DeviceInfoPageUi);
    } // setupUi

    void retranslateUi(QWidget *DeviceInfoPageUi)
    {
        DeviceInfoPageUi->setWindowTitle(QCoreApplication::translate("DeviceInfoPageUi", "Form", nullptr));
        NameLabel->setText(QCoreApplication::translate("DeviceInfoPageUi", "Name:", nullptr));
        NameValue->setText(QCoreApplication::translate("DeviceInfoPageUi", "Name Value", nullptr));
        TypeLabel->setText(QCoreApplication::translate("DeviceInfoPageUi", "Type:", nullptr));
        TypeValue->setText(QCoreApplication::translate("DeviceInfoPageUi", "Type Value", nullptr));
        DescriptionLabel->setText(QCoreApplication::translate("DeviceInfoPageUi", "Description:", nullptr));
        DescriptionValue->setText(QCoreApplication::translate("DeviceInfoPageUi", "Description Value", nullptr));
        VersionLabel->setText(QCoreApplication::translate("DeviceInfoPageUi", "Version:", nullptr));
        VersionValue->setText(QCoreApplication::translate("DeviceInfoPageUi", "Version Value", nullptr));
        LocationLabel->setText(QCoreApplication::translate("DeviceInfoPageUi", "Location:", nullptr));
        LocationValue->setText(QCoreApplication::translate("DeviceInfoPageUi", "Location Value", nullptr));
        SerialLabel->setText(QCoreApplication::translate("DeviceInfoPageUi", "Serial:", nullptr));
        SerialValue->setText(QCoreApplication::translate("DeviceInfoPageUi", "Serial Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeviceInfoPageUi: public Ui_DeviceInfoPageUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEINFOPAGE_H

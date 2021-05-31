/********************************************************************************
** Form generated from reading UI file 'systeminfopage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMINFOPAGE_H
#define UI_SYSTEMINFOPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemInfoPageUi
{
public:
    QGridLayout *gridLayout;
    QLabel *SMBusAdaptersLabel;
    QComboBox *SMBusAdaptersBox;
    QPushButton *DetectButton;
    QLabel *SMBusDumpLabel;
    QLabel *DumpAddressLabel;
    QSpinBox *DumpAddressBox;
    QPushButton *DumpButton;
    QPlainTextEdit *SMBusDataText;

    void setupUi(QWidget *SystemInfoPageUi)
    {
        if (SystemInfoPageUi->objectName().isEmpty())
            SystemInfoPageUi->setObjectName(QString::fromUtf8("SystemInfoPageUi"));
        SystemInfoPageUi->resize(500, 320);
        gridLayout = new QGridLayout(SystemInfoPageUi);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        SMBusAdaptersLabel = new QLabel(SystemInfoPageUi);
        SMBusAdaptersLabel->setObjectName(QString::fromUtf8("SMBusAdaptersLabel"));

        gridLayout->addWidget(SMBusAdaptersLabel, 0, 0, 1, 1);

        SMBusAdaptersBox = new QComboBox(SystemInfoPageUi);
        SMBusAdaptersBox->setObjectName(QString::fromUtf8("SMBusAdaptersBox"));

        gridLayout->addWidget(SMBusAdaptersBox, 0, 1, 1, 2);

        DetectButton = new QPushButton(SystemInfoPageUi);
        DetectButton->setObjectName(QString::fromUtf8("DetectButton"));

        gridLayout->addWidget(DetectButton, 0, 3, 1, 1);

        SMBusDumpLabel = new QLabel(SystemInfoPageUi);
        SMBusDumpLabel->setObjectName(QString::fromUtf8("SMBusDumpLabel"));

        gridLayout->addWidget(SMBusDumpLabel, 1, 0, 1, 1);

        DumpAddressLabel = new QLabel(SystemInfoPageUi);
        DumpAddressLabel->setObjectName(QString::fromUtf8("DumpAddressLabel"));

        gridLayout->addWidget(DumpAddressLabel, 1, 1, 1, 1);

        DumpAddressBox = new QSpinBox(SystemInfoPageUi);
        DumpAddressBox->setObjectName(QString::fromUtf8("DumpAddressBox"));
        DumpAddressBox->setMaximum(255);
        DumpAddressBox->setDisplayIntegerBase(16);

        gridLayout->addWidget(DumpAddressBox, 1, 2, 1, 1);

        DumpButton = new QPushButton(SystemInfoPageUi);
        DumpButton->setObjectName(QString::fromUtf8("DumpButton"));

        gridLayout->addWidget(DumpButton, 1, 3, 1, 1);

        SMBusDataText = new QPlainTextEdit(SystemInfoPageUi);
        SMBusDataText->setObjectName(QString::fromUtf8("SMBusDataText"));

        gridLayout->addWidget(SMBusDataText, 2, 0, 1, 4);


        retranslateUi(SystemInfoPageUi);

        QMetaObject::connectSlotsByName(SystemInfoPageUi);
    } // setupUi

    void retranslateUi(QWidget *SystemInfoPageUi)
    {
        SystemInfoPageUi->setWindowTitle(QCoreApplication::translate("SystemInfoPageUi", "Form", nullptr));
        SMBusAdaptersLabel->setText(QCoreApplication::translate("SystemInfoPageUi", "SMBus Adapters:", nullptr));
        DetectButton->setText(QCoreApplication::translate("SystemInfoPageUi", "Detect Devices", nullptr));
        SMBusDumpLabel->setText(QCoreApplication::translate("SystemInfoPageUi", "SMBus Dumper:", nullptr));
        DumpAddressLabel->setText(QCoreApplication::translate("SystemInfoPageUi", "Address:", nullptr));
        DumpAddressBox->setSuffix(QString());
        DumpAddressBox->setPrefix(QCoreApplication::translate("SystemInfoPageUi", "0x", nullptr));
        DumpButton->setText(QCoreApplication::translate("SystemInfoPageUi", "Dump Device", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemInfoPageUi: public Ui_SystemInfoPageUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMINFOPAGE_H

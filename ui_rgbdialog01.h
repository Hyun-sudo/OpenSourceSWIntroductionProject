/********************************************************************************
** Form generated from reading UI file 'rgbdialog01.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RGBDIALOG01_H
#define UI_RGBDIALOG01_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RGBDialog01Ui
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *ButtonRed;
    QPushButton *ButtonYellow;
    QPushButton *ButtonGreen;
    QPushButton *ButtonCyan;
    QPushButton *ButtonBlue;
    QPushButton *ButtonMagenta;
    QLabel *LabelAuraDevice;
    QComboBox *ComboDevices;
    QLabel *LabelRed;
    QLabel *LabelGreen;
    QLabel *LabelBlue;
    QLabel *LabelMode;
    QComboBox *ComboModes;
    QLineEdit *EditLED0R;
    QLineEdit *EditLED0G;
    QLineEdit *EditLED0B;
    QPushButton *ButtonSetAll;
    QPushButton *ButtonSetDevice;
    QLabel *LabelZone;
    QComboBox *ComboZones;
    QPushButton *ButtonSetZone;
    QPushButton *ButtonSetLED;
    QLabel *LabelLED;
    QComboBox *ComboLEDs;

    void setupUi(QMainWindow *RGBDialog01Ui)
    {
        if (RGBDialog01Ui->objectName().isEmpty())
            RGBDialog01Ui->setObjectName(QString::fromUtf8("RGBDialog01Ui"));
        RGBDialog01Ui->resize(500, 160);
        centralwidget = new QWidget(RGBDialog01Ui);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ButtonRed = new QPushButton(centralwidget);
        ButtonRed->setObjectName(QString::fromUtf8("ButtonRed"));

        gridLayout->addWidget(ButtonRed, 0, 0, 1, 1);

        ButtonYellow = new QPushButton(centralwidget);
        ButtonYellow->setObjectName(QString::fromUtf8("ButtonYellow"));

        gridLayout->addWidget(ButtonYellow, 0, 1, 1, 1);

        ButtonGreen = new QPushButton(centralwidget);
        ButtonGreen->setObjectName(QString::fromUtf8("ButtonGreen"));

        gridLayout->addWidget(ButtonGreen, 0, 2, 1, 1);

        ButtonCyan = new QPushButton(centralwidget);
        ButtonCyan->setObjectName(QString::fromUtf8("ButtonCyan"));

        gridLayout->addWidget(ButtonCyan, 0, 3, 1, 1);

        ButtonBlue = new QPushButton(centralwidget);
        ButtonBlue->setObjectName(QString::fromUtf8("ButtonBlue"));

        gridLayout->addWidget(ButtonBlue, 0, 4, 1, 1);

        ButtonMagenta = new QPushButton(centralwidget);
        ButtonMagenta->setObjectName(QString::fromUtf8("ButtonMagenta"));

        gridLayout->addWidget(ButtonMagenta, 0, 5, 1, 1);

        LabelAuraDevice = new QLabel(centralwidget);
        LabelAuraDevice->setObjectName(QString::fromUtf8("LabelAuraDevice"));

        gridLayout->addWidget(LabelAuraDevice, 0, 6, 1, 1);

        ComboDevices = new QComboBox(centralwidget);
        ComboDevices->setObjectName(QString::fromUtf8("ComboDevices"));

        gridLayout->addWidget(ComboDevices, 0, 7, 1, 1);

        LabelRed = new QLabel(centralwidget);
        LabelRed->setObjectName(QString::fromUtf8("LabelRed"));

        gridLayout->addWidget(LabelRed, 1, 0, 1, 2);

        LabelGreen = new QLabel(centralwidget);
        LabelGreen->setObjectName(QString::fromUtf8("LabelGreen"));

        gridLayout->addWidget(LabelGreen, 1, 2, 1, 2);

        LabelBlue = new QLabel(centralwidget);
        LabelBlue->setObjectName(QString::fromUtf8("LabelBlue"));

        gridLayout->addWidget(LabelBlue, 1, 4, 1, 2);

        LabelMode = new QLabel(centralwidget);
        LabelMode->setObjectName(QString::fromUtf8("LabelMode"));

        gridLayout->addWidget(LabelMode, 1, 6, 2, 1);

        ComboModes = new QComboBox(centralwidget);
        ComboModes->setObjectName(QString::fromUtf8("ComboModes"));

        gridLayout->addWidget(ComboModes, 1, 7, 2, 1);

        EditLED0R = new QLineEdit(centralwidget);
        EditLED0R->setObjectName(QString::fromUtf8("EditLED0R"));

        gridLayout->addWidget(EditLED0R, 2, 0, 1, 2);

        EditLED0G = new QLineEdit(centralwidget);
        EditLED0G->setObjectName(QString::fromUtf8("EditLED0G"));

        gridLayout->addWidget(EditLED0G, 2, 2, 1, 2);

        EditLED0B = new QLineEdit(centralwidget);
        EditLED0B->setObjectName(QString::fromUtf8("EditLED0B"));

        gridLayout->addWidget(EditLED0B, 2, 4, 1, 2);

        ButtonSetAll = new QPushButton(centralwidget);
        ButtonSetAll->setObjectName(QString::fromUtf8("ButtonSetAll"));

        gridLayout->addWidget(ButtonSetAll, 3, 0, 1, 3);

        ButtonSetDevice = new QPushButton(centralwidget);
        ButtonSetDevice->setObjectName(QString::fromUtf8("ButtonSetDevice"));

        gridLayout->addWidget(ButtonSetDevice, 3, 3, 1, 3);

        LabelZone = new QLabel(centralwidget);
        LabelZone->setObjectName(QString::fromUtf8("LabelZone"));

        gridLayout->addWidget(LabelZone, 3, 6, 1, 1);

        ComboZones = new QComboBox(centralwidget);
        ComboZones->setObjectName(QString::fromUtf8("ComboZones"));

        gridLayout->addWidget(ComboZones, 3, 7, 1, 1);

        ButtonSetZone = new QPushButton(centralwidget);
        ButtonSetZone->setObjectName(QString::fromUtf8("ButtonSetZone"));

        gridLayout->addWidget(ButtonSetZone, 4, 0, 1, 3);

        ButtonSetLED = new QPushButton(centralwidget);
        ButtonSetLED->setObjectName(QString::fromUtf8("ButtonSetLED"));

        gridLayout->addWidget(ButtonSetLED, 4, 3, 1, 3);

        LabelLED = new QLabel(centralwidget);
        LabelLED->setObjectName(QString::fromUtf8("LabelLED"));

        gridLayout->addWidget(LabelLED, 4, 6, 1, 1);

        ComboLEDs = new QComboBox(centralwidget);
        ComboLEDs->setObjectName(QString::fromUtf8("ComboLEDs"));

        gridLayout->addWidget(ComboLEDs, 4, 7, 1, 1);

        RGBDialog01Ui->setCentralWidget(centralwidget);

        retranslateUi(RGBDialog01Ui);

        QMetaObject::connectSlotsByName(RGBDialog01Ui);
    } // setupUi

    void retranslateUi(QMainWindow *RGBDialog01Ui)
    {
        RGBDialog01Ui->setWindowTitle(QCoreApplication::translate("RGBDialog01Ui", "MainWindow", nullptr));
        ButtonRed->setText(QString());
        ButtonYellow->setText(QString());
        ButtonGreen->setText(QString());
        ButtonCyan->setText(QString());
        ButtonBlue->setText(QString());
        ButtonMagenta->setText(QString());
        LabelAuraDevice->setText(QCoreApplication::translate("RGBDialog01Ui", "Device", nullptr));
        LabelRed->setText(QCoreApplication::translate("RGBDialog01Ui", "Red", nullptr));
        LabelGreen->setText(QCoreApplication::translate("RGBDialog01Ui", "Green", nullptr));
        LabelBlue->setText(QCoreApplication::translate("RGBDialog01Ui", "Blue", nullptr));
        LabelMode->setText(QCoreApplication::translate("RGBDialog01Ui", "Mode", nullptr));
        ButtonSetAll->setText(QCoreApplication::translate("RGBDialog01Ui", "Set All", nullptr));
        ButtonSetDevice->setText(QCoreApplication::translate("RGBDialog01Ui", "Set Device", nullptr));
        LabelZone->setText(QCoreApplication::translate("RGBDialog01Ui", "Zone", nullptr));
        ButtonSetZone->setText(QCoreApplication::translate("RGBDialog01Ui", "Set Zone", nullptr));
        ButtonSetLED->setText(QCoreApplication::translate("RGBDialog01Ui", "Set LED", nullptr));
        LabelLED->setText(QCoreApplication::translate("RGBDialog01Ui", "LED", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RGBDialog01Ui: public Ui_RGBDialog01Ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RGBDIALOG01_H

/********************************************************************************
** Form generated from reading UI file 'devicepage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEPAGE_H
#define UI_DEVICEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DevicePageUi
{
public:
    QGridLayout *gridLayout;
    QLabel *ZoneLabel;
    QComboBox *ZoneBox;
    QPushButton *ResizeButton;
    QLabel *LEDLabel;
    QComboBox *LEDBox;
    QLabel *SetLabel;
    QPushButton *SetDeviceButton;
    QPushButton *SetZoneButton;
    QPushButton *SetLEDButton;
    QLabel *RedLabel;
    QSpinBox *RedSpinBox;
    QLabel *HueLabel;
    QSpinBox *HueSpinBox;
    QPushButton *SetAllButton;
    QLabel *GreenLabel;
    QSpinBox *GreenSpinBox;
    QLabel *SatLabel;
    QSpinBox *SatSpinBox;
    QLabel *BlueLabel;
    QSpinBox *BlueSpinBox;
    QLabel *ValLabel;
    QSpinBox *ValSpinBox;
    QLabel *ModeLabel;
    QComboBox *ModeBox;
    QLabel *ColorLabel;
    QRadioButton *PerLEDCheck;
    QRadioButton *ModeSpecificCheck;
    QRadioButton *RandomCheck;
    QPushButton *ButtonRed;
    QPushButton *ButtonYellow;
    QPushButton *ButtonGreen;
    QPushButton *ButtonCyan;
    QPushButton *ButtonBlue;
    QPushButton *ButtonMagenta;
    QLabel *SpeedLabel;
    QSlider *SpeedSlider;
    QLabel *DirectionLabel;
    QComboBox *DirectionBox;

    void setupUi(QWidget *DevicePageUi)
    {
        if (DevicePageUi->objectName().isEmpty())
            DevicePageUi->setObjectName(QString::fromUtf8("DevicePageUi"));
        DevicePageUi->resize(556, 300);
        gridLayout = new QGridLayout(DevicePageUi);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ZoneLabel = new QLabel(DevicePageUi);
        ZoneLabel->setObjectName(QString::fromUtf8("ZoneLabel"));

        gridLayout->addWidget(ZoneLabel, 0, 0, 1, 1);

        ZoneBox = new QComboBox(DevicePageUi);
        ZoneBox->setObjectName(QString::fromUtf8("ZoneBox"));

        gridLayout->addWidget(ZoneBox, 0, 1, 1, 2);

        ResizeButton = new QPushButton(DevicePageUi);
        ResizeButton->setObjectName(QString::fromUtf8("ResizeButton"));

        gridLayout->addWidget(ResizeButton, 0, 3, 1, 1);

        LEDLabel = new QLabel(DevicePageUi);
        LEDLabel->setObjectName(QString::fromUtf8("LEDLabel"));

        gridLayout->addWidget(LEDLabel, 1, 0, 1, 1);

        LEDBox = new QComboBox(DevicePageUi);
        LEDBox->setObjectName(QString::fromUtf8("LEDBox"));

        gridLayout->addWidget(LEDBox, 1, 1, 1, 3);

        SetLabel = new QLabel(DevicePageUi);
        SetLabel->setObjectName(QString::fromUtf8("SetLabel"));

        gridLayout->addWidget(SetLabel, 2, 0, 1, 1);

        SetDeviceButton = new QPushButton(DevicePageUi);
        SetDeviceButton->setObjectName(QString::fromUtf8("SetDeviceButton"));

        gridLayout->addWidget(SetDeviceButton, 2, 1, 1, 1);

        SetZoneButton = new QPushButton(DevicePageUi);
        SetZoneButton->setObjectName(QString::fromUtf8("SetZoneButton"));

        gridLayout->addWidget(SetZoneButton, 2, 2, 1, 1);

        SetLEDButton = new QPushButton(DevicePageUi);
        SetLEDButton->setObjectName(QString::fromUtf8("SetLEDButton"));

        gridLayout->addWidget(SetLEDButton, 2, 3, 1, 1);

        RedLabel = new QLabel(DevicePageUi);
        RedLabel->setObjectName(QString::fromUtf8("RedLabel"));

        gridLayout->addWidget(RedLabel, 2, 4, 1, 1);

        RedSpinBox = new QSpinBox(DevicePageUi);
        RedSpinBox->setObjectName(QString::fromUtf8("RedSpinBox"));
        RedSpinBox->setMaximum(255);

        gridLayout->addWidget(RedSpinBox, 2, 5, 1, 2);

        HueLabel = new QLabel(DevicePageUi);
        HueLabel->setObjectName(QString::fromUtf8("HueLabel"));

        gridLayout->addWidget(HueLabel, 2, 7, 1, 1);

        HueSpinBox = new QSpinBox(DevicePageUi);
        HueSpinBox->setObjectName(QString::fromUtf8("HueSpinBox"));
        HueSpinBox->setMaximum(359);

        gridLayout->addWidget(HueSpinBox, 2, 8, 1, 2);

        SetAllButton = new QPushButton(DevicePageUi);
        SetAllButton->setObjectName(QString::fromUtf8("SetAllButton"));

        gridLayout->addWidget(SetAllButton, 3, 1, 1, 3);

        GreenLabel = new QLabel(DevicePageUi);
        GreenLabel->setObjectName(QString::fromUtf8("GreenLabel"));

        gridLayout->addWidget(GreenLabel, 3, 4, 1, 1);

        GreenSpinBox = new QSpinBox(DevicePageUi);
        GreenSpinBox->setObjectName(QString::fromUtf8("GreenSpinBox"));
        GreenSpinBox->setMaximum(255);

        gridLayout->addWidget(GreenSpinBox, 3, 5, 1, 2);

        SatLabel = new QLabel(DevicePageUi);
        SatLabel->setObjectName(QString::fromUtf8("SatLabel"));

        gridLayout->addWidget(SatLabel, 3, 7, 1, 1);

        SatSpinBox = new QSpinBox(DevicePageUi);
        SatSpinBox->setObjectName(QString::fromUtf8("SatSpinBox"));
        SatSpinBox->setMaximum(255);

        gridLayout->addWidget(SatSpinBox, 3, 8, 1, 2);

        BlueLabel = new QLabel(DevicePageUi);
        BlueLabel->setObjectName(QString::fromUtf8("BlueLabel"));

        gridLayout->addWidget(BlueLabel, 4, 4, 1, 1);

        BlueSpinBox = new QSpinBox(DevicePageUi);
        BlueSpinBox->setObjectName(QString::fromUtf8("BlueSpinBox"));
        BlueSpinBox->setMaximum(255);

        gridLayout->addWidget(BlueSpinBox, 4, 5, 1, 2);

        ValLabel = new QLabel(DevicePageUi);
        ValLabel->setObjectName(QString::fromUtf8("ValLabel"));

        gridLayout->addWidget(ValLabel, 4, 7, 1, 1);

        ValSpinBox = new QSpinBox(DevicePageUi);
        ValSpinBox->setObjectName(QString::fromUtf8("ValSpinBox"));
        ValSpinBox->setMaximum(255);

        gridLayout->addWidget(ValSpinBox, 4, 8, 1, 2);

        ModeLabel = new QLabel(DevicePageUi);
        ModeLabel->setObjectName(QString::fromUtf8("ModeLabel"));

        gridLayout->addWidget(ModeLabel, 5, 0, 1, 1);

        ModeBox = new QComboBox(DevicePageUi);
        ModeBox->setObjectName(QString::fromUtf8("ModeBox"));

        gridLayout->addWidget(ModeBox, 5, 1, 1, 3);

        ColorLabel = new QLabel(DevicePageUi);
        ColorLabel->setObjectName(QString::fromUtf8("ColorLabel"));

        gridLayout->addWidget(ColorLabel, 6, 0, 1, 1);

        PerLEDCheck = new QRadioButton(DevicePageUi);
        PerLEDCheck->setObjectName(QString::fromUtf8("PerLEDCheck"));

        gridLayout->addWidget(PerLEDCheck, 6, 1, 1, 1);

        ModeSpecificCheck = new QRadioButton(DevicePageUi);
        ModeSpecificCheck->setObjectName(QString::fromUtf8("ModeSpecificCheck"));

        gridLayout->addWidget(ModeSpecificCheck, 6, 2, 1, 1);

        RandomCheck = new QRadioButton(DevicePageUi);
        RandomCheck->setObjectName(QString::fromUtf8("RandomCheck"));

        gridLayout->addWidget(RandomCheck, 6, 3, 1, 1);

        ButtonRed = new QPushButton(DevicePageUi);
        ButtonRed->setObjectName(QString::fromUtf8("ButtonRed"));

        gridLayout->addWidget(ButtonRed, 6, 4, 1, 1);

        ButtonYellow = new QPushButton(DevicePageUi);
        ButtonYellow->setObjectName(QString::fromUtf8("ButtonYellow"));

        gridLayout->addWidget(ButtonYellow, 6, 5, 1, 1);

        ButtonGreen = new QPushButton(DevicePageUi);
        ButtonGreen->setObjectName(QString::fromUtf8("ButtonGreen"));

        gridLayout->addWidget(ButtonGreen, 6, 6, 1, 1);

        ButtonCyan = new QPushButton(DevicePageUi);
        ButtonCyan->setObjectName(QString::fromUtf8("ButtonCyan"));

        gridLayout->addWidget(ButtonCyan, 6, 7, 1, 1);

        ButtonBlue = new QPushButton(DevicePageUi);
        ButtonBlue->setObjectName(QString::fromUtf8("ButtonBlue"));

        gridLayout->addWidget(ButtonBlue, 6, 8, 1, 1);

        ButtonMagenta = new QPushButton(DevicePageUi);
        ButtonMagenta->setObjectName(QString::fromUtf8("ButtonMagenta"));

        gridLayout->addWidget(ButtonMagenta, 6, 9, 1, 1);

        SpeedLabel = new QLabel(DevicePageUi);
        SpeedLabel->setObjectName(QString::fromUtf8("SpeedLabel"));

        gridLayout->addWidget(SpeedLabel, 7, 0, 1, 1);

        SpeedSlider = new QSlider(DevicePageUi);
        SpeedSlider->setObjectName(QString::fromUtf8("SpeedSlider"));
        SpeedSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(SpeedSlider, 7, 1, 1, 3);

        DirectionLabel = new QLabel(DevicePageUi);
        DirectionLabel->setObjectName(QString::fromUtf8("DirectionLabel"));

        gridLayout->addWidget(DirectionLabel, 8, 0, 1, 1);

        DirectionBox = new QComboBox(DevicePageUi);
        DirectionBox->setObjectName(QString::fromUtf8("DirectionBox"));

        gridLayout->addWidget(DirectionBox, 8, 1, 1, 3);


        retranslateUi(DevicePageUi);

        QMetaObject::connectSlotsByName(DevicePageUi);
    } // setupUi

    void retranslateUi(QWidget *DevicePageUi)
    {
        DevicePageUi->setWindowTitle(QCoreApplication::translate("DevicePageUi", "Form", nullptr));
        ZoneLabel->setText(QCoreApplication::translate("DevicePageUi", "Zone:", nullptr));
        ResizeButton->setText(QCoreApplication::translate("DevicePageUi", "Resize", nullptr));
        LEDLabel->setText(QCoreApplication::translate("DevicePageUi", "LED:", nullptr));
        SetLabel->setText(QCoreApplication::translate("DevicePageUi", "Set:", nullptr));
        SetDeviceButton->setText(QCoreApplication::translate("DevicePageUi", "Device", nullptr));
        SetZoneButton->setText(QCoreApplication::translate("DevicePageUi", "Zone", nullptr));
        SetLEDButton->setText(QCoreApplication::translate("DevicePageUi", "LED", nullptr));
        RedLabel->setText(QCoreApplication::translate("DevicePageUi", "R:", nullptr));
        HueLabel->setText(QCoreApplication::translate("DevicePageUi", "H:", nullptr));
        SetAllButton->setText(QCoreApplication::translate("DevicePageUi", "Set All Devices", nullptr));
        GreenLabel->setText(QCoreApplication::translate("DevicePageUi", "G:", nullptr));
        SatLabel->setText(QCoreApplication::translate("DevicePageUi", "S:", nullptr));
        BlueLabel->setText(QCoreApplication::translate("DevicePageUi", "B:", nullptr));
        ValLabel->setText(QCoreApplication::translate("DevicePageUi", "V:", nullptr));
        ModeLabel->setText(QCoreApplication::translate("DevicePageUi", "Mode:", nullptr));
        ColorLabel->setText(QCoreApplication::translate("DevicePageUi", "Colors:", nullptr));
        PerLEDCheck->setText(QCoreApplication::translate("DevicePageUi", "Per-LED", nullptr));
        ModeSpecificCheck->setText(QCoreApplication::translate("DevicePageUi", "Mode-Specific", nullptr));
        RandomCheck->setText(QCoreApplication::translate("DevicePageUi", "Random", nullptr));
        ButtonRed->setText(QString());
        ButtonYellow->setText(QString());
        ButtonGreen->setText(QString());
        ButtonCyan->setText(QString());
        ButtonBlue->setText(QString());
        ButtonMagenta->setText(QString());
        SpeedLabel->setText(QCoreApplication::translate("DevicePageUi", "Speed:", nullptr));
        DirectionLabel->setText(QCoreApplication::translate("DevicePageUi", "Dir:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DevicePageUi: public Ui_DevicePageUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEPAGE_H

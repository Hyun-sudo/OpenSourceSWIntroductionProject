/********************************************************************************
** Form generated from reading UI file 'rgbdialog02.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RGBDIALOG02_H
#define UI_RGBDIALOG02_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RGBDialog02Ui
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *MainTabBar;
    QWidget *TabDevices;
    QGridLayout *gridLayout_4;
    QTabWidget *DevicesTabBar;
    QWidget *TabInformation;
    QGridLayout *gridLayout_5;
    QTabWidget *InformationTabBar;
    QPushButton *ButtonSaveProfile;
    QPushButton *ButtonLoadProfile;
    QPushButton *ButtonDeleteProfile;
    QComboBox *ProfileBox;

    void setupUi(QMainWindow *RGBDialog02Ui)
    {
        if (RGBDialog02Ui->objectName().isEmpty())
            RGBDialog02Ui->setObjectName(QString::fromUtf8("RGBDialog02Ui"));
        RGBDialog02Ui->resize(700, 350);
        centralwidget = new QWidget(RGBDialog02Ui);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        MainTabBar = new QTabWidget(centralwidget);
        MainTabBar->setObjectName(QString::fromUtf8("MainTabBar"));
        MainTabBar->setTabShape(QTabWidget::Rounded);
        MainTabBar->setIconSize(QSize(20, 20));
        TabDevices = new QWidget();
        TabDevices->setObjectName(QString::fromUtf8("TabDevices"));
        gridLayout_4 = new QGridLayout(TabDevices);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        DevicesTabBar = new QTabWidget(TabDevices);
        DevicesTabBar->setObjectName(QString::fromUtf8("DevicesTabBar"));
        DevicesTabBar->setTabPosition(QTabWidget::West);

        gridLayout_4->addWidget(DevicesTabBar, 1, 0, 1, 1);

        MainTabBar->addTab(TabDevices, QString());
        TabInformation = new QWidget();
        TabInformation->setObjectName(QString::fromUtf8("TabInformation"));
        gridLayout_5 = new QGridLayout(TabInformation);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        InformationTabBar = new QTabWidget(TabInformation);
        InformationTabBar->setObjectName(QString::fromUtf8("InformationTabBar"));
        InformationTabBar->setTabPosition(QTabWidget::West);

        gridLayout_5->addWidget(InformationTabBar, 0, 0, 1, 1);

        MainTabBar->addTab(TabInformation, QString());

        gridLayout->addWidget(MainTabBar, 0, 0, 1, 4);

        ButtonSaveProfile = new QPushButton(centralwidget);
        ButtonSaveProfile->setObjectName(QString::fromUtf8("ButtonSaveProfile"));

        gridLayout->addWidget(ButtonSaveProfile, 1, 0, 1, 1);

        ButtonLoadProfile = new QPushButton(centralwidget);
        ButtonLoadProfile->setObjectName(QString::fromUtf8("ButtonLoadProfile"));

        gridLayout->addWidget(ButtonLoadProfile, 1, 1, 1, 1);

        ButtonDeleteProfile = new QPushButton(centralwidget);
        ButtonDeleteProfile->setObjectName(QString::fromUtf8("ButtonDeleteProfile"));

        gridLayout->addWidget(ButtonDeleteProfile, 1, 2, 1, 1);

        ProfileBox = new QComboBox(centralwidget);
        ProfileBox->setObjectName(QString::fromUtf8("ProfileBox"));

        gridLayout->addWidget(ProfileBox, 1, 3, 1, 1);

        RGBDialog02Ui->setCentralWidget(centralwidget);

        retranslateUi(RGBDialog02Ui);

        MainTabBar->setCurrentIndex(1);
        InformationTabBar->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(RGBDialog02Ui);
    } // setupUi

    void retranslateUi(QMainWindow *RGBDialog02Ui)
    {
        RGBDialog02Ui->setWindowTitle(QCoreApplication::translate("RGBDialog02Ui", "MainWindow", nullptr));
        MainTabBar->setTabText(MainTabBar->indexOf(TabDevices), QCoreApplication::translate("RGBDialog02Ui", "Devices", nullptr));
        MainTabBar->setTabText(MainTabBar->indexOf(TabInformation), QCoreApplication::translate("RGBDialog02Ui", "Information", nullptr));
        ButtonSaveProfile->setText(QCoreApplication::translate("RGBDialog02Ui", "Save Profile", nullptr));
        ButtonLoadProfile->setText(QCoreApplication::translate("RGBDialog02Ui", "Load Profile", nullptr));
        ButtonDeleteProfile->setText(QCoreApplication::translate("RGBDialog02Ui", "Delete Profile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RGBDialog02Ui: public Ui_RGBDialog02Ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RGBDIALOG02_H

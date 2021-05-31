/********************************************************************************
** Form generated from reading UI file 'zoneresizedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZONERESIZEDIALOG_H
#define UI_ZONERESIZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZoneResizeDialogUi
{
public:
    QSlider *ResizeSlider;
    QDialogButtonBox *buttonBox;
    QSpinBox *ResizeBox;

    void setupUi(QWidget *ZoneResizeDialogUi)
    {
        if (ZoneResizeDialogUi->objectName().isEmpty())
            ZoneResizeDialogUi->setObjectName(QString::fromUtf8("ZoneResizeDialogUi"));
        ZoneResizeDialogUi->resize(400, 180);
        ResizeSlider = new QSlider(ZoneResizeDialogUi);
        ResizeSlider->setObjectName(QString::fromUtf8("ResizeSlider"));
        ResizeSlider->setGeometry(QRect(20, 20, 361, 22));
        ResizeSlider->setOrientation(Qt::Horizontal);
        buttonBox = new QDialogButtonBox(ZoneResizeDialogUi);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 140, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ResizeBox = new QSpinBox(ZoneResizeDialogUi);
        ResizeBox->setObjectName(QString::fromUtf8("ResizeBox"));
        ResizeBox->setGeometry(QRect(260, 80, 121, 22));

        retranslateUi(ZoneResizeDialogUi);

        QMetaObject::connectSlotsByName(ZoneResizeDialogUi);
    } // setupUi

    void retranslateUi(QWidget *ZoneResizeDialogUi)
    {
        ZoneResizeDialogUi->setWindowTitle(QCoreApplication::translate("ZoneResizeDialogUi", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ZoneResizeDialogUi: public Ui_ZoneResizeDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZONERESIZEDIALOG_H

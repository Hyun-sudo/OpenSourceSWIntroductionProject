#ifndef SOFTWAREINFOPAGE_H
#define SOFTWAREINFOPAGE_H

#include "ui_softwareinfopage.h"

#include <QFrame>

namespace Ui {
class SoftwareInfoPage;
}

class SoftwareInfoPage : public QFrame
{
    Q_OBJECT

public:
    explicit SoftwareInfoPage(QWidget *parent = nullptr);
    ~SoftwareInfoPage();

private:
    Ui::SoftwareInfoPageUi *ui;
};

#endif // SOFTWAREINFOPAGE_H

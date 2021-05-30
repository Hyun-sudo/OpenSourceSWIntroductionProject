#ifndef SOFTWAREINFOPAGE_H
#define SOFTWAREINFOPAGE_H

#include <QWidget>

namespace Ui {
class SoftwareInfoPage;
}

class SoftwareInfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit SoftwareInfoPage(QWidget *parent = nullptr);
    ~SoftwareInfoPage();

private:
    Ui::SoftwareInfoPage *ui;
};

#endif // SOFTWAREINFOPAGE_H

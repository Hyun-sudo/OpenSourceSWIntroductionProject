#ifndef SYSTEMINFOPAGE_H
#define SYSTEMINFOPAGE_H

#include <QWidget>

namespace Ui {
class SystemInfoPage;
}

class SystemInfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit SystemInfoPage(QWidget *parent = nullptr);
    ~SystemInfoPage();

private:
    Ui::SystemInfoPage *ui;
};

#endif // SYSTEMINFOPAGE_H

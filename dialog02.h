#ifndef DIALOG02_H
#define DIALOG02_H

#include <QWidget>

namespace Ui {
class Dialog02;
}

class Dialog02 : public QWidget
{
    Q_OBJECT

public:
    explicit Dialog02(QWidget *parent = nullptr);
    ~Dialog02();

private:
    Ui::Dialog02 *ui;
};

#endif // DIALOG02_H

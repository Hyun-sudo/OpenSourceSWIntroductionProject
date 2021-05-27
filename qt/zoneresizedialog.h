#ifndef ZONERESIZEDIALOG_H
#define ZONERESIZEDIALOG_H

#include <QWidget>

namespace Ui {
class ZoneResizeDialog;
}

class ZoneResizeDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneResizeDialog(QWidget *parent = nullptr);
    ~ZoneResizeDialog();

private:
    Ui::ZoneResizeDialog *ui;
};

#endif // ZONERESIZEDIALOG_H

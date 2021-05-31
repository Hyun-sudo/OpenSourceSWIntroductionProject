#ifndef ZONERESIZEDIALOG_H
#define ZONERESIZEDIALOG_H

#include "ui_zoneresizedialog.h"

#include <QDialog>

namespace Ui {
class ZoneResizeDialog;
}

class ZoneResizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZoneResizeDialog(int size_min, int size_max, int size_current, QWidget *parent = nullptr);
    ~ZoneResizeDialog();

    int show();

private:
    Ui::ZoneResizeDialogUi *ui;

private slots:
    void on_ResizeSlider_valueChanged(int value);

    void on_ResizeBox_valueChanged(int arg1);
};

#endif // ZONERESIZEDIALOG_H

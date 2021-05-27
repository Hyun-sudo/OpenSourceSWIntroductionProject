#ifndef PROFILESAVEDIALOG_H
#define PROFILESAVEDIALOG_H

#include <QDialog>
#include "ui_DeviceProfileSaveDialog.h"
#include "mainwindow.h"

namespace Ui
{
    class DeviceProfileSaveDialog;
}

class DeviceProfileSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceProfileSaveDialog(QWidget * parent = nullptr);
    ~DeviceProfileSaveDialog();

    std::string show();

private:
    DeviceProfileSaveDialog * ui;
    bool darkTheme = false;
};

#endif // PROFILESAVEDIALOG_H

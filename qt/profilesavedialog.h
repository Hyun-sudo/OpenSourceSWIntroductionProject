#ifndef PROFILESAVEDIALOG_H
#define PROFILESAVEDIALOG_H

#include "ui_profilesavedialog.h"

#include <QDialog>

namespace Ui {
class ProfileSaveDialog;
}

class ProfileSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileSaveDialog(QWidget *parent = nullptr);
    ~ProfileSaveDialog();

    std::string show();

private:
    Ui::ProfileSaveDialogUi *ui;
};

#endif // PROFILESAVEDIALOG_H

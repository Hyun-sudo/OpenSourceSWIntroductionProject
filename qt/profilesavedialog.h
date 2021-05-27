#ifndef PROFILESAVEDIALOG_H
#define PROFILESAVEDIALOG_H

#include <QWidget>

namespace Ui {
class ProfileSaveDialog;
}

class ProfileSaveDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileSaveDialog(QWidget *parent = nullptr);
    ~ProfileSaveDialog();

private:
    Ui::ProfileSaveDialog *ui;
};

#endif // PROFILESAVEDIALOG_H

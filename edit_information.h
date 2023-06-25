#ifndef EDIT_INFORMATION_H
#define EDIT_INFORMATION_H

#include <QWidget>
#include "user.h"
#include "mainmenu.h"
namespace Ui {
class Edit_Information;
}

class Edit_Information : public QWidget
{
    Q_OBJECT

public:
    explicit Edit_Information(QWidget *parent = nullptr);
    ~Edit_Information();

private slots:

    void on_lineEdit_password_editingFinished();

    void on_pushButton_cancel_clicked();

    void on_pushButton_confirm_clicked();

    void on_pushButton_change_avatar_clicked();

private:
    Ui::Edit_Information *ui;
};

#endif // EDIT_INFORMATION_H

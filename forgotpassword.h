#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QWidget>
#include"QValidator"
#include <QMessageBox>
#include"globals.h"
#include"QFile"
namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public QWidget
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    ~ForgotPassword();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ForgotPassword *ui;
};

#endif // FORGOTPASSWORD_H

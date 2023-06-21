#ifndef SIGNUP_H
#define SIGNUP_H
#include<Globals.h>
#include <QWidget>
#include<QMessageBox>
namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_avatarChoice_clicked();

    void on_SignUp_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H

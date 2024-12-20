#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();


private slots:
    void on_commandLinkButton_clicked();

    void on_commandLinkButton_2_clicked();

    void on_Login_2_clicked();

    void on_Exit_clicked();

    void on_Exit_pressed();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H

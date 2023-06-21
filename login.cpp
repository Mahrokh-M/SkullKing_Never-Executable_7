#include "login.h"
#include "ui_login.h"
#include"signup.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
  ui->Login_2->setStyleSheet("QPushButton {background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFD700, stop: 1 #FFA500); color: white; border: none; padding: 10px 20px; font-size: 16px; border-radius: 20px; } QPushButton:hover { background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFDF7F, stop: 1 #FFB37F); } QPushButton:pressed { background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFC87F, stop: 1 #FF8C7F); }");

}

Login::~Login()
{
    delete ui;
}




void Login::on_commandLinkButton_clicked()
{
     SignUp*a=new SignUp();
     a->show();
     this->close();
}


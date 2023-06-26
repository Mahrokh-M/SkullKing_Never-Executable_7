#include "login.h"
#include "ui_login.h"
#include"signup.h"
#include"forgotpassword.h"
#include"globals.h"
#include <QMessageBox>
#include"mainmenu.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
  ui->Login_2->setStyleSheet("QPushButton {background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFD700, stop: 1 #FFA500); color: white; border: none; padding: 10px 20px; font-size: 16px; border-radius: 20px; } QPushButton:hover { background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFDF7F, stop: 1 #FFB37F); } QPushButton:pressed { background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFC87F, stop: 1 #FF8C7F); }");
  connect(ui->UserName, &QLineEdit::returnPressed, [=]() {
      ui->Password->setFocus();
  });
      connect(ui->Password, &QLineEdit::returnPressed, ui->Login_2, &QPushButton::click);
      ui->Exit->setStyleSheet(QString("QWidget { border-image: url(%1); }").arg(":/new/prefix1/closedoor.png"));
}

Login::~Login()
{
    delete ui;
}




void Login::on_commandLinkButton_clicked()
{
     SignUp*a=new SignUp();
     a->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
     a->show();
     this->close();
}


void Login::on_commandLinkButton_2_clicked()
{
    ForgotPassword*b=new ForgotPassword();
    b->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    b->show();
    this->close();
}


void Login::on_Login_2_clicked()
{

        QLabel* errorLabel = new QLabel("*", ui->UserName);
        errorLabel->setStyleSheet("color: red; font-weight: bold;");
        QLabel* errorLabel2 = new QLabel("*", ui->Password);
        errorLabel2->setStyleSheet("color: red; font-weight: bold;");
        if (ui->UserName->text().isEmpty()) {
            errorLabel->setVisible(true);}
            if (ui->Password->text().isEmpty()) {
                errorLabel2->setVisible(true);}
        connect(ui->UserName, &QLineEdit::textChanged, this, [this, errorLabel]() {
            if (!ui->UserName->text().isEmpty()) {
                errorLabel->setVisible(false);
            } else {
                errorLabel->setVisible(true);
            }
        });

        connect(ui->Password, &QLineEdit::textChanged, this, [this, errorLabel2]() {
            if (!ui->Password->text().isEmpty()) {
                errorLabel2->setVisible(false);
            } else {
                errorLabel2->setVisible(true);
            }
        });
        if(!ui->UserName->text().isEmpty()&&!ui->Password->text().isEmpty()){
            bool found=0;
            for (auto it = People.begin(); it != People.end(); ++it){
                if(it->set_get_userName()==ui->UserName->text()&&it->set_get_password()==ui->Password->text()){
                    found=1;
                    this->close();
                    Person=it;
                    MainMenu*a=new MainMenu();
                    a->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
                    a->show();
                    break;
                }
            }
            if(found==0){
                QMessageBox msgBox;
                msgBox.setWindowTitle("User Not Found");
                msgBox.setText("User was not found.");
                msgBox.setIcon(QMessageBox::Critical);

                QString styleSheet = "\
                    QMessageBox {\
                        background-color: #DAA520;\
                        font-size: 16px;\
                        font-weight: bold;\
                    }\
                    QPushButton {\
                        color: #fff;\
                        background-color: #8B4513;\
                        border: none;\
                        padding: 5px 10px;\
                        border-radius: 3px;\
                    }\
                    QPushButton:hover {\
                        background-color: #A0522D;\
                    }\
                ";

                msgBox.setStyleSheet(styleSheet);
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);
                msgBox.exec();
            }
        }
}










void Login::on_Exit_clicked()
{
    ui->Exit->setStyleSheet(QString("QWidget { border-image: url(%1); }").arg(":/new/prefix1/open_door.png"));
    this->close();
}


void Login::on_Exit_pressed()
{
    ui->Exit->setStyleSheet(QString("QWidget { border-image: url(%1); }").arg(":/new/prefix1/open_door.png"));
}


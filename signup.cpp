#include "signup.h"
#include "ui_signup.h"
#include"avatar.h"
#include"login.h"
#include"QValidator"
#include"QFile"
SignUp::SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp)
{
    ChosenAvatar=0;
    ui->setupUi(this);
    ui->SignUp_2->setStyleSheet("QPushButton {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f0d9b5, stop:1 #e1cda6);""border-style: solid;""border-width: 1px;""border-radius: 5px;""border-color: #b59e89;""padding: 5px 10px;""color: #4c4c4c;""font-size: 16px;""font-weight: bold;""}""QPushButton:hover {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e1cda6, stop:1 #f0d9b5);""}""QPushButton:pressed {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d1b78c, stop:1 #e1cda6);""border-style: inset;""}");
    ui->pushButton->setStyleSheet("QPushButton {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f0d9b5, stop:1 #e1cda6);""border-style: solid;""border-width: 1px;""border-radius: 5px;""border-color: #b59e89;""padding: 5px 10px;""color: #4c4c4c;""font-size: 16px;""font-weight: bold;""}""QPushButton:hover {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e1cda6, stop:1 #f0d9b5);""}""QPushButton:pressed {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d1b78c, stop:1 #e1cda6);""border-style: inset;""}");
    ui->avatarChoice->setStyleSheet("QPushButton {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d3b18c, stop:1 #c2a27d);""border-style: solid;""border-width: 1px;""border-radius: 5px;""border-color: #b59e89;""padding: 5px 10px;""color: #40372d;""font-size: 20px;""font-weight: bold;""border-radius:20px;""}""QPushButton:hover {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #c2a27d, stop:1 #d3b18c);""}""QPushButton:pressed {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #b29673, stop:1 #c2a27d);""border-style: inset;""}");
    ui->EmailError->setVisible(false);
    ui->UsernameError->setVisible(false);
    ui->numberError->setVisible(false);
    ui->PassError->setVisible(false);
    ui->nameError->setVisible(false);
    QRegularExpression regex2("^0[1-9]\\d{9}$");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex2, ui->phoneNumber);
    ui->phoneNumber->setValidator(validator);
    connect(ui->Name, &QLineEdit::returnPressed, [=]() {
        ui->username->setFocus();
    });
    connect(ui->username, &QLineEdit::returnPressed, [=]() {
       ui->phoneNumber->setFocus();
    });
    connect(ui->phoneNumber, &QLineEdit::returnPressed, [=]() {
        ui->Email->setFocus();
    });
    connect(ui->Email, &QLineEdit::returnPressed, [=]() {
        ui->Password->setFocus();
    });
    connect(ui->Password, &QLineEdit::returnPressed, ui->SignUp_2, &QPushButton::click);
}


SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_avatarChoice_clicked()
{
    Avatar*a=new Avatar();
    a->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    a->show();
}


void SignUp::on_SignUp_2_clicked()
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    QRegularExpressionMatch match = regex.match(ui->Email->text());
    if (!match.hasMatch()) {
        ui->EmailError->setVisible(true);
    }
    else{
        ui->EmailError->setVisible(false);
    }
    if(ui->Name->text().isEmpty()){
        ui->nameError->setVisible(true);
    }
    else{
        ui->nameError->setVisible(false);
    }
    if(ui->username->text().isEmpty()){
        ui->UsernameError->setVisible(true);
    }
    else{
         ui->UsernameError->setVisible(false);
    }
    if(ui->phoneNumber->text().isEmpty()||ui->phoneNumber->text().length() != 11 || !ui->phoneNumber->hasAcceptableInput()){
        ui->numberError->setVisible(true);
    }
    else{
        ui->numberError->setVisible(false);
    }
    if(ui->Password->text().isEmpty()){
        ui->PassError->setVisible(true);
    }
    else{
        ui->PassError->setVisible(false);
    }
    if(!ui->PassError->isVisible()&&!ui->EmailError->isVisible()&&!ui->nameError->isVisible()&&!ui->numberError->isVisible()&&!ui->UsernameError->isVisible()){
        if(ChosenAvatar==0){
            QMessageBox messageBox;
            messageBox.setWindowTitle("Choose Avatar");
            messageBox.setText("You need to choose your avatar :)");
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.setStyleSheet("QMessageBox { background-color: #F5DEB3; font-size: 16px; font-weight: bold; }");
            QAbstractButton* okButton = messageBox.addButton("Select Avatar", QMessageBox::AcceptRole);
            okButton->setStyleSheet("background-color: #D2B48C; color: white;; font-size: 16px; font-weight: bold;");
            connect(okButton, &QAbstractButton::clicked, [=]() {
                Avatar* avatar = new Avatar();
                avatar->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
                avatar->show();
            });
        messageBox.exec();}
        else{
        User tmp;
        tmp.set_get_name()=ui->Name->text();
        tmp.set_get_userName()=ui->username->text();
        tmp.set_get_money()="1000";
        tmp.set_get_password()=ui->Password->text();
        tmp.set_get_phoneNumber()=ui->phoneNumber->text();
        tmp.set_get_email()=ui->Email->text();
        tmp.set_get_avatar()=ChosenAvatar;
        People.push_back(tmp);
        QString filePath = "Users.txt";
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            for (auto it = People.begin(); it != People.end(); ++it) {
                out << it->set_get_name() <<"/" <<it->set_get_userName() <<"/"<<it->set_get_phoneNumber()<< "/"<<it->set_get_email()<<"/"<<it->set_get_password()<< "/"<<it->set_get_money()<< "/"<<it->set_get_total_win()<< "/"<<it->set_get_total_lose()<<"/"<<it->set_get_avatar()<<"\n";
            }
            file.close();
        }
        this->close();
        Login*a=new Login();
        a->show();
    }
  }
}


void SignUp::on_pushButton_clicked()
{
    this->close();
    Login*a=new Login();
    a->show();
}


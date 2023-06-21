#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include"login.h"

ForgotPassword::ForgotPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("QPushButton {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f9dcc4, stop:1 #f2cfa7);""border-style: solid;""border-width: 1px;""border-radius: 5px;""border-color: #e5b887;""padding: 5px 10px;""color: #423d38;""font-size: 16px;""font-weight: bold;""border-radius:10px;""}""QPushButton:hover {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f2cfa7, stop:1 #f9dcc4);""}""QPushButton:pressed {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e5b887, stop:1 #f2cfa7);""border-style: inset;""}");
    ui->pushButton_2->setStyleSheet("QPushButton {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f9dcc4, stop:1 #f2cfa7);""border-style: solid;""border-width: 1px;""border-radius: 5px;""border-color: #e5b887;""padding: 5px 10px;""color: #423d38;""font-size: 16px;""font-weight: bold;""border-radius:10px;""}""QPushButton:hover {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f2cfa7, stop:1 #f9dcc4);""}""QPushButton:pressed {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e5b887, stop:1 #f2cfa7);""border-style: inset;""}");
    QString phoneRegex = ("^0[1-9]\\d{9}$");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression(phoneRegex), ui->PhoneNum);
    ui->PhoneNum->setValidator(validator);
    QLabel* errorLabel = new QLabel("*", ui->PhoneNum);
    errorLabel->setStyleSheet("color: red; font-weight: bold;");
    errorLabel->setVisible(false);
    connect(ui->PhoneNum, &QLineEdit::textChanged, this, [this, errorLabel]() {
        QString phoneNum = ui->PhoneNum->text();
        if (phoneNum.length() == 11 && ui->PhoneNum->hasAcceptableInput()) {
            errorLabel->setVisible(false);
        } else {
            errorLabel->setVisible(true);
        }
    });

}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::on_pushButton_clicked()
{
    QMessageBox msgBox;
    QString styleSheet = "\
        QMessageBox {\
            background-color: #D2B48C;\
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
      QLabel* errorLabel = new QLabel("*", ui->PhoneNum);
     errorLabel->setStyleSheet("color: red; font-weight: bold;");
     errorLabel->setVisible(false);
     QLabel* errorLabel2 = new QLabel("*", ui->NPassword);
     errorLabel2->setStyleSheet("color: red; font-weight: bold;");
      errorLabel->setVisible(false);
      QLabel* errorLabel3 = new QLabel("*", ui->RPassword);
      errorLabel3->setStyleSheet("color: red; font-weight: bold;");
       errorLabel->setVisible(false);
     connect(ui->PhoneNum, &QLineEdit::textChanged, this, [this, errorLabel]() {
         QString phoneNum = ui->PhoneNum->text();
         if (phoneNum.length() == 11 && ui->PhoneNum->hasAcceptableInput()) {
             errorLabel->setVisible(false);
         } else {
             errorLabel->setVisible(true);
         } });
     connect(ui->NPassword, &QLineEdit::textChanged, this, [this, errorLabel2]() {
         if ( ui->PhoneNum->hasAcceptableInput()) {
             errorLabel2->setVisible(false);
         } else {
             errorLabel2->setVisible(true);
         } });
     connect(ui->RPassword, &QLineEdit::textChanged, this, [this, errorLabel3]() {
         if ( ui->PhoneNum->hasAcceptableInput()) {
             errorLabel3->setVisible(false);
         } else {
             errorLabel3->setVisible(true);
         } });
       QString phoneNum = ui->PhoneNum->text();
    if (ui->PhoneNum->text().isEmpty()||phoneNum.length() != 11 ||!( ui->PhoneNum->hasAcceptableInput())) {
        errorLabel->setVisible(true);
    }
     if(ui->NPassword->text().isEmpty()){
        errorLabel2->setVisible(true);
    }
    if(ui->RPassword->text().isEmpty()){
        errorLabel3->setVisible(true);
    }
    if(!errorLabel->isVisible()&&!errorLabel2->isVisible()&&!errorLabel3->isVisible()) {
        if(ui->NPassword->text()!=ui->RPassword->text()){
            msgBox.setWindowTitle("Password Error");
            msgBox.setText("The passwords do not match.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }
        else{
            bool found=0;
        for (auto it = People.begin(); it != People.end(); ++it){
            if(it->set_get_phoneNumber()==ui->PhoneNum->text()){
                it->set_get_password()=ui->NPassword->text();
                found=1;
                break;
            }
        }
        if(found==0){
            msgBox.setWindowTitle("Not found");
            msgBox.setText("User with this phonenumber was not found.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }
        else{
            msgBox.setWindowTitle("Password Changed");
            msgBox.setText("Password changed successfully:)");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
            QString filePath = "Users.txt";
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                for (auto it = People.begin(); it != People.end(); ++it) {
                    out << it->set_get_name() << "/" <<it->set_get_userName() << "/"<<it->set_get_phoneNumber()<< "/"<<it->set_get_email()<<"/"<<it->set_get_password()<< "/"<<it->set_get_money()<< "/"<<it->set_get_total_win()<< "/"<<it->set_get_total_lose()<<"/"<<it->set_get_avatar()<<"\n";
                }
                file.close();
            }
        }
       this->close();
       Login*a=new Login();
       a->show();}
   }
}



void ForgotPassword::on_pushButton_2_clicked()
{
    this->close();
    Login*a=new Login();
    a->show();
}


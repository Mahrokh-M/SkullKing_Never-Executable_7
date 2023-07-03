#include "edit_information.h"
#include "ui_edit_information.h"
#include <QMessageBox>
#include "ui_mainmenu.h"
#include "user.h"
#include "avatar.h"
#include <globals.h>
#include"QFile"
#include"QValidator"
Edit_Information::Edit_Information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_Information)
{
    ui->setupUi(this);
    QLabel *myLabel=ui->label_background;
    myLabel->lower();
    QString phoneRegex = ("^0[1-9]\\d{9}$");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression(phoneRegex), ui->label_phoneNumber);
    ui->lineEdit_phoneNumber->setValidator(validator);
    ChosenAvatar=Person->set_get_avatar();
    ui->pushButton_confirm->setStyleSheet(""
                                          "QPushButton {background-color: rgb(85, 57, 37);"
                                          "color: rgb(255, 242, 193);"
                                          "border-radius: 10px;"
                                          "font: 700 italic 12pt Calibri; }"
                                          "QPushButton:hover { outline: 3px solid black;color: black;background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFDF7F, stop: 1 #FFB37F)};");
    ui->pushButton_cancel->setStyleSheet(""
                                          "QPushButton {background-color: rgb(85, 57, 37);"
                                          "color: rgb(255, 242, 193);"
                                          "border-radius: 10px;"
                                          "font: 700 italic 12pt Calibri; }"
                                          "QPushButton:hover { outline: 3px solid black;color: black;background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFDF7F, stop: 1 #FFB37F)};"
                                          "QPushButton:pressed { background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFC87F, stop: 1 #FF8C7F); }");
    ui->pushButton_change_avatar->setStyleSheet("QPushButton {"
                                                "    border-radius: 10px;"
                                                "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #2980B9, stop:1 #27AE60);"
                                                "}"
                                                "QPushButton:hover {"
                                                "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1F618D, stop:1 #239B56);"
                                                "}"
                                                "QPushButton:pressed {"
                                                "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #154360, stop:1 #196F3D);"
                                                "}");
    ui->lineEdit_repeatPassword->setVisible(false);
    ui->lineEdit_name->setPlaceholderText(Person->set_get_name());
    ui->lineEdit_username->setPlaceholderText(Person->set_get_userName());
    ui->lineEdit_password->setPlaceholderText(Person->set_get_password());
    ui->lineEdit_phoneNumber->setPlaceholderText(Person->set_get_phoneNumber());
    if(Person->set_get_avatar()==1){
     ui->label_icon->setStyleSheet("QLabel { ""border-image: url(:/new/prefix1/avatar1.png);}");
    }
    else if(Person->set_get_avatar()==2){
        ui->label_icon->setStyleSheet("QLabel { ""border-image: url(:/new/prefix1/avatar2.png);}");
    }
    else if(Person->set_get_avatar()==3){
        ui->label_icon->setStyleSheet("QLabel { ""border-image: url(:/new/prefix1/avatar3.png);}");
    }
    else if(Person->set_get_avatar()==4){
        ui->label_icon->setStyleSheet("QLabel { "
                                      "border-image: url(:/new/prefix1/avatar4.png); }");
    }

    //These lines are here to when the user press enter, it goes to next line edit
    connect(ui->lineEdit_name, &QLineEdit::returnPressed, [=]() {
        ui->lineEdit_username->setFocus();
    });
    connect(ui->lineEdit_username, &QLineEdit::returnPressed, [=]() {
        ui->lineEdit_password->setFocus();
    });
    connect(ui->lineEdit_password, &QLineEdit::returnPressed, [=]() {
        ui->lineEdit_repeatPassword->setFocus();
    });
    connect(ui->lineEdit_repeatPassword, &QLineEdit::returnPressed, [=]() {
        ui->lineEdit_phoneNumber->setFocus();
    });
    connect(ui->lineEdit_phoneNumber, &QLineEdit::returnPressed, ui->pushButton_confirm, &QPushButton::click);


}

Edit_Information::~Edit_Information()
{
    delete ui;
}

void Edit_Information::on_pushButton_confirm_clicked()
{
    if(!ui->lineEdit_password->text().isEmpty()&&ui->lineEdit_repeatPassword->text().isEmpty()){
            QMessageBox messageBox;
            messageBox.setWindowTitle("Password Error");
            messageBox.setText("Repeat your password!");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setStyleSheet("QMessageBox { background-color: #3297a8; font-size: 16px; font-weight: bold; }");
            QAbstractButton* okButton = messageBox.addButton("Ok", QMessageBox::AcceptRole);
            okButton->setStyleSheet("background-color: #262e66; color: white;; font-size: 16px; font-weight: bold;");
        messageBox.exec();

    }
    else if(!ui->lineEdit_password->text().isEmpty()&&!ui->lineEdit_repeatPassword->text().isEmpty()&&(ui->lineEdit_password->text()!=ui->lineEdit_repeatPassword->text())){
        QMessageBox messageBox;
        messageBox.setWindowTitle("Password Error");
        messageBox.setText("Passwords do not match!");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setStyleSheet("QMessageBox { background-color: #3297a8; font-size: 16px; font-weight: bold; }");
        QAbstractButton* okButton = messageBox.addButton("Ok", QMessageBox::AcceptRole);
        okButton->setStyleSheet("background-color: #262e66; color: white;; font-size: 16px; font-weight: bold;");
    messageBox.exec();
    }
    else{
    Person->set_get_avatar()=ChosenAvatar;
    if(!ui->lineEdit_name->text().isEmpty()){
        Person->set_get_name()=ui->lineEdit_name->text();
    }
    if(!ui->lineEdit_phoneNumber->text().isEmpty()){
        Person->set_get_phoneNumber()=ui->label_phoneNumber->text();
    }
    if(!ui->lineEdit_username->text().isEmpty()){
        Person->set_get_userName()=ui->lineEdit_username->text();
    }
    if(!ui->lineEdit_password->text().isEmpty()){
        Person->set_get_password()=ui->lineEdit_password->text();
    }
    QMessageBox messageBox;
    messageBox.setWindowTitle("Edit profile");
    messageBox.setText("The user's profile has been successfully updated!");
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setStyleSheet("QMessageBox { background-color: #3297a8; font-size: 16px; font-weight: bold; }");
    QAbstractButton* okButton = messageBox.addButton("Ok", QMessageBox::AcceptRole);
    okButton->setStyleSheet("background-color: #262e66; color: white;; font-size: 16px; font-weight: bold;");
messageBox.exec();
    MainMenu *main_page=new MainMenu;
    main_page->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    main_page->show();
    this->close();
    QString filePath = "Users.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (auto it = People.begin(); it != People.end(); ++it) {
            out << it->set_get_name() <<"/" <<it->set_get_userName() <<"/"<<it->set_get_phoneNumber()<< "/"<<it->set_get_email()<<"/"<<it->set_get_password()<< "/"<<it->set_get_money()<< "/"<<it->set_get_total_win()<< "/"<<it->set_get_total_lose()<<"/"<<it->set_get_avatar()<<"||";
            for (auto ot = it->set_get_History().begin(); ot != it->set_get_History().end(); ++ot){
                out <<ot->set_get_opponent_username()<<"/"<<ot->set_get_opponent_score()<<"/"<<ot->set_get_user_score()<<"/"<<ot->set_get_game_id()<<"/"<<ot->set_get_result()<<"/"<<ot->set_get_screenshot_path()<<"!!";
            }
            out<<"\n";
        }
        file.close();
    }
  }
}


void Edit_Information::on_lineEdit_password_editingFinished()
{
    ui->lineEdit_repeatPassword->setVisible(true);
    ui->lineEdit_repeatPassword->setPlaceholderText("Repeat your new password!");
}


void Edit_Information::on_pushButton_cancel_clicked()
{
    this->close();
    MainMenu *main_page=new MainMenu();
    main_page->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    main_page->show();

}


void Edit_Information::on_pushButton_change_avatar_clicked()
{

    Avatar *Changing_avatar=new Avatar();
    Changing_avatar->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    Changing_avatar->show();

}

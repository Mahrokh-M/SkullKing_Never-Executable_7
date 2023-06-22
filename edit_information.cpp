#include "edit_information.h"
#include "ui_edit_information.h"
#include <QMessageBox>
#include "ui_mainmenu.h"
#include "user.h"
#include "avatar.h"
#include"globals.h"
Edit_Information::Edit_Information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_Information)
{
    ui->setupUi(this);
    QLabel *myLabel=ui->label_background;
    myLabel->lower();
    Person=new User; //This is temporary
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
    ui->lineEdit_repeatPassword->setVisible(false);
    ui->lineEdit_name->setPlaceholderText(Person->set_get_name());
    ui->lineEdit_username->setPlaceholderText(Person->set_get_userName());
    ui->lineEdit_password->setPlaceholderText(Person->set_get_password());
    ui->lineEdit_phoneNumber->setPlaceholderText(Person->set_get_phoneNumber());
    Person->set_get_avatar()=4;
    if(Person->set_get_avatar()==1){
     ui->label_icon->setStyleSheet("QLabel { ""border-image: url(:/new/prefix2/avatars/avatar1.png);}");
    }
    else if(Person->set_get_avatar()==2){
        ui->label_icon->setStyleSheet("QLabel { ""border-image: url(:/new/prefix2/avatars/avatar2.png);}");
    }
    else if(Person->set_get_avatar()==3){
        ui->label_icon->setStyleSheet("QLabel { ""border-image: url(:/new/prefix2/avatars/avatar3.png);}");
    }
    else if(Person->set_get_avatar()==4){
        ui->label_icon->setStyleSheet("QLabel { "
                                      "border-image: url(:/new/prefix2/avatars/avatar4.png); }");
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
    if(!ui->lineEdit_name->text().isEmpty()){
        Person->set_get_name()=ui->lineEdit_name->text();
    }
    if(!ui->lineEdit_phoneNumber->text().isEmpty()){
        Person->set_get_phoneNumber()=ui->lineEdit_name->text();
    }
    if(!ui->lineEdit_username->text().isEmpty()){
        Person->set_get_userName()=ui->lineEdit_name->text();
    }
    if(!ui->lineEdit_password->text().isEmpty()){
        Person->set_get_password()=ui->lineEdit_name->text();
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
    main_page->show();
    this->close();
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
    main_page->show();

}


void Edit_Information::on_pushButton_change_avatar_clicked()
{

    Avatar *Changing_avatar=new Avatar();
    Changing_avatar->show();
}

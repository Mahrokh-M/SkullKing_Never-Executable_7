#include "edit_information.h"
#include "ui_edit_information.h"
#include <QMessageBox>
#include "user.h"
User *Person; //This is temporary
Edit_Information::Edit_Information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_Information)
{
    ui->setupUi(this);
    Person=new User; //This is temporary
    ui->lineEdit_repeatPassword->setVisible(false);
    ui->lineEdit_name->setPlaceholderText(Person->set_get_name());
    ui->lineEdit_username->setPlaceholderText(Person->set_get_userName());
    ui->lineEdit_password->setPlaceholderText(Person->set_get_password());
    ui->lineEdit_phoneNumber->setPlaceholderText(Person->set_get_phoneNumber());
}

Edit_Information::~Edit_Information()
{
    delete ui;
}

void Edit_Information::on_pushButton_save_clicked()
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
    QMessageBox::information(this, "", "The user's profile has been successfully updated!", QMessageBox::Ok);
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
    MainMenu *main_page=new MainMenu;
    main_page->show();
    this->close();
}


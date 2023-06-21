#include "edit_information.h"
#include "ui_edit_information.h"
#include <QMessageBox>
#include "ui_mainmenu.h"
#include "user.h"
#include "avatar.h"
User *Person; //This is temporary
Edit_Information::Edit_Information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_Information)
{
    ui->setupUi(this);
    QLabel *myLabel=ui->label_background;
    myLabel->lower();
    Person=new User; //This is temporary
    ui->lineEdit_repeatPassword->setVisible(false);
    ui->lineEdit_name->setPlaceholderText(Person->set_get_name());
    ui->lineEdit_username->setPlaceholderText(Person->set_get_userName());
    ui->lineEdit_password->setPlaceholderText(Person->set_get_password());
    ui->lineEdit_phoneNumber->setPlaceholderText(Person->set_get_phoneNumber());
    //QPixmap user_avatar(":/new/prefix2/avatars/avatar1.png");
    //user_avatar= user_avatar.scaled(ui->label_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //int diameter = qMin(ui->label_icon->width(), ui->label_icon->height());
    //QPainterPath path;
    //path.addEllipse(0, 0, diameter, diameter);
    //ui->label_icon->setMask(QRegion(path.toFillPolygon().toPolygon()));
    //ui->label_icon->setAlignment(Qt::AlignCenter);
    //ui->label_icon->setPixmap(user_avatar);
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
    /*ui->label_icon->setStyleSheet("QLabel { "
                                  "color: #333333; "
                                  "border: 4px solid black;}");
                                  //"border-radius: 50%;}");*/

    ui->label_border->setStyleSheet("QLabel { "
                                  "color: #333333; "
                                  //"border: 4px solid #d9c8a9;"
                                  "border-radius: 10px;"
                                  "margin-bottom: 5px; }");
    ui->label_name->setStyleSheet("QLabel { "
                                  "font: 14pt Segoe Print;"
                                  " font-weight: bold; "
                                  "color: white; "
                                  "margin-bottom: 5px; }");
    ui->lineEdit_name->setStyleSheet("QLineEdit { "
                                     "font-size: 14px;"
                                     " border: 2px solid #402f0f;"
                                     " border-radius: 10px;"
                                     "background-color: qlineargradient(spread:pad, x1:0.849019, y1:0.272, x2:0, y2:1, stop:0 rgba(92, 60, 30, 249), stop:1 rgba(255, 255, 255, 255));"
                                     " padding: 5px;"
                                     " }"
                                     " QLineEdit:focus { border-color: #CCCCCC; }");
    ui->label_phoneNumber->setStyleSheet("QLabel { "
                                  "font: 14pt Segoe Print;"
                                  " font-weight: bold; "
                                  " font-weight: bold; "
                                  "color: white; "
                                  "margin-bottom: 5px; }");
    ui->lineEdit_phoneNumber->setStyleSheet("QLineEdit { "
                                     "font-size: 14px;"
                                     " border: 2px solid #402f0f;"
                                     " border-radius: 10px;"
                                     "background-color: qlineargradient(spread:pad, x1:0.849019, y1:0.272, x2:0, y2:1, stop:0 rgba(92, 60, 30, 249), stop:1 rgba(255, 255, 255, 255));"
                                     " padding: 5px;"
                                     " }"
                                     " QLineEdit:focus { border-color: #CCCCCC; }");
    ui->label_username->setStyleSheet("QLabel { "
                                  "font: 14pt Segoe Print;"
                                  " font-weight: bold; "
                                  "color: white; "
                                  "margin-bottom: 5px; }");
    ui->lineEdit_username->setStyleSheet("QLineEdit { "
                                     "font-size: 14px;"
                                     " border: 2px solid #402f0f;"
                                     " border-radius: 10px;"
                                     "background-color: qlineargradient(spread:pad, x1:0.849019, y1:0.272, x2:0, y2:1, stop:0 rgba(92, 60, 30, 249), stop:1 rgba(255, 255, 255, 255));"
                                     " padding: 5px;"
                                     //"margin-bottom: 35px;"
                                     " }"
                                     " QLineEdit:focus { border-color: #CCCCCC; }");
    ui->label_password->setStyleSheet("QLabel { "
                                  "font: 14pt Segoe Print;"
                                  " font-weight: bold; "
                                  "color: white; "
                                  "margin-bottom: 5px; }");
    ui->lineEdit_password->setStyleSheet("QLineEdit { "
                                     "font-size: 14px;"
                                     " border: 2px solid #402f0f;"
                                     " border-radius: 10px;"
                                     "background-color: qlineargradient(spread:pad, x1:0.849019, y1:0.272, x2:0, y2:1, stop:0 rgba(92, 60, 30, 249), stop:1 rgba(255, 255, 255, 255));"
                                     " padding: 5px;"
                                     " }"
                                     " QLineEdit:focus { border-color: #CCCCCC; }");
    ui->lineEdit_repeatPassword->setStyleSheet("QLineEdit { "
                                     "font-size: 14px;"
                                     " border: 2px solid #402f0f;"
                                     " border-radius: 10px;"
                                     "background-color: qlineargradient(spread:pad, x1:0.849019, y1:0.272, x2:0, y2:1, stop:0 rgba(92, 60, 30, 249), stop:1 rgba(255, 255, 255, 255));"
                                     " padding: 5px;"
                                     " }"
                                     " QLineEdit:focus { border-color: #CCCCCC; }");
   ui->pushButton_confirm->setStyleSheet("QPushButton {"
                                         "background-color: #d9c8a9; "
                                         "border: none;"
                                         "color: black;"
                                         "border-radius: 7px;"
                                         "font: 700 10pt Segoe Print;"
                                         //"padding: 10px 20px;"
                                         //"text-align: center;"
                                         //"text-decoration: none;"
                                         //"display: inline-block;"
                                         //"font-size: 16px;"
                                         //"margin: 4px 2px;"
                                         //"cursor: pointer;"
                                         //"border-radius: 5px;"
                                         "}"


                                     //Hover effect for save button
                                    "QPushButton:hover{"
                                         "background-color: #3e8e41; //Darker green }");
   ui->pushButton_cancel->setStyleSheet("QPushButton {"
                                         "background-color: #d9c8a9; "
                                         "border: none;"
                                         "color: black;"
                                         "border-radius: 7px;"
                                         "font: 900 10pt Segoe Print;"
                                         //"padding: 10px 20px;"
                                         //"text-align: center;"
                                         //"text-decoration: none;"
                                         //"display: inline-block;"
                                         //"font-size: 16px;"
                                         //"margin: 4px 2px;"
                                         //"cursor: pointer;"
                                         //"border-radius: 5px;"
                                         "}");
   ui->pushButton_change_avatar->setStyleSheet("QPushButton{"
                                               "background-color: qconicalgradient(cx:0.472, cy:0.511364, angle:357.9, stop:0 rgba(35, 40, 3, 255), stop:0.16 rgba(98, 36, 108, 255), stop:0.225 rgba(95, 57, 166, 255), stop:0.285 rgba(74, 74, 204, 255), stop:0.345 rgba(52, 145, 211, 255), stop:0.41784 rgba(112, 217, 245, 255), stop:0.52 rgba(110, 205, 113, 255), stop:0.57 rgba(88, 205, 129, 255), stop:0.635 rgba(45, 179, 156, 255), stop:0.695 rgba(38, 133, 104, 255), stop:0.75 rgba(45, 113, 92, 255), stop:0.807512 rgba(208, 103, 161, 255), stop:0.88 rgba(155, 14, 146, 255), stop:0.934272 rgba(117, 54, 137, 255), stop:1 rgba(35, 40, 3, 255));"
                                               "border-radius: 10px;"
                                               "color: white;"
                                               "font: 700 9pt Segoe Print;"
                                               "}");
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
    this->close();
    MainMenu *main_page=new MainMenu;
    main_page->show();

}


void Edit_Information::on_pushButton_change_avatar_clicked()
{

    Avatar *Changing_avatar=new Avatar();
    Changing_avatar->show();
    this->close();
}


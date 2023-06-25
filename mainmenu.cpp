#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "edit_information.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    ui->pushButton_start->setStyleSheet("QPushButton {"
                                       " border-image: url(:/new/prefix1/push button background.jpg);"
                                       " background-repeat: no-repeat;"
                                       " background-position: center;"
                                       " border: none;"
                                       "padding: 3px 3px;"
                                       "font: 20pt Lucida Calligraphy;"
                                       "color: rgb(255, 255, 255);"
                                       "border-radius: 25px;}"

                                        "QPushButton:hover{ outline: 3px solid rgb(196, 106, 27);}"
                                       );
    ui->pushButton_edit->setStyleSheet("QPushButton {"
                                       " border-image: url(:/new/prefix1/push button background.jpg);"
                                       " background-repeat: no-repeat;"
                                       " background-position: center;"
                                       " border: none;"
                                       "padding: 3px 3px;"
                                       "font: 20pt Lucida Calligraphy;"
                                       "color: rgb(255, 255, 255);"
                                       "border-radius: 25px;}"


                                       "QPushButton:hover{ outline: 3px solid rgb(196, 106, 27);}");

    ui->pushButton_history->setStyleSheet("QPushButton {"
                                       " border-image: url(:/new/prefix1/push button background.jpg);"
                                       " background-repeat: no-repeat;"
                                       " background-position: center;"
                                       " border: none;"
                                       "padding: 3px 3px;"
                                       "font: 20pt Lucida Calligraphy;"
                                       "color: rgb(255, 255, 255);"
                                       "border-radius: 25px;}"

                                          "QPushButton:hover{ outline: 3px solid rgb(196, 106, 27);}"
                                       );
    ui->pushButton_exit->setStyleSheet("QPushButton {"
                                       " border-image: url(:/new/prefix1/push button background.jpg);"
                                       " background-repeat: no-repeat;"
                                       " background-position: center;"
                                       " border: none;"
                                       "padding: 3px 3px;"
                                       "font: 20pt Lucida Calligraphy;"
                                       "color: rgb(255, 255, 255);"
                                       "border-radius: 25px;}"

                                       "QPushButton:hover{ outline: 3px solid rgb(196, 106, 27);}"
                                      );
}

MainMenu::~MainMenu()
{
    delete ui;
}




void MainMenu::on_pushButton_edit_clicked()
{
    this->close();
    Edit_Information *a=new Edit_Information();
    a->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    a->show();

}

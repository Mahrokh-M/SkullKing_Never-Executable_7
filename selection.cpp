#include "selection.h"
#include "ui_selection.h"
#include "maingame.h"
#include"server.h"
#include"globals.h"
#include"mainmenu.h"
Selection::Selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Selection)
{
    ui->setupUi(this);
    ui->Server->setStyleSheet("QPushButton {"
                              "    border-radius: 10px;"
                              "    background-color: #3b1e10;"
                              "    color: #fbf7eb;"
                              "    font-weight: bold;"
                              "    font-size: 20px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #5a2f1c;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #7b4331;"
                              "}");
    ui->Client->setStyleSheet("QPushButton {"
                              "    border-radius: 10px;"
                              "    background-color: #3b1e10;"
                              "    color: #fbf7eb;"
                              "    font-weight: bold;"
                              "    font-size: 20px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #5a2f1c;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #7b4331;"
                              "}");
    ui->Exit->setStyleSheet("QPushButton {"
                              "    border-radius: 10px;"
                              "    background-color: #3b1e10;"
                              "    color: #fbf7eb;"
                              "    font-weight: bold;"
                              "    font-size: 20px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #5a2f1c;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #7b4331;"
                              "}");
}

Selection::~Selection()
{
    delete ui;
}



void Selection::on_Server_clicked()
{
    server_or_client=1;
    Server*a=new Server();
    a->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    a->show();
    a->hide();
    this->close();
    mainGame*b=new mainGame();
    b->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    b->show();
}


void Selection::on_Client_clicked()
{
    server_or_client=2;
    this->close();
    mainGame*a=new mainGame();
    a->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    a->show();
}





void Selection::on_Exit_clicked()
{
    this->close();
    MainMenu*a=new MainMenu();
    a->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    a->show();
}




#include "each_game_history.h"
#include "ui_each_game_history.h"
#include <globals.h>

Each_game_history::Each_game_history(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Each_game_history)
{
    ui->setupUi(this);
    qDebug()<<Person->set_get_userName();
    Game_history selected_game;
    for(auto it=Person->set_get_History().begin(); it!=Person->set_get_History().end(); it++){
        if(it->set_get_game_id()==chosen_game_id)
            selected_game=*it;
    }
    ui->pushButton_back->setStyleSheet("QPushButton {background-color: rgb(85, 57, 37);"
                                          "color: rgb(255, 242, 193);"
                                          "border-radius: 10px;"
                                          "outline: 3px solid #e0cc9f;"
                                          "font: 700 italic 12pt Calibri; }"
                                          "QPushButton:hover { outline: 3px solid black;color: black;background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FFDF7F, stop: 1 #FFB37F)};");
    ui->result->setText(selected_game.set_get_result());
    ui->opponent_username->setText(selected_game.set_get_opponent_username());
    ui->your_score->setText(selected_game.set_get_user_score());
    ui->opponent_score->setText(selected_game.set_get_opponent_score());
    if(selected_game.set_get_screenshot_path()!=""){
      ui->label_screenshot->setStyleSheet(QString("border-image: url(%1);").arg(selected_game.set_get_screenshot_path()));
    }
}

Each_game_history::~Each_game_history()
{
    delete ui;
}

void Each_game_history::on_pushButton_back_clicked()
{
    this->close();
    History *prev_page=new History();
    prev_page->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    prev_page->show();
}


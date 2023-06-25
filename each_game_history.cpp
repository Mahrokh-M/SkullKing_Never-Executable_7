#include "each_game_history.h"
#include "ui_each_game_history.h"
#include <globals.h>

Each_game_history::Each_game_history(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Each_game_history)
{
    ui->setupUi(this);
    Game_history selected_game;
    for(auto it=Person->set_get_History().begin(); it!=Person->set_get_History().end(); it++){
        if(it->set_get_game_id()==chosen_game_id)
            selected_game=*it;
    }
    ui->result->setText(selected_game.set_get_result());
    ui->opponent_username->setText(selected_game.set_get_opponent_username());
    ui->your_score->setText(selected_game.set_get_user_score());
    ui->opponent_score->setText(selected_game.set_get_opponent_score());
}

Each_game_history::~Each_game_history()
{
    delete ui;
}

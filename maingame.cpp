#include "maingame.h"
#include "ui_maingame.h"

mainGame::mainGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainGame)
{
    ui->setupUi(this);
}

mainGame::~mainGame()
{
    delete ui;
}

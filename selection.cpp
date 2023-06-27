#include "selection.h"
#include "ui_selection.h"
#include "maingame.h"
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
}

Selection::~Selection()
{
    delete ui;
}




void Selection::on_pushButton_clicked()
{
    this->close();
    mainGame* a=new mainGame;
    a->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    a->show();

}


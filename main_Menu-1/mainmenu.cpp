#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "edit_information.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    QMenuBar *menu=new QMenuBar;
}

MainMenu::~MainMenu()
{
    delete ui;
}




void MainMenu::on_pushButton_edit_clicked()
{
    Edit_Information *a=new Edit_Information();
    a->show();
    this->close();
}


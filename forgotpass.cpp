#include "forgotpass.h"
#include "ui_forgotpass.h"

ForgotPass::ForgotPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPass)
{
    ui->pushButton->setStyleSheet("QPushButton {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f9dcc4, stop:1 #f2cfa7);""border-style: solid;""border-width: 1px;""border-radius: 5px;""border-color: #e5b887;""padding: 5px 10px;""color: #423d38;""font-size: 16px;""font-weight: bold;""border-radius:10px;""}""QPushButton:hover {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f2cfa7, stop:1 #f9dcc4);""}""QPushButton:pressed {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e5b887, stop:1 #f2cfa7);""border-style: inset;""}");
    ui->pushButton_2->setStyleSheet("QPushButton {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f9dcc4, stop:1 #f2cfa7);""border-style: solid;""border-width: 1px;""border-radius: 5px;""border-color: #e5b887;""padding: 5px 10px;""color: #423d38;""font-size: 16px;""font-weight: bold;""border-radius:10px;""}""QPushButton:hover {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f2cfa7, stop:1 #f9dcc4);""}""QPushButton:pressed {""background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e5b887, stop:1 #f2cfa7);""border-style: inset;""}");
    ui->setupUi(this);
}

ForgotPass::~ForgotPass()
{
    delete ui;
}

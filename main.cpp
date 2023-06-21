#include "mainwindow.h"
#include"login.h"
#include"signup.h"
#include <QApplication>
#include<globals.h>
#include<QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //reading users info from files
    QString filePath = "Users.txt";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split("/");
            QString name = fields[0];
            QString username = fields[1];
            QString phonenumber = fields[2];
            QString email=fields[3];
            QString password = fields[4];
            QString money = fields[5];
            QString win = fields[6];
            QString lose = fields[7];
            QString avatar = fields[8];
            User tmp;
            tmp.set_get_name()=name;
            tmp.set_get_userName()=username;
            tmp.set_get_money()=money;
            tmp.set_get_password()=password;
            tmp.set_get_phoneNumber()=phonenumber;
            tmp.set_get_email()=email;
            tmp.set_get_total_win()=win.toInt();
            tmp.set_get_total_lose()=lose.toInt();
            tmp.set_get_avatar()=avatar.toInt();
            People.push_back(tmp);
            }

        file.close();
    }
    Login w;
    w.show();
    return a.exec();
}

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
            QStringList fields = line.split("||");
            QString name = fields[0].split("/")[0];
            QString username = fields[0].split("/")[1];
            QString phonenumber = fields[0].split("/")[2];
            QString email=fields[0].split("/")[3];
            QString password = fields[0].split("/")[4];
            QString money = fields[0].split("/")[5];
            QString win = fields[0].split("/")[6];
            QString lose = fields[0].split("/")[7];
            QString avatar = fields[0].split("/")[8];
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
            QStringList fields2=fields[1].split("!!");
            for(int i=0;i!=fields2.size()-1;i++){
            QString opponent_username=fields2[i].split("/")[0];
            QString opponent_score=fields2[i].split("/")[1];
            QString user_score=fields2[i].split("/")[2];
            QString game_id=fields2[i].split("/")[3];
            QString result=fields2[i].split("/")[4];
            QString screenshot_path=fields2[i].split("/")[5];
            Game_history a;
            a.set_get_opponent_username()=opponent_username;
            a.set_get_opponent_score()=opponent_score;
            a.set_get_user_score()=user_score;
            a.set_get_game_id()=game_id;
            a.set_get_result()=result;
            a.set_get_screenshot_path()=screenshot_path;
            tmp.set_get_History().push_back(a);
            }
            People.push_back(tmp);
         }
        file.close();
    }
    Login w;
    w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}

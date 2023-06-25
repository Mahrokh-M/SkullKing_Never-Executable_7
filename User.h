#ifndef USER_H
#define USER_H
#include <Qstring>
#include "history.h"

class User
{
private:
    QString name;
    QString userName;
    QString password;
    QString phoneNumber;
    QString email;
    QString money;
    int total_wins;
    int total_lose;
    int avatar;
    QVector<Game_history> all_games;
    //list<Card> cards;
public:
    User();
    User(QString given_name, QString given_userName, QString given_password, QString given_phoneNumber, QString given_money);
    int& set_get_total_win();
    int& set_get_total_lose();
    int& set_get_avatar();
    QString& set_get_name();
    QString& set_get_userName();
    QString& set_get_password();
    QString& set_get_phoneNumber();
    QString& set_get_email();
    QString& set_get_money();
    void operator=(const User& given_user);
    QVector<Game_history>& set_get_History();
    //list<Card>& set_get_cards();
};

#endif // USER_H

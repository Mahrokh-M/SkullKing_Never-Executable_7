#include "user.h"

User::User() {
    name = "";
    userName = "";
    password = "";
    phoneNumber = "";
    money = "";
    total_wins = 0;
    total_lose = 0;
    avatar= 0;
    num_win=0;
}
User::User(QString given_name, QString given_userName, QString given_password, QString given_phoneNumber, QString given_money) {
    name = given_name;
    userName = given_userName;
    password = given_password;
    phoneNumber = given_phoneNumber;
    money = given_money;
    total_wins = 0;
    total_lose = 0;
}
QString& User::set_get_name() { return name; }
QString& User::set_get_userName() { return userName; }
QString& User::set_get_password() { return password; }
QString& User::set_get_phoneNumber() { return phoneNumber; }
QString& User::set_get_email() { return email; }
QString& User::set_get_money() { return money; }
int& User::set_get_total_win() { return total_wins; }
int& User::set_get_total_lose() { return total_lose; }
int& User::set_get_avatar() { return avatar; }
int& User::set_get_num_win() { return num_win; }
void User::operator=(const User& given_user){
    name = given_user.name;
    userName = given_user.userName;
    password = given_user.password;
    phoneNumber = given_user.phoneNumber;
    money = given_user.money;
    total_wins = given_user.total_wins;
    total_lose = given_user.total_lose;
    avatar=given_user.avatar;
}
QVector<Game_history>& User::set_get_History(){return all_games;}
QVector<int>& User::set_get_cards(){return cards;}

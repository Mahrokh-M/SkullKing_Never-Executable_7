#include "User.h"
User::User() {
	name = "";
	userName = "";
	password = "";
	phoneNumber = "";
	money = "";
	total_wins = 0;
	total_lose = 0;
}
User::User(string given_name, string given_userName, string given_password, string given_phoneNumber, string given_money) {
	name = given_name;
	userName = given_userName;
	password = given_password;
	phoneNumber = given_money;
	money = given_money;
	total_wins = 0;
	total_lose = 0;
}
string& User::set_get_name() { return name; }
string& User::set_get_userName() { return userName; }
string& User::set_get_password() { return password; }
string& User::set_get_phoneNumber() { return phoneNumber; }
string& User::set_get_money() { return money; }
int& User::set_get_total_win() { return total_wins; }
int& User::set_get_total_lose() { return total_lose; }
//vector<History>& User::set_get_History(){return all_games;}
list<Card>& User::set_get_cards(){return cards;}
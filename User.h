#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;
class User
{
private:
	string name;
	string userName;
	string password;
	string phoneNumber;
	string money;
	//list<Card> cards;
	int total_wins;
	int total_lose;
	//vector<History> all_games;
	vector<int> a;
public:
	User();
	User(string given_name, string given_userName, string given_password, string given_phoneNumber, string given_money);
	int& set_get_total_win();
	int& set_get_total_lose();
	string& set_get_name();
	string& set_get_userName();
	string& set_get_password();
	string& set_get_phoneNumber();
	string& set_get_money();
	//vector<History>& set_get_History();
	//list<Card>& set_get_cards();
};


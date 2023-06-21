#pragma once
#include<iostream>
using namespace std;
class History
{
private:
	string opponent_username;
	string opponent_score;
	string user_score;
	//screenshot last round
public:
	History();
	History(string, string, string);
	string get_opponent_username();
	string get_opponent_score();
	string get_user_score();
};


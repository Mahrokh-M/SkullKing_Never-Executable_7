#pragma once
#include<iostream>
using namespace std;
class Card
{private:
	string type; //Queen King Pirate flag parrot treasure map 
	int number;
	int value;
	bool isReserved;
public:
	Card();
	Card(string, int, int, bool);
	string get_type();
	int get_number();
	int get_value();
	bool & set_get_isReserved();
};


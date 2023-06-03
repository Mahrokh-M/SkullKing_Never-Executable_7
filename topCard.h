#pragma once
#include<iostream>
using namespace std;
class topCard
{
protected:
	string type; //Queen King Pirate flag parrot treasure map 
	int value;
	bool isReserved;
public:
	topCard();
	topCard(string, int, bool);
	string& get_type();
	int& get_value();
	bool& set_get_isReserved();

};


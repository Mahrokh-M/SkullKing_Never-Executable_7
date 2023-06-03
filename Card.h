#pragma once
#include<iostream>
#include"topCard.h"
using namespace std;
class Card:public topCard
{
private:
	int number;
public:
	Card();
	Card(string, int, int, bool);
	int&get_number();

};


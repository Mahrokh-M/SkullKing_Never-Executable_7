#include<iostream>
#include"card.h"
#include "User.h"
#include <time.h>
#include <cstdlib>
using namespace std;
int main() {
	vector<User> all_users;//***this is temporary for working with visual studio and will be deleted in qt
	User a;
	all_users.push_back(a);
	int user_index = 0;//***this is also temporary and will be deleted in qt
	int round = 1;
	srand(time(NULL));
	Card all_cards[42]; //An array of all cards we have in the game
	//***Do not forget to declare this as global to be common between server and client!
	for (int i = 0; i < 8; i++) {
		all_cards[i].get_type() = "treasure";
		all_cards[i].get_number() = i + 1;
		all_cards[i].get_value() = i + 1;
	}
	for (int i = 8, j = 0; i < 16; i++, j++) {
		all_cards[i].get_type() = "map";
		all_cards[i].get_number() = j + 1;
		all_cards[i].get_value() = j + 1;
	}
	for (int i = 16, j = 0; i < 24; i++, j++) {
		all_cards[i].get_type() = "parrot";
		all_cards[i].get_number() = j + 1;
		all_cards[i].get_value() = j + 1;
	}
	for (int i = 24, j = 0; i < 32; i++, j++) {
		all_cards[i].get_type() = "flag";
		all_cards[i].get_number() = j + 1;
		all_cards[i].get_value() = j + 11;
	}


}
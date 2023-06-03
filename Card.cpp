#include "Card.h"
Card::Card() {
	type = "";
	number = 0;
	value = 0;
	isReserved = false;
}
Card::Card(string type, int number, int value, bool isReserved) {
	this->type = type;
	this->number = number;
	this->value = value;
	this->isReserved = isReserved;
}
bool&Card::set_get_isReserved(){
	return isReserved;
}
string Card::get_type(){
	return type;
}
int Card::get_number() {
	return number;
}
int Card::get_value(){
	return value;
}
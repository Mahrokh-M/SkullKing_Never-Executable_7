#include "topCard.h"
topCard::topCard() {
	type = "";
	value = 0;
	isReserved = false;
}
topCard::topCard(string type, int value, bool isReserved) {
	this->type = type;
	this->value = value;
	this->isReserved = isReserved;
}
bool& topCard::set_get_isReserved() {
	return isReserved;
}
string& topCard::get_type() {
	return type;
}
int& topCard::get_value() {
	return value;
}
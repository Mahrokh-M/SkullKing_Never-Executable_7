#include "Card.h"
Card::Card():topCard() {
	number = 0;
}
Card::Card(string type, int number, int value, bool isReserved):topCard(type, value, isReserved) {
	this->number = number;
}
int&Card::get_number() {
	return number;
}

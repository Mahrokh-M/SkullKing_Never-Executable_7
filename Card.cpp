#include "card.h"

Card::Card() {
    type = "";
    value = 0;
    isReserved = false;
    number = 0;
}
Card::Card(QString type, int number, int value, bool isReserved) {
    this->type = type;
    this->value = value;
    this->isReserved = isReserved;
    this->number = number;
}
int& Card::get_number() {
    return number;
}
bool& Card::set_get_isReserved() {
    return isReserved;
}
QString& Card::get_type() {
    return type;
}
int& Card::get_value() {
    return value;
}

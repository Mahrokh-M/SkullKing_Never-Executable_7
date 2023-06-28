#ifndef CARD_H
#define CARD_H
#include <QString>

class Card
{
protected:
    QString type; //Queen King Pirate flag parrot treasure map
    int value;
    int number;
    bool isReserved;
public:
    Card();
    Card(QString, int, int, bool);
    int&get_number();
    QString& get_type();
    int& get_value();
    bool& set_get_isReserved();
};

#endif // CARD_H

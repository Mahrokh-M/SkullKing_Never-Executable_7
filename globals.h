#ifndef GLOBALS_H
#define GLOBALS_H
#include<list>
#include<user.h>
#include "history.h"
using namespace std;
    extern list<User> People;
    extern list<User>::iterator Person;
    extern QString chosen_game_id;
    extern int server_or_client;
class Globals
{
public:
    Globals();
};

#endif // GLOBALS_H

#ifndef CANDY_H
#define CANDY_H

#include <string>
#include "colours.h"

using namespace std;

class Candy
{
public:
    string name;
    string description;
    string effectType;
    int effectValue;
    string candy_type;
    int price;

    void printCandy()
    {
        printf(
            MAGENTA_FG "Name: " RESET "%s\n"
            CYAN_FG "Description: " RESET "%s\n"
            GREEN_FG "Effect: " RESET "%s\n"
            GOLD_FG "Effect Value: " RESET "%d\n"
            ORANGE_FG"Candy Type: " RESET "%s\n"
            RED_FG"Price: " RESET "%d\n"
            ,name.c_str()
            ,description.c_str()
            ,effectType.c_str()
            ,effectValue
            ,candy_type.c_str()
            ,price
        );
    }
};
#endif
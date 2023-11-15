#ifndef CANDY_H
#define CANDY_H

#include <string>

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
            "Name: %s\n"
            "Description: %s\n"
            "Effect: %s\n"
            "Effect Value: %d\n"
            "Candy Type: %s\n"
            "Price: %d\n"
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
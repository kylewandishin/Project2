#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "candy.h"
class Player
{
private:
    static const int _MAX_CANDY_AMOUNT = 4;
    std::string _name;
    int _stamina;
    double _gold;
    std::string _effect;
    vector<Candy> _inventory;
    int _candy_amount;
    std::string _nickname;

public:
    Player();
    Player(std::string name, int stamina, double gold, std::string effect, vector<Candy> candy_array);
    int getCandyAmount();
    void setName(std::string name);
    std::string getName();
    void setNickName(std::string nickName);
    std::string getNickName();
    void setStamina(int stamina);
    int getStamina();
    void setGold(double gold);
    double getGold();
    void setEffect(std::string effect);
    std::string getEffect();
    void printInventory();
    Candy findCandy(std::string candy_name);
    bool addCandy(Candy candy);
    bool removeCandy(std::string candy_name);
    bool hasNoCandy();
    void printPlayer();
};

#endif

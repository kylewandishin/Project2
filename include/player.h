#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "candy.h"
class Player
{
private:
    static const int _MAX_CANDY_AMOUNT = 9;
    std::string _name;
    int _stamina;
    double _gold;
    std::string _effect;
    vector<Candy> _inventory;
    int _candy_amount;
    std::string _nickname;
    bool _immune = false;

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
    void printInventory(ostream& out);
    Candy findCandy(std::string candy_name);
    bool addCandy(Candy candy);
    bool removeCandy(std::string candy_name);
    bool removeCandyByType(std::string candy_type);
    bool hasNoCandy();
    bool hasMaxCandy();
    void printPlayer();
    void printPlayer(ostream& out);
    void useCandy(Candy);
    void setImmune(bool);
    bool getImmune();
    vector<Candy> getInventory();
    vector<Candy> getUInventory();
    int skipTurns = 0;
};

#endif

#include "./../../include/player.h"
#include <iostream>

Player::Player() :  _name(""), _stamina(0), _gold(0.0), _effect(""), _candy_amount(0) {
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        _inventory[i].name = "";
        _inventory[i].description = "";
        _inventory[i].price = 0.0;
        _inventory[i].candy_type = "";
    }
}


Player::Player(string name,int stamina, double gold, std::string effect, vector<Candy> candy_array)
    : _name(name),_stamina(stamina), _gold(gold), _effect(effect), _candy_amount(0) {
    
    for (int i = 0; i < _MAX_CANDY_AMOUNT && i < (int)candy_array.size(); i++) {
        _inventory.push_back(candy_array[i]);
        if (!_inventory[i].name.empty()) {
            _candy_amount++;
        }
    }
}

int Player::getCandyAmount() {
    return _candy_amount;
}

void Player::setName(std::string name){
    _name = name;
}
    
string Player::getName(){
    return _name;
}

void Player::setNickName(std::string nickName){
    _nickname = nickName;
}
std::string Player::getNickName(){
    return _nickname;
}

void Player::setStamina(int stamina) {
    _stamina = stamina;
}

int Player::getStamina() {
    return _stamina;
}

void Player::setGold(double gold) {
    _gold = gold;
}

double Player::getGold() {
    return _gold;
}

void Player::setEffect(std::string effect) {
    _effect = effect;
}

std::string Player::getEffect() {
    return _effect;
}

void Player::printInventory() {
    int rows = (int)_inventory.size();
    rows = rows/3 + (rows%3!=0?1:0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            int index = i * 2 + j;
            if (index < _candy_amount) {
                std::cout << "[" << _inventory[index].name << "] ";
            }
        }
        std::cout << std::endl;
    }
}
bool Player::hasNoCandy() {
    return _candy_amount == 0;
}
Candy Player::findCandy(std::string candy_name) {
    bool isEqual;
    for (int i = 0; i < _candy_amount; i++) {
        isEqual = false;
        if (candy_name.size() == _inventory[i].name.size()){
            isEqual = true;
            for (size_t j = 0; j < candy_name.size(); ++j) {
                if (std::tolower(candy_name[j]) != std::tolower(_inventory[i].name[j])) {
                    isEqual = false;
                }
            }
        }
        if (isEqual) {
            Candy blankCandy;
            blankCandy.name = _inventory[i].name;
            blankCandy.description = _inventory[i].description;
            blankCandy.price = _inventory[i].price;
            blankCandy.candy_type = _inventory[i].candy_type;
            return blankCandy;  // Return a blank Candy if not found
        }
    }
    Candy blankCandy;
    blankCandy.name = "";
    blankCandy.description = "";
    blankCandy.price = 0.0;
    blankCandy.candy_type = "";
    return blankCandy;  // Return a blank Candy if not found
}

bool Player::addCandy(Candy candy) {
    for (Candy c: _inventory){
        if (c.name == candy.name)
            return false;
    }
    _inventory.push_back(candy);
    _candy_amount++;
    return true;
}

bool Player::removeCandy(std::string candy_name) {
    bool isEqual;
    for (int i = 0; i < _candy_amount; i++) {
        isEqual = false;
        if (candy_name.size() == _inventory[i].name.size()){
            isEqual = true;
            for (size_t j = 0; j < candy_name.size(); ++j) {
                if (std::tolower(candy_name[j]) != std::tolower(_inventory[i].name[j])) {
                    isEqual = false;
                }
            }
        }
        if (isEqual) {
            for (int j = i; j < (int)_inventory.size(); j++) {
                _inventory[j] = _inventory[j + 1];
            }
            _candy_amount--;
            return true;
        }
    }
    return false;
}

void Player::printPlayer(){
    printf(
    "Name: %s\n"
    "Stamina: %d\n"
    "Gold: %.2f\n"
    "Candies:\n"
    ,_name.c_str()
    ,_stamina
    ,_gold
    );
    printInventory();
    printf("--------------------------------------------------------------------------\n");
}

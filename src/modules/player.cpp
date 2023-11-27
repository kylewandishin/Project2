#include "./../../include/player.h"
#include "./../../include/colours.h"
#include <iostream>
#include <set>

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
    for (size_t i = 0; i < candy_array.size(); i++){
        _inventory.push_back(candy_array[i]);
        _candy_amount++;
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
    if (stamina >100)
        _stamina = 100;
    else if (stamina<0)
        _stamina = 0;
    else
        _stamina = stamina;
}

int Player::getStamina() {
    return _stamina;
}

void Player::setGold(double gold) {
    if (gold >100)
        _gold = 100;
    else if (gold<0)
        _gold = 0;
    else
        _gold = gold;
}

double Player::getGold() {
    return _gold;
}

void Player::setImmune(bool immune){
    _immune = immune;
}

bool Player::getImmune(){
    return _immune;
}

void Player::setEffect(std::string effect) {
    _effect = effect;
}

std::string Player::getEffect() {
    return _effect;
}

void Player::printInventory() {
    for (int i = 0; i < (int)_inventory.size(); i++){
        std::cout << "[" << _inventory[i].name << "] ";
        if ((i+1)%3==0)
            printf("\n");
    }
    if ((int)_inventory.size()%3!=0)
        printf("\n");
}
void Player::printInventory(ostream &outFile) {
    for (int i = 0; i < (int)_inventory.size(); i++){
        outFile << ("[" + _inventory[i].name + "] ");
        if ((i+1)%3==0)
            outFile << "\n";
    }
    if ((int)_inventory.size()%3!=0)
        outFile <<"\n";
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
            Candy temp = {
                _inventory[i].name,
                _inventory[i].description,
                _inventory[i].effectType,
                _inventory[i].effectValue,
                _inventory[i].candy_type,
                _inventory[i].price
            };
            return temp;  // Return a blank Candy if not found
        }
    }
    Candy blankCandy={
        "",
        "",
        "",
        0,
        "",
        0,
    };
    return blankCandy;  // Return a blank Candy if not found
}

bool Player::addCandy(Candy candy) {
    if ((int)_inventory.size() >= _MAX_CANDY_AMOUNT){
        printf("sorry, inventory is full. please remove a candy first\n");
        return false;
    }
    _inventory.push_back(candy);
    _candy_amount++;
    return true;
}
bool Player::removeCandyByType(std::string candy_type){
    bool isEqual;
    vector<string> worked;
    for (int i = 0; i < (int)_inventory.size(); i++) {
        isEqual = false;
        if (candy_type.size() == _inventory[i].candy_type.size()){
            isEqual = true;
            for (size_t j = 0; j < candy_type.size(); ++j) {
                if (std::tolower(candy_type[j]) != std::tolower(_inventory[i].candy_type[j])) {
                    isEqual = false;
                }
            }
        }
        if (isEqual) {
            worked.push_back(_inventory[i].name);
        }
    }
    removeCandy(worked[rand()%((int)worked.size())]);
    return false;
}

bool Player::removeCandy(std::string candy_name) {
    bool isEqual;
    for (int i = 0; i < (int)_inventory.size(); i++) {
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
            for (int j = i; j < (int)_inventory.size()-1; j++) {
                _inventory[j] = _inventory[j + 1];
            }
            printf("fixed\n");
            _candy_amount--;
            _inventory.pop_back();
            return true;
        }
    }
    return false;
}

std::string RAINBOW(const std::string& input) {
    const std::string colors[] = {RED_FG, GREEN_FG, YELLOW_FG, BLUE_FG, MAGENTA_FG, CYAN_FG};
    std::string rainbow_str;
    size_t color_index = 0;

    for (size_t i = 0; i < input.length(); ++i) {
        rainbow_str += colors[color_index] + input.substr(i, 1) + RESET;
        color_index = (color_index + 1) % (sizeof(colors) / sizeof(colors[0]));
    }

    return rainbow_str;
}

void Player::printPlayer(){
    printf(
    MAGENTA_FG "Name: " RESET "%s\n"
    RED_FG "Stamina: " RESET "%d\n"
    GOLD_FG "Gold: " RESET "%.2f\n"
    CYAN_FG "Candies:\n" RESET
    ,_name.c_str()
    ,_stamina
    ,_gold
    );
    printInventory();
    printf( "%s" RESET ,RAINBOW("--------------------------------------------------------------------------\n").c_str());
}
void Player::printPlayer(ostream& outFile){ // used for output logs as escape sequences will show up in the text files if i do not remove them.
    outFile 
    << "Player name: " << _nickname << "\n"
    << "Character name: " << _name << "\n"
    << "Stamina: " << _stamina << "\n"
    << "Gold: " << _gold << "\n"
    << "Candies:\n"
    ;
    printInventory(outFile);
    outFile << "\n\n";
}
bool Player::hasMaxCandy(){
    return ((int)_inventory.size()>=9);
}

vector<Candy> Player::getInventory(){
    return _inventory;
}

vector<Candy> Player::getUInventory(){
    set<string> uniqueNames; // use set to track unique items by name
    vector<Candy> uniqueItems;
    for (const Candy& item : _inventory) { // const and refrence to not make a "copy" of item and not alter it
        if (uniqueNames.insert(item.name).second) { // .insert returns pair<it,bool> for where it was placed and successfully added 
            uniqueItems.push_back(item);
        }
    }
    return uniqueItems;
}


void Player::useCandy(Candy candy){
    removeCandy(candy.name);
    if (candy.candy_type == "gummy"){
        skipTurns-=candy.effectValue;
    }else if (candy.candy_type == "magical" || candy.candy_type == "poison"){
        if (!_immune){
            _stamina += candy.effectValue;
            printf("success!\n");
        }else{
            printf("your immunity was used. you are not longer protected.\n");
            _effect = "";
            _immune = false;
        }
    }else if (candy.candy_type == "immunity"){
        _effect = "immune";
        _immune = true;
    }else if (candy.candy_type == "999"){
        _stamina = 100;
        _gold = 1000.0;
        _effect = "immunity";
        _immune = true;
    }else{
        printf("Nothing!\n");
    }
    return;
}
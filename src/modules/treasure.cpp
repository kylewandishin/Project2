#include "./../../include/treasure.h"
#include "./../../include/candy.h"
#include "./../../include/player.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
void addCandySafe(Player& player, Candy c ){
    if (player.hasMaxCandy()){
            char input = 'a';
            string empty;
            while (input!='y'&&input!='n'){
                printf("would you like to remove a candy in your inventory for the %s candy?\n", c.name.c_str());
                cin >> input;
                getline(cin,empty);
            }
            if (input == 'y'){
                while(player.findCandy(empty).name==""){
                    getline(cin,empty);
                }
                player.removeCandy(empty);
            }
            else{
                return;
            }
        }
        player.addCandy(c);
}


Treasure::Treasure(vector<Riddle> riddles, vector<Candy> inventory)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    _inventory = inventory;
    _riddles = riddles;
}
void grantCandy(Player& player){
    const Candy robbery = {
        "Robber's repel",
        "This candy acts as an anti-robbery shield, safeguarding the player's gold from potential theft by others during their journey",
        "other",
        100,
        "robbery",
        1001
    };
    addCandySafe(player, robbery);
}

void candyAquisition(Player& player){
    const Candy jov = {
        "Jelly Bean of Vigor",
        "Using the Jellybean of Vigor, you can restore 50 units of stamina",
        "stamina",
        50,
        "magical",
        1001
    }, tht = {
        "Treasure Hunter's Truffle",
        "This candy allows the player to unlock a hidden treasure",
        "skip",
        100,
        "skip",
        1001
    };

    int weight = rand()%100;
    if (weight<70){
        addCandySafe(player, jov);
    }else{
        addCandySafe(player, tht);
    }
    return;
}

bool playRPS() {
    char p1, p2;
    const char options[3] = {'r','p','s'};
    int i = 0;
    string empty;
    do {
        printf((i == 0 ? "Enter r, p, or s\n" : "Invalid selection!\n"));
        std::cin >> p1;
        getline(cin,empty);
        i++;
    } while (p1 != 'r' && p1 != 'p' && p1 != 's');
    p2 = options[rand()%3];
    if (p1 == p2) {
        printf("Tie! Play again\n");
        return playRPS();
    }
    if ((p1 == 'r' && p2 == 's') || (p1 == 's' && p2 == 'p') || (p1 == 'p' && p2 == 'r')) {
        return true;
    }
    return false;
}

void Treasure::visitTreasure(Player& player)
{
    Riddle rid = _riddles[rand()%(int)_riddles.size()];
    if (player.findCandy("Treasure Hunter's Truffle").name != ""){
        char useCandy = 'a';
        string empty;
        while(useCandy!='y' && useCandy!='n'){
            printf("would you like to use your Treasure Hunter's Truggle?(y/n)\n");
            cin>>useCandy;
            getline(cin,empty);
        }
        if (rid.playRiddle()){
            printf("congratulations!\n");
        }
        else{
            printf("nope!\n");
            return;
        }
    }
    else if (rid.playRiddle()){
        printf("congratulations!\n");
    }
    else{
        printf("nope!\n");
        return;
    }
    int weighted = (rand()%100) + 1;
        if (weighted >= 1  && weighted<=30)
            player.setStamina(player.getStamina() + ((rand()%20)+10));
        if (weighted >= 31 && weighted<= 40)
            player.setGold(player.getGold() + ((rand()%20)+20));
        if (weighted >= 41 && weighted<= 70)
            grantCandy(player);
        if (weighted >= 71 && weighted<= 100)
            candyAquisition(player);
}
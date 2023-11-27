#include "./../../include/store.h"
#include "./../../include/candy.h"
#include "./../../include/player.h"
#include <iostream>
#include <vector>

using namespace std;
Store::Store(vector<Candy> inv, std::string name)
{
    _name = name;
    _inventory = inv;
}
Store::Store()
{
    _name = "none";
    _inventory = {};
}
void Store::setName(string name){
    _name = name;
}
void Store::setInventory(vector<Candy> inventory){
    _inventory = inventory;
}
void Store::visitStore(Player &player)
{
    string empty;
    printf(
        "welcome to %s\n"
        "here is our stock:\n",
        _name.c_str());
    for (Candy c : _inventory)
    {
        printf("-------------------------------------------------------------------------\n");
        c.printCandy();
    }
    printf("-------------------------------------------------------------------------\n");
   
    char doBuy;
    while (doBuy != 'y' && doBuy!='n'){
        printf("Anything catch your eye? (y/n):\n");
        cin >> doBuy;    
        getline(cin,empty);
    }
    if (doBuy == 'y')
    {
        string input;
        bool nameEqual;
        do
        {
            printf("Name of the candy you would like to purchase? (\"e\" to leave store)\n");
            getline(cin, input);
            if (input == "e" || input == "E")
            {
                break;
            }
            for (Candy c : _inventory)
            {
                if (c.name.size() != input.size())
                    continue;

                nameEqual = true;
                for (int i = 0; i < (int)input.size(); i++){
                    if (tolower(input[i]) != tolower(c.name[i])){
                        nameEqual = false;
                        break;
                    }
                }
                if (nameEqual){
                    input = "y";
                    bool failBefore = false;
                    if (player.hasMaxCandy()){
                        printf("Would you like to remove a candy?(y/n)\n");
                        cin >> doBuy;
                        cin.clear();
                        if (doBuy=='y' || doBuy=='Y'){
                            printf("Ok here is a list of candies you have:\n");
                            player.printInventory();
                            cin.ignore();
                            printf("select a candy to remove:\n");
                            getline(cin, input);
                            player.removeCandy(input);
                        }else{
                            failBefore = true;
                        }
                    }
                    input = "y";
                    double gold = player.getGold();
                    if (failBefore){
                        break;
                    }
                    else if (gold<c.price){
                        printf("sorry, you do not have enough gold for this candy!\n");
                        break;
                    }
                    else if(player.addCandy(c)){
                        player.setGold(gold-c.price);
                        printf("Success %s has been purchased, your new gold is %.2f!\n",c.name.c_str(), player.getGold());
                        break;
                    }else{
                        break;
                    }
                }
            }
            if (input == "e" || input == "E")
            {
                break;
            }else if (input!="y"){
                printf("Sorry looks like that candy is not in stock, please try again:\n");
            }
        } while (true);
    }
    printf("Thank you for shopping at %s!\n", _name.c_str());
}
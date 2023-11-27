#ifndef STORE_H
#define STORE_H

#include "candy.h"
#include "player.h"
#include <vector>

class Store{
    private:
        std::string _name;
        vector<Candy> _inventory;
    public:
        Store(vector<Candy> c, std::string name);
        Store();
        void setInventory(vector<Candy>);
        void setName(std::string);
        void visitStore(Player& player);
}; 

#endif
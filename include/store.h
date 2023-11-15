#ifndef STORE_H
#define STORE_H

#include "candy.h"
#include "player.h"
#include <vector>

class Store{
    private:
        vector<Candy> _inventory;
    public:
        Store(vector<Candy> c);
        void visitStore(Player& player);

}; 

#endif
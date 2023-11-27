#ifndef TREASURE_H
#define TREASURE_H

#include "candy.h"
#include "riddle.h"
#include "player.h"
#include <vector>

class Treasure{
    private:
        vector<Candy> _inventory;
        vector<Riddle> _riddles;
    public:
        Treasure(vector<Riddle>,vector<Candy>);
        void visitTreasure(Player& player);
}; 

#endif
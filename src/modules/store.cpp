#include "./../../include/store.h"
#include "./../../include/candy.h"
#include "./../../include/player.h"
#include <iostream>
#include <vector>

using namespace std;
Store::Store(vector<Candy> inv){
    _inventory = inv;
}
void Store::visitStore(Player& player){
    
}
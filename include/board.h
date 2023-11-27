#ifndef BOARD_H
#define BOARD_H

#include "candy.h"
#include "store.h"
#include "colours.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Tile
{
    string color;
    string tile_type;
};


class Board
{
private:
    const static int _BOARD_SIZE = 120;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    Store _candy_stores[_MAX_CANDY_STORE];
    int _candy_store_count;
    vector<int> _player_positions;

public:
    // Board(int);
    Board(int, vector<Candy>);

    // void resetBoard();
    void resetBoard(vector<Candy>);
    Tile getTiles();
    void displayTile(int, ostream& out = std::cout);
    void displayBoard(ostream& out = std::cout);

    int setPlayerPosition(int,int);

    int getBoardSize() const;
    int getCandyStoreCount();
    int getPlayerPosition(int);
    vector<int> getPlayerPositions();

    bool addCandyStore(int position, string name, vector<Candy> inv);
    int isPositionCandyStore(int); 
    void visitCandyStore(int index, Player& player);

    bool movePlayer(int index, int tile_to_move_forward);

};

#endif
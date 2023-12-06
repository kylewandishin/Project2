#include "./../../include/board.h"
#include "./../../include/player.h"
#include "./../../include/store.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

vector<Candy> randomSample(vector<Candy> arr) {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    for (int i = arr.size() - 1; i > 0; --i) { // shuffle arr vector
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
    
    int sampleSize = rand() % 6 + 5; // 5 to 10 for stock of the store

    vector<Candy> result;
    // sample of shuffled vector
    for (int i = 0; i < sampleSize && i < arr.size(); ++i) {
        result.push_back(arr[i]);
    }

    return result;
}

Board::Board(int players, vector<Candy> inv)
{
    for (int i = 0; i < players; i++)
        _player_positions.push_back(0);
    
    resetBoard(inv);
}

void Board::resetBoard(vector<Candy> inv)
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    vector<string> storeNames = {"The Gumdrop Tavern","The Bubblegum Cafe", "The Gummy Cave"};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }
    int storePosition;
    string storeName;

    // |generate store positions
    srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < 3; i++){
        storePosition = (rand()%9 + 9*i)*3; // random number 0-8 then multiply by 3 to get 0,3,6,9,...,24 for a magenta tile
        addCandyStore(storePosition, storeName, randomSample(inv));
        storeNames.erase(remove(storeNames.begin(), storeNames.end(), storeName), storeNames.end());
    }

    // |special tiles
    int tilePos; 
    for (int i = 0; i < rand()%3; i++){
        tilePos = rand()%(_BOARD_SIZE-5);
        _tiles[tilePos].tile_type = "gumdrop forest";
    }
    for (int i = 0; i < rand()%3; i++){
        tilePos = rand()%(_BOARD_SIZE-5);
        _tiles[tilePos].tile_type = "gingerbread house";
    }
    for (int i = 0; i < rand()%3; i++){
        tilePos = rand()%(_BOARD_SIZE-5);
        _tiles[tilePos].tile_type = "ice cream stop";
    } 
    for (int i = 0; i < rand()%8; i++){
        tilePos = rand()%(_BOARD_SIZE-5);
        _tiles[tilePos].tile_type = "shortcut" + to_string((rand()%3)+4);
    }
    for (int i = 0; i < rand()%10; i++){
        tilePos = rand()%(_BOARD_SIZE-5);
        _tiles[tilePos].tile_type = "treasure";
    }
}
 
void Board::displayTile(int position, ostream& out)
{
    Tile target = _tiles[position];

    int numPlayers = _player_positions.size(), pOnT = 0;
    vector<int> pOnTNum;
    for (int i = 0; i < numPlayers; i++){
        if (_player_positions[i] == position){
            pOnT++;
            pOnTNum.push_back(i+1);
        }
    }
    out << target.color;
    if (pOnT == numPlayers)
        out << "all";
    else if (pOnT == 0)
        out << "   ";
    else if (pOnT == 1)
        out << " " << pOnTNum[0] << " ";
    else if (pOnT == 2)
        out << pOnTNum[0] << " " << pOnTNum[1];
    else if (pOnT == 3)
        out << pOnTNum[0] << pOnTNum[1] << pOnTNum[2];
    else
        out << "all";
    out<< RESET;
}

void Board::displayBoard(ostream& out)
{
    int segmentSize = 24;  // Adjust the size of each horizontal segment as needed
    int side = 2;
    int shift = 23;

    int lastRow = _BOARD_SIZE%29;
    for (int row = 0; row<_BOARD_SIZE/29; row++){
        side++;
        shift = (side%2 == 1 ? 23 : 0);
        for (int i = (side%2==1 ? 0 : segmentSize); (side%2==1 ? i < segmentSize : i > 0); (side%2==1 ? i++ : i--))
            displayTile(row*29 + i + (side%2==1 ? 0 : -1),out);      
        out << endl;
        for (int k = 0; k < 5; k++){
            for (int j = 0; j<=shift-1; j++){
                out << "   ";
            }
            displayTile(row*29 + 24 + k, out);
            out << endl;
        }
    }
    if (side%2 == 1){
        if (lastRow < 24){           
            for (int i = 0; i < 22-lastRow+1; i++){
                out << "   ";
            }
            out << ORANGE << "Castle" << RESET;
            for (int i = lastRow; i > 1; i--){
                displayTile(_BOARD_SIZE-lastRow+i-1,out);
            } 
        }
    }else{
        for (int i = 0; i < lastRow-1; i++){
            displayTile(_BOARD_SIZE-lastRow+i,out);
        }
        out << ORANGE << "Castle" << RESET;
    }
    out << endl;  
   
}

int Board::setPlayerPosition(int index, int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE-1)
    {
        int curPos = _player_positions[index];
        _player_positions[index] = new_position;
        Tile t = _tiles[new_position];
        if (t.tile_type != "regular tile"){
            istringstream iss((string)t.tile_type);
            string type;
            iss >> type;
            printf("Something is happening... you landed on a %s tile\n", type.c_str());
            if (type == "shortcut"){   
                printf("you were sent forward 4 spaces.\n");
                int extra;
                iss>>extra;
                _player_positions[index] = new_position+extra;
                return 1;
            }
            else if (type == "ice cream stop"){   
                return 2;
            }
            else if (type == "gumdrop forest"){   
                printf("you were sent back 4 spaces.\n");
                if (new_position < 4)
                    _player_positions[index] = 0;
                else{
                    _player_positions[index] = new_position-4;
                }
                return 3;   
            }
            else if (type == "gingerbread house"){   
                printf("you were sent back to your old position.\n");
                _player_positions[index] = curPos;
                return 4;       
            }
            else if (type == "treasure"){   
                printf("you landed on a treasure.\n");
                return 5;       
            }
        }
        _player_positions[index] = new_position;
        return 1;    
    }
    _player_positions[index] = _BOARD_SIZE-1;
    return 0;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount()
{
    return _candy_store_count;
}

int Board::getPlayerPosition(int index)
{
    return _player_positions[index];
}
vector<int> Board::getPlayerPositions()
{
    return _player_positions;
}

bool Board::addCandyStore(int position, string name, vector<Candy> inv)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_stores[_candy_store_count] = Store(inv,name);
    _candy_store_count++;
    return true;
}
void Board::visitCandyStore(int index, Player& player){
    _candy_stores[index].visitStore(player);
}

int Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if (_candy_store_position[i] == board_position)
        {
            return i;
        }
    }
    return -1;
}

bool Board::movePlayer(int index,int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player_positions[index];
    if (new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_positions[index] = new_player_position;
    return true;
}
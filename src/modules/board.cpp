#include "./../../include/board.h"

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
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

    _player_position = 0;
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    if (position == _player_position)
    {
        cout << "X";
    }
    else
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    int segmentSize = 24;  // Adjust the size of each horizontal segment as needed
    int side = 2;
    int shift = 23;

    int lastRow = _BOARD_SIZE%29;
    for (int row = 0; row<_BOARD_SIZE/29; row++){
        side++;
        shift = (side%2 == 1 ? 23 : 0);
        for (int i = (side%2==1 ? 0 : segmentSize); (side%2==1 ? i < segmentSize : i > 0); (side%2==1 ? i++ : i--))
            displayTile(row*29 + i + (side%2==1 ? 0 : -1));      
        cout << endl;
        for (int k = 0; k < 5; k++){
            for (int j = 0; j<=shift-1; j++){
                cout << "   ";
            }
            displayTile(row*29 + 24 + k);
            cout << endl;
        }
    }
    if (side%2 == 1){
        if (lastRow < 24){           
            for (int i = 0; i < 22-lastRow+1; i++){
                cout << "   ";
            }
            cout << ORANGE << "Castle" << RESET;
            for (int i = lastRow; i > 1; i--){
                displayTile(_BOARD_SIZE-lastRow+i-1);
            } 
        }
    }else{
        for (int i = 0; i < lastRow-1; i++){
            displayTile(_BOARD_SIZE-lastRow+i);
        }
        cout << ORANGE << "Castle" << RESET;
    }
    cout << endl;  
   
}

bool Board::setPlayerPosition(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_position = new_position;
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayerPosition() const
{
    return _player_position;
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if (_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player_position;
    if (new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_position = new_player_position;
    return true;
}
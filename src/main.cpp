#include "./../include/board.h"
#include "./../include/player.h"
#include "./../include/store.h"
#include "./../include/riddle.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <filesystem>

namespace fs = filesystem;
using namespace std;

struct Card
{
    string colour;
    int distance;
};

vector<Candy> getCandy(string file_name, vector<Candy> candies);
void getRiddles(string file_name, vector<Riddle> &riddles);
vector<Player> getPlayers(string file_name, vector<Player> players, vector<Candy> avalCandies);

string getOutFileName();
int getIntInput(string prompt);
string getStrInput(string prompt);
char getCharInput(string prompt);
bool takeTurn(vector<Player> &, int, Board &);

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<Candy> avalCandies;
    vector<Riddle> riddles;
    vector<Player> characters, players;

    int numPlayers = 0;
    string input, characterName, prompt;
    bool nameFound;

    // SET UP CODE
    getRiddles("./assets/riddles.txt", riddles);
    avalCandies = getCandy("assets/candy.txt", avalCandies);
    Store store = Store(avalCandies, "The Welcome Store");
    characters = getPlayers("./assets/characters.txt", characters, avalCandies);
    while (numPlayers < 1 || numPlayers > 4)
    {
        numPlayers = getIntInput("Welcome to the game of candylandy. Please enter the number of participants:(1-4)\n");
        cin.clear();
    }
    Board board = Board(numPlayers, avalCandies);

    for (int i = 0; i < numPlayers; i++)
    {
        prompt = "Enter Player " + to_string(i + 1) + " Name:\n";
        input = getStrInput(prompt);
        printf("Awesome! Here is a list of characters a player can choose from:\n");
        for (Player p : characters)
            p.printPlayer();
        while (true)
        {
            characterName = getStrInput("Select A Character:\n");
            nameFound = false;
            for (Player p : characters)
            {
                if (characterName == p.getName())
                {
                    nameFound = true;
                    p.setNickName(input);
                    players.push_back(p);
                    break;
                }
            }
            if (nameFound)
                break;
        }
        char visitStore = '_';
        string empty;
        while (visitStore != 'y' && visitStore != 'n')
        {
            printf("Do you want to visit the candy store? (y/n)\n");
            cin >> visitStore;
            getline(cin, empty);
        }
        if (visitStore == 'y')
        {
            store.visitStore(players[players.size() - 1]);
        }
        printf("__________________________________________________________________________\n\n\n");
    }

    // RUN GAME
    int i = numPlayers;
    printf("let the game begin...\n");
    board.displayBoard();
    string outFilePath = getOutFileName();
    ofstream outfile(outFilePath);
    int turnNo = 1;
    while (true)
    {
        if (takeTurn(players, (numPlayers > 1 ? i % numPlayers : 0), board))
            i++;
        else
            break;
        outfile << "--------------------------------------------------------------------------\n";
        outfile << "turn " << turnNo << ":\n"
                << endl;
        for (Player p : players)
            p.printPlayer(outfile);
        if (i % 2 == 0)
            turnNo++;
    }
    outfile << "game has ended\nfinal stats:\n\n";
    for (Player p : players)
        p.printPlayer(outfile);
    return 0;
}

string getOutFileName()
{
    const string path = "./logs";
    int maxFile = -1;
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            string filename = entry.path().filename().string();
            if (filename.substr(0, 4) == "game" && filename.substr(filename.size() - 4) == ".txt")
            {
                int fileNumber = stoi(filename.substr(4, filename.size() - 8));
                maxFile = max(maxFile, fileNumber);
            }
        }
    }
    return (path + "/" + "game" + to_string(maxFile + 1) + ".txt");
}
// INPUT HANDLE
int getIntInput(string prompt)
{
    printf("%s", prompt.c_str());
    int input;
    if (cin >> input)
    {
        return input;
    }
    else
    {
        cin.clear();
        cin.ignore();
        return getIntInput(prompt);
    }
}
string getStrInput(string prompt)
{
    cout << prompt;
    string input;
    getline(cin >> ws, input); // Use ws to discard leading whitespace
    return input;
}
char getCharInput(string prompt)
{
    printf("%s", prompt.c_str());
    char input;
    if (cin >> input)
    {
        cin.clear();
        return input;
    }
    else
    {
        cin.clear();
        cin.ignore();
        return getIntInput(prompt);
    }
}

// GAME MOVE ON
bool takeTurn(vector<Player> &players, int playerNum, Board &b)
{
    Player &player = players[playerNum];
    if (player.skipTurns < 0)
    {
        player.skipTurns += 1;
        printf("your turn was skipped, only %d more turns to go.\n", (-player.skipTurns));
        return true;
    }
    const string colours[] = {MAGENTA, GREEN, BLUE};
    const string colours_txt[] = {"Magenta", "Green", "Blue"};
    Card drawn;
    int cardNum;
    int input = 0;
    cin.clear();
    while (input != 1 && input != 2 && input != 3)
    {
        printf(
            "What would you like to do %s?\n"
            "1.) Draw a card\n"
            "2.) Use candy\n"
            "3.) Show stats\n",
            player.getNickName().c_str());
        input = getIntInput("");
    }
    if (input == 1)
    {
        // weighted 2/3 to 1/3 for 2x vs 1x movement cards
        cardNum = rand() % 100;
        if (cardNum < 66)
            cardNum = 1;
        else
            cardNum = 2;
        int index = rand() % 3;
        string colour = colours[index];
        drawn = {colour, cardNum};
        printf("You have drawn a %dx %s card.\n", cardNum, colours_txt[index].c_str());

        int curPos = b.getPlayerPosition(playerNum), newPos = curPos;
        string empty;
        for (int i = curPos + 1; i < curPos + 4; i++)
        {
            if (i % 3 == index)
            {
                newPos = i;
                break;
            }
        }
        if (cardNum == 2)
            newPos += 3;
        if (newPos >= b.getBoardSize())
        {
            newPos = b.getBoardSize();
        }
        vector<int> original_positions = b.getPlayerPositions();
        int resultOfSetPos = b.setPlayerPosition(playerNum, newPos);
        vector<int> new_positions = b.getPlayerPositions();
        for (int i = 0; i < (int)original_positions.size(); i++)
        {
            if (i == playerNum)
            {
                continue;
            }
            if (original_positions[i] == new_positions[playerNum])
            {
                double randGold = ((rand() % 25000) / 1000.00) + 5;
                printf(
                    "you landed on %s's tile\n"
                    "they have robbed you for %.2f gold\n",
                    players[i].getNickName().c_str(), randGold);
                player.setGold(player.getGold() - randGold);
                printf("%s has been moved back 1 tile.\n", players[i].getNickName().c_str());
                b.setPlayerPosition(i, b.getPlayerPosition(i) - 1);
            }
        }
        char drawAgain = 'a';
        if (resultOfSetPos == 0)
        {
            b.displayBoard();
            printf("%s has won! thank you for playing candy land.\n", player.getNickName().c_str());
            return false;
        }
        else if (resultOfSetPos == 2)
        {

            while (drawAgain != 'y' && drawAgain != 'n')
            {
                printf("would you like to draw another card? (y/n)\n");
                cin >> drawAgain;
                getline(cin, empty);
            }
            if (drawAgain == 'y')
                printf("ok finish this turn first then take another.\n");
        }
        else if (resultOfSetPos == 3)
        {
            player.setGold(player.getGold() - (rand() % 6 + 5));
        }
        else if (resultOfSetPos == 4)
        {
            if (player.removeCandyByType("immunity"))
            {
                printf("you lost an immunity candy.\n");
            }
        }
        b.displayBoard();
        int indexOfStore = b.isPositionCandyStore(newPos);
        if (indexOfStore != -1)
        {
            char visitStoreChar = 'a';

            while (visitStoreChar != 'y' && visitStoreChar != 'n')
            {
                printf("you have landed on a candy store. would you like to visit? (y/n)\n");
                cin >> visitStoreChar;
                getline(cin, empty);
            }
            if (visitStoreChar == 'y')
            {
                b.visitCandyStore(indexOfStore, player);
            }
        }
        if (drawAgain == 'y')
            return takeTurn(players, playerNum, b);
    }
    else if (input == 2)
    {
        for (Candy c : player.getUInventory())
        {
            printf("--------------------------------------------------\n");
            c.printCandy();
            printf("\n");
        }
        printf("--------------------------------------------------\n");
        string candyName = "";
        Candy candy = {"", "", "", 0, "", 0};
        printf("candy:\n");
        while (candy.name == "")
        {
            candyName = getStrInput("which candy would you like to use:\n");
            candy = player.findCandy(candyName);
        }
        printf("printing...\n");
        candy.printCandy();
        printf("getting target:\n");
        for (int i = 0; i < (int)players.size(); i++)
        {
            printf("%d : %s\n", i + 1, (i == playerNum ? "you" : players[i].getNickName().c_str()));
        }
        printf("got:\n");

        string useOnPrompt = "who would you like to use this on? (1-" + to_string((int)players.size()) + ")\n";
        int useOnP = 0;
        while (useOnP < 1 || useOnP > (int)players.size())
        {
            useOnP = getIntInput(useOnPrompt);
        }
        printf("set up target\n");
        Player &target = players[useOnP - 1];
        printf("candy target\n");
        target.useCandy(candy);
    }
    else
    {
        player.printPlayer();
    }
    return true;
}

// FILE READING
vector<Player> getPlayers(
    string file_name,
    vector<Player> players,
    vector<Candy> avalCandies)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        printf("Failed to open file\n");
        return players;
    }
    string line, name, stam, gold, candies, candy_name;
    getline(file, line);
    while (getline(file, line))
    {
        if (line.empty() || line.find_first_not_of(" \t\n\v\f\r") == string::npos)
        {
            continue;
        }
        istringstream iss(line);
        getline(iss, name, '|');
        getline(iss, stam, '|');
        getline(iss, gold, '|');
        getline(iss, candies);
        istringstream c(candies);
        vector<Candy> players_candies;
        while (getline(c, candy_name, ','))
        {
            for (Candy candy : avalCandies)
            {
                if (candy.name == candy_name)
                {
                    players_candies.push_back(candy);
                    break;
                }
            }
        }

        Player p = Player(name, stoi(stam), stod(gold), "", players_candies);
        players.push_back(p);
    }
    return players;
}

vector<Candy> getCandy(
    string file_name,
    vector<Candy> candies)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        printf("Failed to open file\n");
        return candies;
    }
    string line, name, desc, eType, eVal, cType, price;
    getline(file, line);
    // Name|Description|Effect type|Effect value|Candy type|Price
    while (getline(file, line))
    {
        if (line.empty() || line.find_first_not_of(" \t\n\v\f\r") == string::npos)
        {
            continue;
        }
        istringstream iss(line);
        getline(iss, name, '|');
        getline(iss, desc, '|');
        getline(iss, eType, '|');
        getline(iss, eVal, '|');
        getline(iss, cType, '|');
        getline(iss, price);
        candies.push_back({name, desc, eType, stoi(eVal), cType, stoi(price)});
    }
    return candies;
}
void getRiddles(string file_name, vector<Riddle> &riddles)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        printf("Failed to open file\n");
        return;
    }
    string line, answer;
    while (getline(file, line))
    {
        istringstream iss(line);
        getline(iss, line, '|');
        getline(iss, answer);
        riddles.push_back({line, answer});
    }
    printf("hello\n");
}
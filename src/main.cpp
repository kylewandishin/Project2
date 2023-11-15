#include "./../include/board.h"
#include "./../include/player.h"
#include "./../include/store.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

vector<Candy> getCandy(string file_name, vector<Candy> candies);
vector<Player> getPlayers(string file_name, vector<Player> players, vector<Candy> avalCandies);

int getIntInput(string prompt);
string getStrInput(string prompt);
char getCharInput(string prompt);

int main()
{
    vector<Candy> avalCandies;
    vector<Player> characters, players;
    Board board;
    int numPlayers;
    string input, characterName, prompt;
    bool nameFound;

    avalCandies = getCandy("assets/candy.txt", avalCandies); 
    Store store = Store(avalCandies);
    characters = getPlayers("./assets/characters.txt", characters, avalCandies);
    numPlayers = getIntInput("Welcome to the game of candylandy. Please enter the number of participants:\n");
    for (int i = 0; i < numPlayers; i++) {
        prompt = "Enter Player " + to_string(i+1) + " Name:\n";
        input = getStrInput(prompt);
        printf("Awesome! Here is a list of characters a player can choose from:\n");
        for (Player p : characters)
            p.printPlayer();
        while(true){
            characterName = getStrInput("Select A Character:\n");
            nameFound = false;
            for (Player p : characters){
                if (characterName==p.getName()){
                    nameFound = true;
                    players.push_back(p);
                    break;
                }
            }
            if (nameFound)
                break;
        }
    
        char visitStore = getCharInput("Do you want to visit the candy store? (y/n)\n");
        if (visitStore=='y' || visitStore=='Y'){
            store.visitStore(players[players.size() - 1]);
        }
        printf("__________________________________________________________________________\n\n\n");
    }

    board.displayBoard();
    return 0;
}
int getIntInput(string prompt){
    printf("%s",prompt.c_str());
    int input;
    if (cin >> input){
        return input;
    }else{
        cin.clear();
        cin.ignore();
        return getIntInput(prompt);
    }
}
string getStrInput(string prompt) {
    cout << prompt;
    string input;
    getline(cin >> ws, input); // Use ws to discard leading whitespace
    return input;
}
char getCharInput(string prompt){
    printf("%s",prompt.c_str());
    char input;
    if (cin >> input){
        cin.clear();
        return input;
    }else{
        cin.clear();
        cin.ignore();
        return getIntInput(prompt);
    }
}
vector<Player> getPlayers(
    string file_name,
    vector<Player> players,
    vector<Candy> avalCandies
)
{
    ifstream file(file_name);
    if (!file.is_open()){
        printf("Failed to open file\n");
        return players;
    }
    string line, name, stam, gold, candies, candy_name;
    getline(file,line);
    while(getline(file,line)){
        if (line.empty() || line.find_first_not_of(" \t\n\v\f\r") == string::npos) {
            continue;
        }
        istringstream iss(line);
        getline(iss,name,'|');
        getline(iss,stam,'|');
        getline(iss,gold,'|');
        getline(iss,candies);
        istringstream c(candies);
        vector<Candy> players_candies;
        while(getline(c, candy_name, ',')){
            for (Candy candy : avalCandies){
                if (candy.name == candy_name){
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
    vector<Candy> candies
)
{
    ifstream file(file_name);
    if (!file.is_open()){
        printf("Failed to open file\n");
        return candies;
    }
    string line, name, desc, eType, eVal,cType ,price;
    getline(file,line);
    //Name|Description|Effect type|Effect value|Candy type|Price
    while(getline(file,line)){
        if (line.empty() || line.find_first_not_of(" \t\n\v\f\r") == string::npos) {
            continue;
        }
        istringstream iss(line);
        getline(iss,name,'|');
        getline(iss,desc,'|');
        getline(iss,eType,'|');
        getline(iss,eVal,'|');
        getline(iss,cType,'|');
        getline(iss,price);
        candies.push_back({name,desc,eType,stoi(eVal),cType,stoi(price)});
    }
    return candies;
}
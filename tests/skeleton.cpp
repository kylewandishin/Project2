#include "../include/board.h"
#include "../include/candy.h"
#include "../include/colours.h"
#include "../include/player.h"
#include "../include/riddle.h"
#include "../include/store.h"
#include "../include/treasure.h"
#include <iostream>

using namespace std;
int main(){
    printf(ORANGE_FG "color test fg" RESET "\n");
    printf(ORANGE "color test bg" RESET "\n");
    Candy c1 = {
        "Jelly Bean of Vigor",
        "Using the Jellybean of Vigor, you can restore 50 units of stamina",
        "stamina",
        50,
        "magical",
        1001
    }, c2 = {
        "Treasure Hunter's Truffle",
        "This candy allows the player to unlock a hidden treasure",
        "skip",
        100,
        "skip",
        1001
    };
    Riddle r1 = {
        "Jelly Bean of Vigor",
        "1",
    }, r2 = {
        "Treasure Hunter's Truffle",
        "a",
    };
    c1.printCandy();
    Board b = Board(2, {c1,c2});
    b.displayBoard();
    Player p = Player("pooper", 99, 100.00, "", {c1,c2});
    p.printPlayer();
    Store s = Store({c1,c2}, "test store");
    s.visitStore(p);
    Treasure t = Treasure({r1,r2},{c1,c2});
    t.visitTreasure(p);

    return 0;
}
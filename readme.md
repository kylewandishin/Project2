# Project 2
## <span style="color:#C5595D; font-size;64px;">**Warning! if you do not use one of the provided compilation method. you must ensure you are putting the executable in a folder ("./anyFolder/executable"). if you do not do this the logs folder will be created and filled in the relative path "./../"**</span>

## Table of Contents

- [Compile](#Compile)
- [Run](#Run)
- [features](#Features)
- [Board](#board)
- [Candy](#candy)
- [Colors](#colors)
- [Player](#player)
- [Riddle](#riddle)
- [Store](#store)
- [Treasure](#treasure)

## Compile

compile.py is used as a helper file that will compile and run this project with all flags. please run it in the CandyLand folder.

```shell
python compile.py
```
can also be used with flags to run after compilation like this
```shell
python compile.py -r
```

makefile is used for comilation as well

```shell
make
```
or to compile and run ```only for Linux based os``` you can run

```shell
make run
```

cmake is also used for compilation

```shell
cmake .
make
```

<span style="color: #C5595D;" >!**Warning** this will erase the content for the makefile!</span>

all options will compile into `./build`

## Run

to run the executable, please run the command

```shell
./build/CandyLand
```

```add a .exe if needed```

## Features

this section discusses the untaught content i have used in this project.
a small demo can be found in ```./tests/smallDemo.cpp```

### printf

```cpp
printf("%s string | %d int | %.2f float with 2 decimals", "apple", 10, 15.64296284425)
```

will print `apple string | 10 int | 15.64 float with 2 decimals`

### turnary operators

turnary operators are shorthand if statements in the form
`( condition ? if true : else )`
for example

```cpp
printf("%s",(playRPS() ? "you won\n" : "you lost\n"));
```

this code block will wait for a bool response from playing rock paper scissors then if the game is won, will print you won, othersize it will print you lost

### pass by refrence

pass by refrence is a concept where instead of passing in an object and returning the altered object, you can return something else and alter the object directly. for example

```cpp
Player p = ...;
p = store.visitStore(p);

Player Store::visitStore(Player p){
    ...
    p.addCandy(...);
}
```

is the same as

```cpp
Player p = ...
store.visitStore(p);

void Store::visitStore(Player& p){
    ...
    p.addCandy(...);
}
```

## Board

The `Board` class controlls position of players and special tiles and is navigated by the takeTurn method in main.cpp

the board class has been significantly altared from its initial state given to us in recitation. the board relies on a vector of integers indicating the players positions at any given point and all movement is handled in Board.setPlayerPosition()

to display the board with all player positions a special format was created. because all tiles are the string `"   "` with the background color of the tile. we can show 1-4 players like this

```
" 3 "
"1 4"
"124"
"all"
```

## Candy

The `Candy` class is just a the same as the candy struct with the added feature of printcandy

## Colors

The `Colors` class defines the color palette used. this is done with a large series of color macros
this file has been altered to include extra escape sequences

## Player

The `Player` class handles player information and state at any given point. all other information is handled elsewhere

pretty similar to the Player class in homework 7, the inventory was changed to a vector and methods were added for activities such as using candies

## Riddle

contains the riddle, answer and a function to play the riddle

## Store

contains the inventory of the store, the name of the store and a function to visit the store

uses the function

```cpp
visitStore(Player& player)
```

which takes in a refrence to a player object so that candies can be added directly and gold can be altered

## Treasure

The `Treasure` class is similar to store just handling a way to play the treasure puzzles and recieve rewards.
and instead of buying candies a puzzle is played then a random event occurs

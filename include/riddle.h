#ifndef RIDDLE_H
#define RIDDLE_H

#include "player.h"
#include <iostream>

using namespace std;
class Riddle{
    public:
        std::string _riddle;
        std::string _answer;

        bool playRiddle(){
            string answer;
            printf("%s\n",_riddle.c_str());
            getline(cin >> ws, answer);
            bool isEqual = true;
            if (answer.size() == _answer.size()){
                for (int i = 0; i < (int)_answer.size(); i++){
                    if (tolower(answer[i]) != tolower(_answer[i])){
                        isEqual = false;
                        break;
                    }
                }
                if (isEqual){
                    return true;
                }
            }
            return false;
        }
};

#endif
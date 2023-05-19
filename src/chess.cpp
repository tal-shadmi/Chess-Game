#include "Game.hpp"
#include <stdlib.h>

int main(int argc, char* argv[]){
    // Create game instance and start a game
    // TODO: make Game a singelton
    // TODO: add a menu
    if (argv[1] != NULL){
        if (std::string(argv[1]) == "Game"){
            Game g;
            g.StartGame();
        }
        else if (std::string(argv[1]) == "Sheni"){
            Game g;
            g.FoolsMate();
        }
    }
    else{
        cout << "No valid option had been chosen.\nplease choose one of the following options: " << endl;
        cout << "1. Game" << endl;
    }
    return 0;
}
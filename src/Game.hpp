#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.hpp"

// Game class for managing a game of chess
class Game{
    private:
        // Enum for turn indication
        enum Turn {BLACK = 'B', WHITE = 'W'};
        // The board of the game
        Board board;
        // Player turn (Black's or White's)
        Turn turn;

        // Function to get a move from the user and check it's validity
        // The move should be in this form 'row number''column big letter'
        void GetMove();
        // Function to perform the move given by the user, if valid
        void PerformMove(std::string curr_position, std::string new_position);
        // Function to check the current status of the game: regular/check/checkmate 
        bool CheckGameStatus();
        // Function to switch turn of players in the game
        void SwitchTurn();
        
    public:
        Game();
        ~Game() = default;
        // Function to initiate the game of chess
        void StartGame();
};

#endif
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <windows.h>
using std::cout;
using std::endl;

#include "GamePiece.hpp"

#define BOARD_DIMENSION (8)
#define SQUARE_DIMENSION (5)
#define HORIZONTAL_SEPERATOR "="
#define VERTICAL_SEPERATOR "||"
#define SPACE " "

// #define BASE "__"
// #define STANDARD_BODY "[]"
// #define HORSE_BODY "[E"

class GamePiece;

// Board class for managing a board of chess
class Board{
    private:
        // Function to initiate initial game pieces placement on board
        void InitBoardPawns();
        // Function to initiate the board
        void InitBoard();
    public:
        // The actual game pieces array (which is basiclly the board)
        GamePiece* board[BOARD_DIMENSION][BOARD_DIMENSION];
        Board();
        ~Board();
        // Function for printing the board
        void PrintBoard();
};

#endif
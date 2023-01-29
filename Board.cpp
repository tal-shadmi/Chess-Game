#include "Board.hpp"

/*
* Implementation of private functions of class Board
*/

void Board::PrintBoard(){
    for (size_t row = 0; row < BOARD_DIMENSION; row++){
        for (size_t column = 0; column < BOARD_DIMENSION; column++){
            for (size_t i = 0; i < SQUARE_DIMENSION; i++){
                cout << "=";
            }
        }
        for (size_t i = 0; i < SQUARE_DIMENSION - 1; i++){
            cout << "\n";
        }
    }
}

void Board::InitBoardPawns(){
    for (size_t row = 0; row < BOARD_DIMENSION; row++){
        for (size_t column = 0; column < BOARD_DIMENSION; column++){
            //board[row][column]
        }
    }
    
}

void Board::InitBoard(){
    InitBoardPawns();
    PrintBoard();
}

/*
* Implementation of public functions of class Board
*/

Board::Board(){
    InitBoard();
}
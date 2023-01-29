#include <vector>
using std::vector;
#include <list>
using std::list;
#include <iostream>
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

class Board{
    private:
        /*
        * Private variables
        */
        GamePiece board[BOARD_DIMENSION][BOARD_DIMENSION];
        list<vector<unsigned int>> black_pawns_initial_positions = {{1,0}, {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}};
        list<vector<unsigned int>> black_rocks_initial_positions = {{0,0}, {0,7}};
        list<vector<unsigned int>> black_knights_initial_positions = {{0,1}, {0,6}};
        list<vector<unsigned int>> black_bishops_initial_positions = {{0,2}, {0,5}};
        list<vector<unsigned int>> black_queen_initial_positions = {{0,3}};
        list<vector<unsigned int>> black_king_initial_positions = {{0,4}};
        list<vector<unsigned int>> white_pawns_initial_positions = {{6,0}, {6,1}, {6,2}, {6,3}, {6,4}, {6,5}, {6,6}, {6,7}};
        list<vector<unsigned int>> white_rocks_initial_positions = {{7,0}, {7,7}};
        list<vector<unsigned int>> white_knights_initial_positions = {{7,1}, {7,6}};
        list<vector<unsigned int>> white_bishops_initial_positions = {{7,2}, {7,5}};
        list<vector<unsigned int>> white_queen_initial_positions = {{7,3}};
        list<vector<unsigned int>> white_king_initial_positions = {{7,4}};
        /*
        * Private functions
        */
        void InitBoardPawns();
        void PrintBoard();
        void InitBoard();
    public:
        Board();
};
#include "Board.hpp"

/*
* Implementation of private functions of class Board
*/

void Board::PrintBoard(){
    // Get a handle on std out for color managing in terminal printings
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Print the board
    cout << "Printing the board: \n\n";
    for (size_t row = 0; row < BOARD_DIMENSION; row++){
        // Printing the column indicators of a chess board
        if (row == 0){
            cout << "    A  B  C  D  E  F  G  H" << endl;
        }
        cout << SPACE << SPACE << "==========================" << endl;
        // cout << "\n";

        // Printing all the game pieces
        for (size_t column = 0; column < BOARD_DIMENSION * (SQUARE_DIMENSION - 1) + 1; column++){
            // Printing the row indicators of a chess board
            if (column == 0){
                cout << (BOARD_DIMENSION - row) << SPACE;
            }

            if (column % (SQUARE_DIMENSION - 1) == 0){
                cout << VERTICAL_SEPERATOR;
            }
            if ( ((column - 2) >= 0) && ((column - 2) % (SQUARE_DIMENSION - 1) == 0)){
                if (board[row][(column - 2) / (SQUARE_DIMENSION - 1)] != nullptr){
                    if (board[row][(column - 2) / (SQUARE_DIMENSION - 1)]->GetColor() == GamePiece::BLACK){
                        SetConsoleTextAttribute(hConsole, 1);
                        board[row][(column - 2) / (SQUARE_DIMENSION - 1)]->PrintSymbol();
                        SetConsoleTextAttribute(hConsole, 15);
                    }
                    if (board[row][(column - 2) / (SQUARE_DIMENSION - 1)]->GetColor() == GamePiece::WHITE){
                        SetConsoleTextAttribute(hConsole, 14);
                        board[row][(column - 2) / (SQUARE_DIMENSION - 1)]->PrintSymbol();
                        SetConsoleTextAttribute(hConsole, 15);
                    }
                }
                else cout << SPACE;
            }
        }
        cout << endl;
        if (row == BOARD_DIMENSION - 1){
            cout << SPACE << SPACE << "==========================" << endl;
        }
    }
}

void Board::InitBoardPawns(){
    cout << "Init board pawns\n";
    PiecePosition::Position p;
    for (size_t row = 0; row < BOARD_DIMENSION; row++){
        for (size_t column = 0; column < BOARD_DIMENSION; column++){
            // Place the black pawns
            if (row == 1){
                p.row = row;
                p.column = column;
                PiecePosition position(p);
                board[row][column] = new Pawn(position, GamePiece::Color::BLACK);
            }
            // Place the white pawns
            else if (row == 6){
                p.row = row;
                p.column = column;
                PiecePosition position(p);
                board[row][column] = new Pawn(position, GamePiece::Color::WHITE);
            }
            // Place the other black pieces
            else if (row == 0){
                if (column == 0 || column == 7){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new Rock(position, GamePiece::Color::BLACK);
                }
                else if (column == 1 || column == 6){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new Knight(position, GamePiece::Color::BLACK);
                }
                else if (column == 2 || column == 5){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new Bishop(position, GamePiece::Color::BLACK);
                }
                else if (column == 3){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new Queen(position, GamePiece::Color::BLACK);
                }
                else if (column == 4){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new King(position, GamePiece::Color::BLACK);
                }
            }
            // Place the other white pieces
            else if (row == 7){
                if (column == 0 || column == 7){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new Rock(position, GamePiece::Color::WHITE);
                }
                else if (column == 1 || column == 6){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new Knight(position, GamePiece::Color::WHITE);
                }
                else if (column == 2 || column == 5){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new Bishop(position, GamePiece::Color::WHITE);
                }
                else if (column == 3){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new Queen(position, GamePiece::Color::WHITE);
                }
                else if (column == 4){
                    p.row = row;
                    p.column = column;
                    PiecePosition position(p);
                    board[row][column] = new King(position, GamePiece::Color::WHITE);
                }
            }
            else board[row][column] = nullptr;
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

Board::~Board(){
    for (size_t row = 0; row < BOARD_DIMENSION; row++){
        delete[] board[row];
    }
}
#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include <iostream>
using std::cout;
using std::endl;

#include "PiecePosition.hpp"
#include "Board.hpp"

class Board;

// GamePiece class for managing a game piece in chess
class GamePiece{
    private:
        // Game piece position on board
        // TODO: unused at the moment - needs to understand if it can has any benefit
        PiecePosition position;
    protected:
        // Enum for game piece type
        enum Symbol {PAWN = 'P', ROCK = 'R', KNIGHT = 'N', BISHOP = 'B', QUEEN = 'Q', KING = 'K'};
        // Game piece type
        Symbol symbol;
    public:
        // Enum for game piece color
        enum Color {BLACK = 'B', WHITE = 'W'};
        // Game piece color
        Color color;
        GamePiece() = delete;
        GamePiece(const GamePiece&) = delete;
        GamePiece(PiecePosition position, Color color);
        ~GamePiece() = default;
        // Function to print the game piece type
        virtual void PrintSymbol();
        // Function to get the game piece type
        virtual char GetSymbol();
        // Function to determine if move a player wants to make with a game piece is legal or not
        virtual bool IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating) = 0;
        // Function to get the game piece color
        Color GetColor();
        // Function to get the game piece position
        PiecePosition GetPosition();
        // Function to set a game piece new position
        void SetPosition(PiecePosition new_position);
};

// Pawn class for managing a Pawn game piece in chess
class Pawn : public GamePiece{
    public:
        Pawn(PiecePosition position, Color color);
        Pawn(const Pawn&) = delete;
        ~Pawn() = default;
        virtual bool IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating);
};

// Rock class for managing a Rock game piece in chess
class Rock : public GamePiece{
    public:
        Rock(PiecePosition position, Color color);
        Rock(const Rock&) = delete;
        ~Rock() = default;
        virtual bool IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating);
};

// Knight class for managing a Knight game piece in chess
class Knight : public GamePiece{
    public:
        Knight(PiecePosition position, Color color);
        Knight(const Knight&) = delete;
        ~Knight() = default;
        virtual bool IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating);
};

// Bishop class for managing a Bishop game piece in chess
class Bishop : public GamePiece{
    public:
        Bishop(PiecePosition position, Color color);
        Bishop(const Bishop&) = delete;
        ~Bishop() = default;
        virtual bool IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating);
};

// Queen class for managing a Queen game piece in chess
class Queen : public GamePiece{
    public:
        Queen(PiecePosition position, Color color);
        Queen(const Queen&) = delete;
        ~Queen() = default;
        virtual bool IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating);
};

// King class for managing a King game piece in chess
class King : public GamePiece{
    public:
        King(PiecePosition position, Color color);
        King(const King&) = delete;
        ~King() = default;
        virtual bool IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating);
};

#endif
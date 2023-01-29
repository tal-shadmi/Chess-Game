#include <iostream>
using std::cout;
using std::endl;

#include "PawnPosition.hpp"

class GamePiece{
    private:
        enum Color {BLACK = 'B', WHITE = 'W'};
        PawnPosition position;
        Color color;
        // TODO: movement rules
    public:
        GamePiece() = delete;
        GamePiece(const GamePiece&) = delete;
        GamePiece(PawnPosition position, Color color);
        ~GamePiece() = default;
        void PrintSymbol();
};

class Pawn : public GamePiece{
    public:
        Pawn() = delete;
        Pawn(const Pawn&) = delete;
        ~Pawn() = default;
        void PrintSymbol();
};

class Rock : public GamePiece{
    public:
        Rock() = delete;
        Rock(const Rock&) = delete;
        ~Rock() = default;
        void PrintSymbol();
};

class Knight : public GamePiece{
    public:
        Knight() = delete;
        Knight(const Knight&) = delete;
        ~Knight() = default;
        void PrintSymbol();
};

class Bishop : public GamePiece{
    public:
        Bishop() = delete;
        Bishop(const Bishop&) = delete;
        ~Bishop() = default;
        void PrintSymbol();
};

class Queen : public GamePiece{
    public:
        Queen() = delete;
        Queen(const Queen&) = delete;
        ~Queen() = default;
        void PrintSymbol();
};

class King : public GamePiece{
    public:
        King() = delete;
        King(const King&) = delete;
        ~King() = default;
        void PrintSymbol();
};


#ifndef PIECEPOSITION_H
#define PIECEPOSITION_H

#include <vector>
using std::vector;

class PiecePosition{
    public:
        typedef struct Position{
            unsigned int row;
            unsigned char column;
        }Position;
        Position position;
        PiecePosition() = default;
        PiecePosition(Position position);
        ~PiecePosition() = default;
        void ChangePosition(Position new_position);
        Position GetPosition();
};

#endif
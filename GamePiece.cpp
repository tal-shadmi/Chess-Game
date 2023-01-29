#include "GamePiece.hpp"

GamePiece::GamePiece(PawnPosition position, Color color){
    this->position = position;
    this->color = color;
}

void Pawn::PrintSymbol(){
    cout << 'P';
}

void Rock::PrintSymbol(){
    cout << 'R';
}

void Knight::PrintSymbol(){
    cout << 'N';
}

void Bishop::PrintSymbol(){
    cout << 'B';
}

void Queen::PrintSymbol(){
    cout << 'Q';
}

void King::PrintSymbol(){
    cout << 'K';
}
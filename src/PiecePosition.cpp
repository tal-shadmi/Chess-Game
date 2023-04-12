#include "PiecePosition.hpp"

PiecePosition::PiecePosition(Position position){
    this->position = position;
}

void PiecePosition::ChangePosition(Position new_position){ 
    this->position = new_position;
}

PiecePosition::Position PiecePosition::GetPosition(){
    return this->position;
}
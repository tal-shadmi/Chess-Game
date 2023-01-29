#include "PawnPosition.hpp"

PawnPosition::PawnPosition(vector<vector<unsigned int>> position){
    this->position = position;
}

void PawnPosition::ChangePosition(vector<vector<unsigned int>> new_position){ 
    this->position = new_position;
}
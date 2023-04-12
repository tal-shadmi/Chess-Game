#include "GamePiece.hpp"

GamePiece::GamePiece(PiecePosition position, Color color){
    this->position = position;
    this->color = color;
}

void GamePiece::PrintSymbol(){
    cout << char(this->symbol);
}

char GamePiece::GetSymbol(){
    return char(this->symbol);
}

GamePiece::Color GamePiece::GetColor(){
    return this->color;
}

PiecePosition GamePiece::GetPosition(){
    return this->position;
}

void GamePiece::SetPosition(PiecePosition new_position){
    this->position = new_position;
    this->position.ChangePosition(new_position.GetPosition());
}

Pawn::Pawn(PiecePosition position, Color color):GamePiece(position, color){
    this->symbol = this->Symbol::PAWN;
}

bool Pawn::IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating){
    // Check if the move is legal for a Pawn
    // White Pawn case
    if (this->color == this->Color::WHITE){
        // In case eating other player game piece
        if (IsEating){
            if (int(new_position[0] - '0') != int(curr_position[0] - '0') + 1 ||
                (new_position[1] - curr_position[1] != 1 && new_position[1] - curr_position[1] != -1)){
                    return false;
                }
        }
        // In case not eating other player game piece
        else{
            if (curr_position[0] == '2' && int(new_position[0] - '0') == int(curr_position[0] - '0') + 2 && new_position[1] == curr_position[1] && board.board[5][curr_position[1] - 'A'] == nullptr){
                return true;
            }
            if (int(new_position[0] - '0') != int(curr_position[0] - '0') + 1 ||
                new_position[1] != curr_position[1]){
                    return false;
                }
        }
    }
    // Black Pawn case
    else if (this->color == this->Color::BLACK){
        // In case eating other player game piece
        if (IsEating){
            if (int(new_position[0] - '0') != int(curr_position[0] - '0') - 1 ||
                (new_position[1] - curr_position[1] != 1 && new_position[1] - curr_position[1] != -1)){
                    return false;
                }
        }
        // In case not eating other player game piece
        else{
            if (curr_position[0] == '7' && int(new_position[0] - '0') == int(curr_position[0] - '0') - 2 && new_position[1] == curr_position[1] && board.board[2][curr_position[1] - 'A'] == nullptr){
                return true;
            }
            if (int(new_position[0] - '0') != int(curr_position[0] - '0') - 1 ||
                new_position[1] != curr_position[1]){
                    return false;
                }
        }
    }
    return true;
}

Rock::Rock(PiecePosition position, Color color):GamePiece(position, color){
    this->symbol = this->Symbol::ROCK;
}

bool Rock::IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating){
    // Check if the move is legal for a Rock
    if (int(new_position[0] - '0') != int(curr_position[0] - '0') && new_position[1] != curr_position[1]){
            return false;
        }
    // Check for blockings if the move is on the same row
    if (int(new_position[0] - '0') == int(curr_position[0] - '0')){
        if (int(new_position[1] - 'A') - int(curr_position[1] - 'A') > 0){
            for (int i=int(curr_position[1] - 'A') + 1; i<int(new_position[1] - 'A'); i++){
                if (board.board[BOARD_DIMENSION - int(new_position[0] - '0')][i] != nullptr){
                    return false;
                }
            }
        }
        else if (int(new_position[1] - 'A') - int(curr_position[1] - 'A') < 0){
            for (int i=int(curr_position[1] - 'A') - 1; i>int(new_position[1] - 'A'); i--){
                if (board.board[BOARD_DIMENSION - int(new_position[0] - '0')][i] != nullptr){
                    return false;
                }
            }
        }
    }
    // Check for blockings if the move is on the same column
    else if (int(new_position[1] - 'A') == int(curr_position[1] - 'A')){
        if (int(new_position[0] - '0') - int(curr_position[0] - '0') > 0){
            for (int i=BOARD_DIMENSION - int(curr_position[0] - '0') - 1; i>BOARD_DIMENSION - int(new_position[0] - '0'); i--){
                if (board.board[i][int(new_position[1] - 'A')] != nullptr){
                    return false;
                }
            }
        }
        else if (int(new_position[0] - '0') - int(curr_position[0] - '0') < 0){
            for (int i=BOARD_DIMENSION - int(curr_position[0] - '0') + 1; i< BOARD_DIMENSION - int(new_position[0] - '0'); i++){
                if (board.board[i][int(new_position[1] - 'A')] != nullptr){
                    return false;
                }
            }
        }
    }
    return true;
}

Knight::Knight(PiecePosition position, Color color):GamePiece(position, color){
    this->symbol = this->Symbol::KNIGHT;
}

bool Knight::IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating){
    // Check if the move is legal for a Knight
    if (( (new_position[0] == curr_position[0] || int(new_position[0] - '0') == int(curr_position[0] -'0') + 2 || int(new_position[0] - '0') == int(curr_position[0] -'0') - 2) && (int(new_position[1] - 'A') == int(curr_position[1] -'A') + 1 || int(new_position[1] - 'A') == int(curr_position[1] -'A') - 1) ) ||
        ( (new_position[1] == curr_position[1] || int(new_position[1] - 'A') == int(curr_position[1] - 'A') + 2 || int(new_position[1] - 'A') == int(curr_position[1] - 'A') - 2) && (int(new_position[0] - '0') == int(curr_position[0] - '0') + 1 || int(new_position[0] - '0') == int(curr_position[0] - '0') - 1)) ){
            return true;
        }
    return false;
}

Bishop::Bishop(PiecePosition position, Color color):GamePiece(position, color){
    this->symbol = this->Symbol::BISHOP;
}

bool Bishop::IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating){
    // Check if the move is legal for a Bishop
    if (std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')) != std::abs(int(new_position[1]) - int(curr_position[1]))){
            return false;
        }
    // Check for blockings if the move is to higher row direction
    if (int(new_position[0] - '0') - int(curr_position[0] - '0') > 0){
        // Check for blockings if the move is to higher column direction
        if (int(new_position[1]) - int(curr_position[1]) > 0){
            for (int i=1; i<std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')); i++){
                if (board.board[BOARD_DIMENSION - int(curr_position[0] - '0') - i][int(curr_position[1] - 'A') + i] != nullptr){
                    return false;
                }
            }
        }
        // Check for blockings if the move is to lower column direction
        else if (int(new_position[1]) - int(curr_position[1]) < 0){
            for (int i=1; i<std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')); i++){
                if (board.board[BOARD_DIMENSION - int(curr_position[0] - '0') - i][int(curr_position[1] - 'A') - i] != nullptr){
                    return false;
                }
            }
        }
    }
    // Check for blockings if the move is to lower row direction
    else if (int(new_position[0] - '0') - int(curr_position[0] - '0') < 0){
        // Check for blockings if the move is to higher column direction
        if (int(new_position[1]) - int(curr_position[1]) > 0){
            for (int i=1; i<std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')); i++){
                if (board.board[BOARD_DIMENSION - int(curr_position[0] - '0') + i][int(curr_position[1] - 'A') + i] != nullptr){
                    return false;
                }
            }
        }
        // Check for blockings if the move is to lower column direction
        else if (int(new_position[1]) - int(curr_position[1]) < 0){
            for (int i=1; i<std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')); i++){
                if (board.board[BOARD_DIMENSION - int(curr_position[0] - '0') + i][int(curr_position[1] - 'A') - i] != nullptr){
                    return false;
                }
            }
        }
    }
    return true;
}

Queen::Queen(PiecePosition position, Color color):GamePiece(position, color){
    this->symbol = this->Symbol::QUEEN;
}

bool Queen::IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating){
    // Check if the move is legal for a Queen
    if ( (int(new_position[0] - '0') != int(curr_position[0] - '0') && new_position[1] != curr_position[1]) && (std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')) != std::abs(int(new_position[1]) - int(curr_position[1]))) ){
            return false;
        }
    // Checking for blockings the same way we did it for the Rock and the Bishop but combined
    // TODO: this code is repeting from the Rock and Bishop - put it in a function
    if (int(new_position[0] - '0') == int(curr_position[0] - '0')){
        if (int(new_position[1] - 'A') - int(curr_position[1] - 'A') > 0){
            for (int i=int(curr_position[1] - 'A') + 1; i<int(new_position[1] - 'A'); i++){
                if (board.board[BOARD_DIMENSION - int(new_position[0] - '0')][i] != nullptr){
                    return false;
                }
            }
        }
        else if (int(new_position[1] - 'A') - int(curr_position[1] - 'A') < 0){
            for (int i=int(curr_position[1] - 'A') - 1; i>int(new_position[1] - 'A'); i--){
                if (board.board[BOARD_DIMENSION - int(new_position[0] - '0')][i] != nullptr){
                    return false;
                }
            }
        }
    }
    else if (int(new_position[1] - 'A') == int(curr_position[1] - 'A')){
        if (int(new_position[0] - '0') - int(curr_position[0] - '0') > 0){
            for (int i=BOARD_DIMENSION - int(curr_position[0] - '0') - 1; i>BOARD_DIMENSION - int(new_position[0] - '0'); i--){
                if (board.board[i][int(new_position[1] - 'A')] != nullptr){
                    return false;
                }
            }
        }
        else if (int(new_position[0] - '0') - int(curr_position[0] - '0') < 0){
            for (int i=BOARD_DIMENSION - int(curr_position[0] - '0') + 1; i< BOARD_DIMENSION - int(new_position[0] - '0'); i++){
                if (board.board[i][int(new_position[1] - 'A')] != nullptr){
                    return false;
                }
            }
        }
    }
    else if (int(new_position[0] - '0') - int(curr_position[0] - '0') > 0){
        if (int(new_position[1]) - int(curr_position[1]) > 0){
            for (int i=1; i<std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')); i++){
                if (board.board[BOARD_DIMENSION - int(curr_position[0] - '0') - i][int(curr_position[1] - 'A') + i] != nullptr){
                    return false;
                }
            }
        }
        else if (int(new_position[1]) - int(curr_position[1]) < 0){
            for (int i=1; i<std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')); i++){
                if (board.board[BOARD_DIMENSION - int(curr_position[0] - '0') - i][int(curr_position[1] - 'A') - i] != nullptr){
                    return false;
                }
            }
        }
    }
    else if (int(new_position[0] - '0') - int(curr_position[0] - '0') < 0){
        if (int(new_position[1]) - int(curr_position[1]) > 0){
            for (int i=1; i<std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')); i++){
                if (board.board[BOARD_DIMENSION - int(curr_position[0] - '0') + i][int(curr_position[1] - 'A') + i] != nullptr){
                    return false;
                }
            }
        }
        else if (int(new_position[1]) - int(curr_position[1]) < 0){
            for (int i=1; i<std::abs(int(new_position[0] - '0') - int(curr_position[0] - '0')); i++){
                if (board.board[BOARD_DIMENSION - int(curr_position[0] - '0') + i][int(curr_position[1] - 'A') - i] != nullptr){
                    return false;
                }
            }
        }
    }
    return true;
}

King::King(PiecePosition position, Color color):GamePiece(position, color){
    this->symbol = this->Symbol::KING;
}

bool King::IsMoveLegal(Board &board, std::string curr_position, std::string new_position, bool IsEating){
    // Check if the move is legal for a King
    if ((new_position[0] != curr_position[0] && new_position[0] != curr_position[0] + 1 && new_position[0] != curr_position[0] - 1) ||
        (new_position[1] != curr_position[1] && new_position[1] != curr_position[1] + 1 && new_position[1] != curr_position[1] - 1) ){
            return false;
        }
    return true;
}
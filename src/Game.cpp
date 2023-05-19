#include "Game.hpp"

/*
* Implementation of public functions of class Board
*/

Game::Game(){
    // White always starts in chess
    turn = this->Turn::WHITE;
    check = false;
}

void Game::GetMove(){
    std::string curr_position;
    std::string new_position;
    GamePiece *game_piece = nullptr;

    // Get from the player the place of the game piece he wants to move and check validity of this choice
    // TODO: currently the mechanic is "you touch you go" meaning there is no option for changing a game piece after chosen. problematic in case there are no possible moves for this chosen game piece.
    cout << "Type position of your chosen game piece: \n";
    std::cin >> curr_position;
    while (curr_position.length() != 2 || int(curr_position[0] - '0') < 1 || int(curr_position[0] - '0') > 8 || curr_position[1] < 'A' || curr_position[1] > 'H' ||
            this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A'] == nullptr ||
            this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']->GetColor() != this->turn){
        cout << "Illegal position! Type position of your chosen game piece: \n";
        std::cin >> curr_position;
    }

    // Static cast to the correct game piece
    if (this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']->GetSymbol() == 'P'){
        game_piece = static_cast<Pawn*>(this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']);
    }
    if (this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']->GetSymbol() == 'R'){
        game_piece = static_cast<Rock*>(this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']);
    }
    if (this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']->GetSymbol() == 'N'){
        game_piece = static_cast<Knight*>(this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']);
    }
    if (this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']->GetSymbol() == 'B'){
        game_piece = static_cast<Bishop*>(this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']);
    }
    if (this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']->GetSymbol() == 'Q'){
        game_piece = static_cast<Queen*>(this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']);
    }
    if (this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']->GetSymbol() == 'K'){
        game_piece = static_cast<King*>(this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A']);
    }                                                                                
    
    // Get from the player the place to which he would like to move his game piece and check legality of this move
    cout << "Type new position of your chosen game piece: \n";
    std::cin >> new_position;
    while (new_position.length() != 2 || int(new_position[0] - '0') < 1 || int(new_position[0] - '0') > 8 || new_position[1] < 'A' || new_position[1] > 'H' ||
            (this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] != nullptr && this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A']->GetColor() == this->turn) ||
             (this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] != nullptr && !(game_piece->IsMoveLegal(this->board, curr_position, new_position, true))) ||
             (this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] == nullptr && !(game_piece->IsMoveLegal(this->board, curr_position, new_position, false))) ){
        cout << "Illegal new position! Type new position of your chosen game piece: \n";
        std::cin >> new_position;
    }

    // Perform chosen move
    GamePiece *save = nullptr;
    if (this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] != nullptr){
        save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
    }
    PerformMove(curr_position, new_position);
    // Check for check on black if the requested move is performed
    check = CheckForCheck(this->Turn::BLACK);
    if (check){
        if (this->turn == this->Turn::BLACK){
            PerformMove(new_position, curr_position);
            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
            GetMove();
        }
        else if (this->turn == this->Turn::WHITE){
            cout << "CHECK!" << endl;
            return;
        }
    }
    // Check for check on white if the requested move is performed
    check = CheckForCheck(this->Turn::WHITE);
    if (check){
        if (this->turn == this->Turn::WHITE){
            cout << "Your King will be under check! this move is not possible!" << endl;
            PerformMove(new_position, curr_position);
            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
            GetMove();
        }
        else if (this->turn == this->Turn::BLACK){
            cout << "CHECK!" << endl;
            return;
        }
    }
}

void Game::PerformMove(std::string curr_position, std::string new_position){
    GamePiece *save = this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A'];
    this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A'] = nullptr;
    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
}

bool Game::CheckForCheck(Game::Turn player){
    int king_row, king_column;
    bool found = false;
    // Find the king of the player
    for (king_row=0; king_row<BOARD_DIMENSION; king_row++){
        if (found) break;
        for (king_column=0; king_column<BOARD_DIMENSION; king_column++){
            if (this->board.board[king_row][king_column] != nullptr && this->board.board[king_row][king_column]->GetSymbol() == 'K' && char(this->board.board[king_row][king_column]->GetColor()) == player){
                found = true;
                break;
            }
        }
    }
    king_row -= 1;
    // Check for check on straight lines from the king
    for (unsigned int way=0; way<4; way++){
        for (int steps=1; steps<BOARD_DIMENSION; steps++){
            if (way == 0){
                // cout << "checking straight right line" << endl;
                if (king_column + steps < BOARD_DIMENSION){
                    if (this->board.board[king_row][king_column + steps] != nullptr){
                        if (this->board.board[king_row][king_column + steps]->GetColor() != player){
                            if (this->board.board[king_row][king_column + steps]->GetSymbol() == 'Q' || this->board.board[king_row][king_column + steps]->GetSymbol() == 'R'){
                                // cout << "check in a straight line from the right from game piece in " << king_row << " " << (king_column + steps) << endl;
                                return true;
                            }
                            else break;
                        }
                        else break;
                    }
                }
                else break;
            }
            if (way == 1){
                // cout << "checking straight left line" << endl;
                if (king_column - steps >= 0){
                    if (this->board.board[king_row][king_column - steps] != nullptr){
                        if (this->board.board[king_row][king_column - steps]->GetColor() != player){
                            if (this->board.board[king_row][king_column - steps]->GetSymbol() == 'Q' || this->board.board[king_row][king_column - steps]->GetSymbol() == 'R'){
                                // cout << "check in a straight line from the left from game piece in " << king_row << " " << (king_column - steps) << endl;
                                return true;
                            }
                            else break;
                        }
                        else break;
                    }
                }
                else break;
            }
            if (way == 2){
                // cout << "checking straight down line" << endl;
                if (king_row + steps < BOARD_DIMENSION){
                    if (this->board.board[king_row + steps][king_column] != nullptr){
                        if (this->board.board[king_row + steps][king_column]->GetColor() != player){
                            if (this->board.board[king_row + steps][king_column]->GetSymbol() == 'Q' || this->board.board[king_row + steps][king_column]->GetSymbol() == 'R'){
                                // cout << "check in a straight line from the down from game piece in " << (king_row + steps) << " " << king_column << endl;
                                return true;
                            }
                            else break;
                        }
                        else break;
                    }
                }
                else break;
            }
            if (way == 3){
                // cout << "checking straight up line" << endl;
                if (king_row - steps >= 0){
                    if (this->board.board[king_row - steps][king_column] != nullptr){
                        if (this->board.board[king_row - steps][king_column]->GetColor() != player){
                            if (this->board.board[king_row - steps][king_column]->GetSymbol() == 'Q' || this->board.board[king_row - steps][king_column]->GetSymbol() == 'R'){
                                // cout << "check in a straight line from the up from game piece in " << (king_row - steps) << " " << king_column << endl;
                                return true;
                            }
                            else break;
                        }
                        else break;
                    }
                }
                else break;
            }
        }
    }
    // Check for check on diagonal lines from the king
    for (unsigned int way=0; way<4; way++){
        for (int steps=1; steps<BOARD_DIMENSION; steps++){
            if (way == 0){
                // cout << "checking the right down diagonal" << endl;
                if (king_column + steps < BOARD_DIMENSION && king_row + steps < BOARD_DIMENSION){
                    if (this->board.board[king_row + steps][king_column + steps] != nullptr){
                        if (this->board.board[king_row + steps][king_column + steps]->GetColor() != player){
                            if (this->board.board[king_row + steps][king_column + steps]->GetSymbol() == 'Q' || this->board.board[king_row + steps][king_column + steps]->GetSymbol() == 'B'){
                                // cout << "check from the right down diagonal from game piece in " << (king_row + steps) << " " << (king_column + steps) << endl;
                                return true;
                            }
                            else if (this->board.board[king_row + steps][king_column + steps]->GetSymbol() == 'P' && steps == 1 && this->board.board[king_row + steps][king_column + steps]->GetColor() == this->Turn::BLACK){
                                // cout << "check from the right down diagonal from game piece in " << (king_row + steps) << " " << (king_column + steps) << endl;
                                return true;
                            }
                            else break;
                        }
                        else break;
                    }
                }
                else break;
            }
            if (way == 1){
                // cout << "checking the left down diagonal" << endl;
                if (king_column - steps >= 0 && king_row + steps < BOARD_DIMENSION){
                    if (this->board.board[king_row + steps][king_column - steps] != nullptr){
                        if (this->board.board[king_row + steps][king_column - steps]->GetColor() != player){
                            if (this->board.board[king_row + steps][king_column - steps]->GetSymbol() == 'Q' || this->board.board[king_row + steps][king_column - steps]->GetSymbol() == 'B'){
                                // cout << "check from the left down diagonal from game piece in " << (king_row + steps) << " " << (king_column - steps) << endl;
                                return true;
                            }
                            else if (this->board.board[king_row + steps][king_column - steps]->GetSymbol() == 'P' && steps == 1 && this->board.board[king_row + steps][king_column - steps]->GetColor() == this->Turn::BLACK){
                                // cout << "check from the left down diagonal from game piece in " << (king_row + steps) << " " << (king_column - steps) << endl;
                                return true;
                            }
                            else break;
                        }
                        else break;
                    }
                }
                else break;
            }
            if (way == 2){
                // cout << "checking the right up diagonal" << endl;
                if (king_column + steps < BOARD_DIMENSION && king_row - steps >= 0){
                    if (this->board.board[king_row - steps][king_column + steps] != nullptr){
                        if (this->board.board[king_row - steps][king_column + steps]->GetColor() != player){
                            if (this->board.board[king_row - steps][king_column + steps]->GetSymbol() == 'Q' || this->board.board[king_row - steps][king_column + steps]->GetSymbol() == 'B'){
                                // cout << "check from the right up diagonal from game piece in " << (king_row - steps) << " " << (king_column + steps) << endl;
                                return true;
                            }
                            else if (this->board.board[king_row - steps][king_column + steps]->GetSymbol() == 'P' && steps == 1 && this->board.board[king_row - steps][king_column + steps]->GetColor() == this->Turn::WHITE){
                                // cout << "check from the right up diagonal from game piece in " << (king_row - steps) << " " << (king_column + steps) << endl;
                                return true;
                            }
                            else break;
                        }
                        else break;
                    }
                }
                else break;
            }
            if (way == 3){
                // cout << "checking the left up diagonal" << endl;
                if (king_column - steps >= 0 && king_row - steps >= 0){
                    if (this->board.board[king_row - steps][king_column - steps] != nullptr){
                        if (this->board.board[king_row - steps][king_column - steps]->GetColor() != player){
                            if (this->board.board[king_row - steps][king_column - steps]->GetSymbol() == 'Q' || this->board.board[king_row - steps][king_column - steps]->GetSymbol() == 'B'){
                                // cout << "check from the left up diagonal from game piece in " << (king_row - steps) << " " << (king_column - steps) << endl;
                                return true;
                            }
                            else if (this->board.board[king_row - steps][king_column - steps]->GetSymbol() == 'P' && steps == 1 && this->board.board[king_row  - steps][king_column - steps]->GetColor() == this->Turn::WHITE){
                                // cout << "check from the left up diagonal from game piece in " << (king_row - steps) << " " << (king_column - steps) << endl;
                                return true;
                            }
                            else break;
                        }
                        else break;
                    }
                }
                else break;
            }
        }
    }
    return false;
}

// TODO: implement
bool Game::CheckIfCanPerventCheck(int row, int column){
    GamePiece *game_piece = nullptr;
    GamePiece *save = nullptr;
    std::string curr_position;
    curr_position.append(std::string(1, char('1' + BOARD_DIMENSION - row)));
    curr_position.append(std::string(1, char('A' + column)));
    std::string new_position;
    // In case the game piece is a pawn
    if (this->board.board[row][column]->GetSymbol() == 'P'){
        game_piece = static_cast<Pawn*>(this->board.board[row][column]);
        cout << "can pawn pervent check?" << endl;
        // In case white tries to block check
        if (this->turn == this->Turn::BLACK){
            // try one step forward
            if (row - 1 >= 0 && this->board.board[row-1][column] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - 1)));
                new_position.append(std::string(1, char('A' + column)));
                PerformMove(curr_position, new_position);
                if (!CheckForCheck(this->Turn::WHITE)){
                    PerformMove(new_position, curr_position);
                    return true;
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            // try two steps forward
            if (row - 2 >= 0 && this->board.board[row-2][column] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - 2)));
                new_position.append(std::string(1, char('A' + column)));
                if (game_piece->IsMoveLegal(this->board, curr_position, new_position, false)){
                    PerformMove(curr_position, new_position);
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                    PerformMove(new_position, curr_position);
                }
                new_position.clear();
            }
            // try and eat to the right
            if (row - 1 >= 0 && column + 1 < BOARD_DIMENSION && this->board.board[row-1][column+1] != nullptr && this->board.board[row+1][column+1]->GetColor() == this->Turn::BLACK){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - 1)));
                new_position.append(std::string(1, char('A' + column + 1)));
                if (game_piece->IsMoveLegal(this->board, curr_position, new_position, true)){
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                        return true;
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                }
                new_position.clear();
            }
            // try and eat to the left
            if (row - 1 >= 0 && column - 1 >= 0 && this->board.board[row-1][column-1] != nullptr && this->board.board[row+1][column+1]->GetColor() == this->Turn::BLACK){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - 1)));
                new_position.append(std::string(1, char('A' + column - 1)));
                if (game_piece->IsMoveLegal(this->board, curr_position, new_position, true)){
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                        return true;
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                }
                new_position.clear();
            }
            cout << "chcked if white pawn pervented check" << endl;
        }
        // In case black tries to block check
        else if (this->turn == this->Turn::WHITE){
            // try one step forward
            if (row + 1 < BOARD_DIMENSION && this->board.board[row+1][column] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + 1)));
                new_position.append(std::string(1, char('A' + column)));
                PerformMove(curr_position, new_position);
                if (!CheckForCheck(this->Turn::BLACK)){
                    PerformMove(new_position, curr_position);
                    return true;
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            // try two steps forward
            if (row + 2 < BOARD_DIMENSION && this->board.board[row+2][column] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + 2)));
                new_position.append(std::string(1, char('A' + column)));
                if (game_piece->IsMoveLegal(this->board, curr_position, new_position, false)){
                    PerformMove(curr_position, new_position);
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                    PerformMove(new_position, curr_position);
                }
                new_position.clear();
            }
            // try and eat to the right
            if (row + 1 < BOARD_DIMENSION && column + 1 < BOARD_DIMENSION && this->board.board[row+1][column+1] != nullptr && this->board.board[row+1][column+1]->GetColor() == this->Turn::BLACK){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + 1)));
                new_position.append(std::string(1, char('A' + column + 1)));
                if (game_piece->IsMoveLegal(this->board, curr_position, new_position, true)){
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                        return true;
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                }
                new_position.clear();
            }
            // try and eat to the left
            if (row + 1 < BOARD_DIMENSION && column - 1 < BOARD_DIMENSION && this->board.board[row+1][column-1] != nullptr && this->board.board[row+1][column+1]->GetColor() == this->Turn::BLACK){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + 1)));
                new_position.append(std::string(1, char('A' + column - 1)));
                if (game_piece->IsMoveLegal(this->board, curr_position, new_position, true)){
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                        return true;
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                }
                new_position.clear();
            }
            cout << "chcked if black pawn pervented check" << endl;
        }
        return false;
    }
    // In case the game piece is a rock
    else if (this->board.board[row][column]->GetSymbol() == 'R'){
        game_piece = static_cast<Rock*>(this->board.board[row][column]);
        cout << "can rock pervent check?" << endl;
        // Check all possible moves up the column
        for (int i=column + 1; i<BOARD_DIMENSION; i++){
            if (this->board.board[row][i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row)));
                new_position.append(std::string(1, char('A' + i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row][i] != nullptr){
                if (this->board.board[row][i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row)));
                    new_position.append(std::string(1, char('A' + i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by rock going up the column " << endl;
        // Check all possible moves down the column
        for (int i=column - 1; i>=0; i--){
            if (this->board.board[row][i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row)));
                new_position.append(std::string(1, char('A' + i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row][i] != nullptr){
                if (this->board.board[row][i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row)));
                    new_position.append(std::string(1, char('A' + i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by rock going down the column " << endl;
        // Check all possible moves up the row
        for (int i=row + 1; i<BOARD_DIMENSION; i++){
            if (this->board.board[i][column] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - i)));
                new_position.append(std::string(1, char('A' + column)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[i][column] != nullptr){
                if (this->board.board[i][column]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - i)));
                    new_position.append(std::string(1, char('A' + column)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by rock going up the row " << endl;
        // Check all possible moves down the row
        for (int i=row - 1; i>=0; i--){
            if (this->board.board[i][column] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - i)));
                new_position.append(std::string(1, char('A' + column)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[i][column] != nullptr){
                if (this->board.board[i][column]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - i)));
                    new_position.append(std::string(1, char('A' + column)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by rock going down the row " << endl;
        return false;
    }
    else if (this->board.board[row][column]->GetSymbol() == 'N'){
        game_piece = static_cast<Knight*>(this->board.board[row][column]);
        cout << "can knight pervent check?" << endl;
        // TODO
        // if (( (new_position[0] == curr_position[0] || int(new_position[0] - '0') == int(curr_position[0] -'0') + 2 || int(new_position[0] - '0') == int(curr_position[0] -'0') - 2) && (int(new_position[1] - 'A') == int(curr_position[1] -'A') + 1 || int(new_position[1] - 'A') == int(curr_position[1] -'A') - 1) ) ||
        // ( (new_position[1] == curr_position[1] || int(new_position[1] - 'A') == int(curr_position[1] - 'A') + 2 || int(new_position[1] - 'A') == int(curr_position[1] - 'A') - 2) && (int(new_position[0] - '0') == int(curr_position[0] - '0') + 1 || int(new_position[0] - '0') == int(curr_position[0] - '0') - 1)) ){
        //     return true;
        // }
        return false;
    }
    else if (this->board.board[row][column]->GetSymbol() == 'B'){
        game_piece = static_cast<Bishop*>(this->board.board[row][column]);
        cout << "can bishop pervent check?" << endl;
        // Check all possible moves to the down right diagonal
        for (int i=1; i<BOARD_DIMENSION; i++){
            if (row + i > BOARD_DIMENSION - 1 || column + i > BOARD_DIMENSION - 1){
                break;
            }
            if (this->board.board[row + i][column + i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                new_position.append(std::string(1, char('A' + column + i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row + i][column + i] != nullptr){
                if (this->board.board[row + i][column + i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                    new_position.append(std::string(1, char('A' + column + i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by bishop going down right diagonal " << endl;
        // Check all possible moves to the up left diagonal
        for (int i=1; i<BOARD_DIMENSION; i++){
            if (row - i < 0 || column - i < 0){
                break;
            }
            if (this->board.board[row - i][column - i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - i)));
                new_position.append(std::string(1, char('A' + column - i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row - i][column - i] != nullptr){
                if (this->board.board[row - i][column - i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - i)));
                    new_position.append(std::string(1, char('A' + column - i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by bishop going up left diagonal " << endl;
        // Check all possible moves to the up right diagonal
        for (int i=1; i<BOARD_DIMENSION; i++){
            if (row - i < 0 || column + i > BOARD_DIMENSION - 1){
                break;
            }
            if (this->board.board[row - i][column + i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - i)));
                new_position.append(std::string(1, char('A' + column + i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row - i][column + i] != nullptr){
                if (this->board.board[row - i][column + i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - i)));
                    new_position.append(std::string(1, char('A' + column + i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by bishop going up right diagonal " << endl;
        // Check all possible moves to the down left diagonal
        for (int i=1; i<BOARD_DIMENSION; i++){
            if (row + i > BOARD_DIMENSION - 1 || column - i < 0){
                break;
            }
            if (this->board.board[row + i][column - i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                new_position.append(std::string(1, char('A' + column - i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row + i][column - i] != nullptr){
                if (this->board.board[row + i][column - i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                    new_position.append(std::string(1, char('A' + column - i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by bishop going down left diagonal " << endl;
        return false;
    }
    else if (this->board.board[row][column]->GetSymbol() == 'Q'){
        game_piece = static_cast<Queen*>(this->board.board[row][column]);
        cout << "can queen pervent check?" << endl;
        // Check all possible moves up the column
        for (int i=column + 1; i<BOARD_DIMENSION; i++){
            if (this->board.board[row][i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row)));
                new_position.append(std::string(1, char('A' + i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row][i] != nullptr){
                if (this->board.board[row][i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row)));
                    new_position.append(std::string(1, char('A' + i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by queen going up the column " << endl;
        // Check all possible moves down the column
        for (int i=column - 1; i>=0; i--){
            if (this->board.board[row][i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row)));
                new_position.append(std::string(1, char('A' + i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row][i] != nullptr){
                if (this->board.board[row][i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row)));
                    new_position.append(std::string(1, char('A' + i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by queen going down the column " << endl;
        // Check all possible moves up the row
        for (int i=row + 1; i<BOARD_DIMENSION; i++){
            if (this->board.board[i][column] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - i)));
                new_position.append(std::string(1, char('A' + column)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[i][column] != nullptr){
                if (this->board.board[i][column]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - i)));
                    new_position.append(std::string(1, char('A' + column)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by queen going up the row " << endl;
        // Check all possible moves down the row
        for (int i=row - 1; i>=0; i--){
            if (this->board.board[i][column] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - i)));
                new_position.append(std::string(1, char('A' + column)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[i][column] != nullptr){
                if (this->board.board[i][column]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - i)));
                    new_position.append(std::string(1, char('A' + column)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by queen going down the row " << endl;
        // Check all possible moves to the down right diagonal
        for (int i=1; i<BOARD_DIMENSION; i++){
            if (row + i > BOARD_DIMENSION - 1 || column + i > BOARD_DIMENSION - 1){
                break;
            }
            if (this->board.board[row + i][column + i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                new_position.append(std::string(1, char('A' + column + i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row + i][column + i] != nullptr){
                if (this->board.board[row + i][column + i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                    new_position.append(std::string(1, char('A' + column + i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by queen going down right diagonal " << endl;
        // Check all possible moves to the up left diagonal
        for (int i=1; i<BOARD_DIMENSION; i++){
            if (row - i < 0 || column - i < 0){
                break;
            }
            if (this->board.board[row - i][column - i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - i)));
                new_position.append(std::string(1, char('A' + column - i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row - i][column - i] != nullptr){
                if (this->board.board[row - i][column - i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - i)));
                    new_position.append(std::string(1, char('A' + column - i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by queen going up left diagonal " << endl;
        // Check all possible moves to the up right diagonal
        for (int i=1; i<BOARD_DIMENSION; i++){
            if (row - i < 0 || column + i > BOARD_DIMENSION - 1){
                break;
            }
            if (this->board.board[row - i][column + i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - i)));
                new_position.append(std::string(1, char('A' + column + i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row - i][column + i] != nullptr){
                if (this->board.board[row - i][column + i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row - i)));
                    new_position.append(std::string(1, char('A' + column + i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by queen going up right diagonal " << endl;
        // Check all possible moves to the down left diagonal
        for (int i=1; i<BOARD_DIMENSION; i++){
            if (row + i > BOARD_DIMENSION - 1 || column - i < 0){
                break;
            }
            if (this->board.board[row + i][column - i] == nullptr){
                new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                new_position.append(std::string(1, char('A' + column - i)));
                PerformMove(curr_position, new_position);
                if (this->turn == this->Turn::BLACK){
                    if (!CheckForCheck(this->Turn::WHITE)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                else if (this->turn == this->Turn::WHITE){
                    if (!CheckForCheck(this->Turn::BLACK)){
                        PerformMove(new_position, curr_position);
                        return true;
                    }
                }
                PerformMove(new_position, curr_position);
                new_position.clear();
            }
            else if (this->board.board[row + i][column - i] != nullptr){
                if (this->board.board[row + i][column - i]->GetColor() == this->turn){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                    new_position.append(std::string(1, char('A' + column - i)));
                    save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                    new_position.clear();
                    break;
                }
                break;
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by queen going down left diagonal " << endl;
        return false;
    }
    else if (this->board.board[row][column]->GetSymbol() == 'K'){
        game_piece = static_cast<King*>(this->board.board[row][column]);
        cout << "can king pervent check?" << endl;
        for (int i=-1; i<=1; i++){
            for (int j=-1; j<=1; j++){
                if ( (i == 0 && j == 0) || row + i < 0 || row + i > BOARD_DIMENSION - 1 || column + j < 0 || column + j > BOARD_DIMENSION - 1 ){
                    continue;
                }
                if (this->board.board[row + i][column + j] == nullptr){
                    new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                    new_position.append(std::string(1, char('A' + column + j)));
                    PerformMove(curr_position, new_position);
                    if (this->turn == this->Turn::BLACK){
                        if (!CheckForCheck(this->Turn::WHITE)){
                            PerformMove(new_position, curr_position);
                            return true;
                        }
                    }
                    else if (this->turn == this->Turn::WHITE){
                        if (!CheckForCheck(this->Turn::BLACK)){
                            PerformMove(new_position, curr_position);
                            return true;
                        }
                    }
                    PerformMove(new_position, curr_position);
                    new_position.clear();
                }
                else if (this->board.board[row + i][column + j] != nullptr){
                    if (this->board.board[row + i][column + j]->GetColor() == this->turn){
                        new_position.append(std::string(1, char('1' + BOARD_DIMENSION - row + i)));
                        new_position.append(std::string(1, char('A' + column + j)));
                        save = this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'];
                        PerformMove(curr_position, new_position);
                        if (this->turn == this->Turn::BLACK){
                            if (!CheckForCheck(this->Turn::WHITE)){
                                PerformMove(new_position, curr_position);
                                this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                                return true;
                            }
                        }
                        else if (this->turn == this->Turn::WHITE){
                            if (!CheckForCheck(this->Turn::BLACK)){
                                PerformMove(new_position, curr_position);
                                this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                                return true;
                            }
                        }
                        PerformMove(new_position, curr_position);
                        this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
                        new_position.clear();
                        break;
                    }
                    break;
                }
            }
        }
        cout << "chcked if " << this->turn << " check can be pervented by king moving " << endl;
        return false;
    }
    else return false; 
}

// TODO: implement
bool Game::CheckIfGameEnded(){
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    for (int row=0; row<BOARD_DIMENSION; row++){
        cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
        for (int column=0; column<BOARD_DIMENSION; column++){
            // cout << row << " " << column << endl;
            if (this->board.board[row][column] != nullptr){
                cout << "***************************" << endl;
                if (this->board.board[row][column]->GetColor() != this->turn){
                    cout << "***************************" << endl;
                    if (CheckIfCanPerventCheck(row, column)){
                        cout << "***************************" << endl;
                        return false;
                    }
                }
            }
        }
    }
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    return true;
}

void Game::SwitchTurn(){
    if (this->turn == this->Turn::BLACK){
        this->turn = this->Turn::WHITE;
    }
    else if (this->turn == this->Turn::WHITE){
        this->turn = this->Turn::BLACK;
    }
}

void Game::StartGame(){
    cout << "\nNow it's WHITE's turn" << endl;
    // A loop to manage the turn system of the game
    while (1){
        // Get and perform move
        GetMove();
        // Check if checkmate has been accomplished by one of the players
        cout << check << endl;
        if (check){
            if (CheckIfGameEnded()){
                cout << "checkmate!\n";
                break;
            }
        }
        // Switch players turn
        SwitchTurn();
        // Announce current player
        if (this->turn == this->Turn::BLACK){
            cout << "\nNow it's BLACK's turn" << endl;
        }
        else if (this->turn == this->Turn::WHITE){
            cout << "\nNow it's WHITE's turn" << endl;
        }
        // Print current board
        this->board.PrintBoard();
    }
    if (this->turn == this->Turn::BLACK){
        cout << "\nGAME OVER! BLACK WINS :)\n";
    }
    else if (this->turn == this->Turn::WHITE){
        cout << "\nGAME OVER! WHITE WINS :)\n";
    }
}

void Game::FoolsMate(){
    cout << "\nLET'S PLAY :)\n";
    cout << "\nLet me show you something ;)\n";
    Sleep(3000);
    cout << "\nNow it's WHITE's turn" << endl;
    PerformMove("2E", "4E");
    this->board.PrintBoard();
    SwitchTurn();
    cout << "\nNow it's BLACK's turn" << endl;
    Sleep(3000);
    PerformMove("7E", "5E");
    this->board.PrintBoard();
    SwitchTurn();
    cout << "\nNow it's WHITE's turn" << endl;
    Sleep(3000);
    PerformMove("1D", "5H");
    this->board.PrintBoard();
    SwitchTurn();
    cout << "\nNow it's BLACK's turn" << endl;
    Sleep(3000);
    PerformMove("8B", "6C");
    this->board.PrintBoard();
    SwitchTurn();
    cout << "\nNow it's WHITE's turn" << endl;
    Sleep(3000);
    PerformMove("1F", "4C");
    this->board.PrintBoard();
    SwitchTurn();
    cout << "\nNow it's BLACK's turn" << endl;
    Sleep(3000);
    PerformMove("8G", "6F");
    this->board.PrintBoard();
    SwitchTurn();
    cout << "\nNow it's WHITE's turn" << endl;
    Sleep(3000);
    PerformMove("5H", "7F");
    this->board.PrintBoard();
    SwitchTurn();
    Sleep(3000);
    cout << "\nGAME OVER! WHITE WINS :)\n";
    cout << "\nThat's how Fool's mate is done ;)\n";
    Sleep(3000);
    system("type ..\\banner_150.txt");
}
#include "Game.hpp"

/*
* Implementation of public functions of class Board
*/

Game::Game(){
    // White always starts in chess
    turn = this->Turn::WHITE;
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
    PerformMove(curr_position, new_position);
}

void Game::PerformMove(std::string curr_position, std::string new_position){
    GamePiece *save = this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A'];
    this->board.board[BOARD_DIMENSION - int(curr_position[0] - '0')][curr_position[1] - 'A'] = nullptr;
    this->board.board[BOARD_DIMENSION - int(new_position[0] - '0')][new_position[1] - 'A'] = save;
}

// TODO: implement
bool Game::CheckGameStatus(){
    return false;
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
    bool legal_move = true;
    bool game_over = false;
    cout << "\nNow it's WHITE's turn" << endl;
    // A loop to manage the turn system of the game
    while (1){
        // Get and perform move
        GetMove();
        // Check current game status
        game_over = CheckGameStatus();
        if (game_over){
            cout << "checkmate!\n";
            continue;
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
}
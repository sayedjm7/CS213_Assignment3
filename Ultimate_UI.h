#ifndef ULTIMATE_UI_H
#define ULTIMATE_UI_H

#include "BoardGame_Classes.h"
#include "Ultimate_Tic_Tac_Toe.h"

class Ultimate_UI : public UI<char> {
private:
    Ultimate_Board* ultimateBoard;

public:

    Ultimate_UI();

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    void display_board_matrix(const vector<vector<char>> &matrix) const;

    void display_welcome_message() override;

    void set_ultimate_board(Ultimate_Board* board) { ultimateBoard = board; }

private:
    Move<char>* get_human_move(Player<char>* player);
    Move<char>* get_computer_move(Player<char>* player);

    pair<int, int> get_big_board_coords(Player<char>* player);
    pair<int, int> get_small_board_coords(int bigRow, int bigCol, Player<char>* player);
    void display_small_board(int bigRow, int bigCol) const;
};

#endif
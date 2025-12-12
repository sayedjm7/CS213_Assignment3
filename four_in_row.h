//
// Created by dell on 03/12/2025.
//

#ifndef CS213_ASSIGNMENT3_2_FOUR_IN_ROW_H
#define CS213_ASSIGNMENT3_2_FOUR_IN_ROW_H
#include "BoardGame_Classes.h"

class four_in_row_board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    four_in_row_board();
    bool update_board(Move<char>* move) override;

    Player<char> *player{};
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class four_in_row_ui : public UI<char> {
public:
    four_in_row_ui();
    void display_welcome_message() override;
    Player<char> *create_player(string &name, char symbol, PlayerType type) override;
    Move<char> *get_move(Player<char> *player);
    Player<char>** setup_players() override;
};

#endif //CS213_ASSIGNMENT3_2_FOUR_IN_ROW_H
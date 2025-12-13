#pragma once
#ifndef INVERSE_XO_CLASSES_H
#define INVERSE_XO_CLASSES_H

#include "XO_Classes.h"

class Inverse_XO_Board : public Board<char> {
private:
    char blank_symbol = '.';

    bool check_three(char sym) const;

public:
    Inverse_XO_Board();

    bool update_board(Move<char>* move) override;

    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;

    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};



class Inverse_XO_UI : public UI<char> {
public:
    Inverse_XO_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_welcome_message();
};

#endif
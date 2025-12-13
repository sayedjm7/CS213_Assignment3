#pragma once
#ifndef DIAMOND_XO_H
#define DIAMOND_XO_H
#include "BoardGame_Classes.h"
using namespace std;
class diamond_XO_Board : public Board<char> {
private:
    char blank_symbol = '.';

    //  bool check_three(char sym) const;

public:
    bool is_horizontal_four(char m);
    bool is_vertical_four(char m);
    bool is_three(char m);
    diamond_XO_Board();
    bool update_board(Move<char>* move) override;

    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};


class diamond_XO_UI : public UI<char> {
public:
    diamond_XO_UI();

    
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
      //template<typename T>
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
    void display_welcome_message();

};




//Diamond
#endif
#pragma once
#ifndef NUMERICAL_XO_H
#define NUMERICAL_XO_H

#include <vector>
#include "BoardGame_Classes.h"

using namespace std;
class Numaric_XO_UI : public UI<int> {
public:
    Numaric_XO_UI();
    Player<int>* create_player(string& name, int symbol, PlayerType type)override;
    Move<int>* get_move(Player<int>* player) override;
    Player<int>** setup_players() override;
    void display_message(string m) ;

    void display_welcome_message();
    
};
class Numaric_XO_Board : public Board<int> {
private:
    bool check_three() const ;

public:
    Numaric_XO_Board();

    bool update_board(Move<int>* move)override;

    bool is_win(Player<int>* player)override;
    bool is_lose(Player<int>* player)override ;
    bool is_draw(Player<int>* player)override;
    bool game_is_over(Player<int>* player) override;

    bool is_there(const vector<int>& nums, int value);

};
#endif







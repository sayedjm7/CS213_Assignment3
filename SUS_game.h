//
// Created by dell on 22/11/2025.
//

#ifndef CS213_ASSIGNMENT3_SUS_GAME_H
#define CS213_ASSIGNMENT3_SUS_GAME_H

#include "BoardGame_Classes.h"



class sus_game_board : public Board<char> {
private:
    char blank_symbol = '.';

public:

    int num = 0;
    int p1_score = 0;
    int p2_score = 0;
    sus_game_board();
    ~sus_game_board() override;
    bool update_board(Move<char>* move) override;
    Player<char> *player;
    void count_sus_number(int x, int y, char sym);

    bool is_win(Player<char>* player) override;


    bool is_lose(Player<char>*) override { return false; };


    bool is_draw(Player<char>* player);


    bool game_is_over(Player<char>* player) override{return false;};
};

// قبل:
// class SUS_UI : public UI<char>  , public sus_game_board{

// بعد:
class SUS_UI : public UI<char> {
private:
    int best_x = 0;
    int best_y = 0;


    sus_game_board* game_board_ptr = nullptr;


public:
    SUS_UI();
    ~SUS_UI() override {};
    void display_welcome_message() override;

    Move<char>* get_move(Player<char>* player) override;
    bool U_score_point();


    // setter لربط الـ UI بلوحة اللعبة الحقيقية
    void set_game_board(sus_game_board* gb) { game_board_ptr = gb; }

    Player<char> *create_player(string &name, char symbol, PlayerType type) override;
    Player<char>** setup_players() override;
};








#endif //CS213_ASSIGNMENT3_SUS_GAME_H

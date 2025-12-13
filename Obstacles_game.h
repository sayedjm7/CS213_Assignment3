//
// Created by dell on 25/11/2025.
//

#ifndef CS213_ASSIGNMENT3_1_OBSTACLES_GAME_H
#define CS213_ASSIGNMENT3_1_OBSTACLES_GAME_H

#include "BoardGame_Classes.h"
class obstacle_ui : public UI<char> {
public:
    obstacle_ui();

    ~obstacle_ui() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);

    void display_welcome_message();

};

class obstacle_board : public Board<char>{
private:
    char blank_symbol = '.';


public:
    obstacle_board();

    bool update_board(Move<char>* move);
    bool is_valid_move(int ox, int oy, int nx, int ny,PlayerType p) ;

    bool is_win(Player<char>* player);


    bool is_lose(Player<char>*) { return false; };


    bool is_draw(Player<char>* player);


    bool game_is_over(Player<char>* player);
};

#endif //CS213_ASSIGNMENT3_1_OBSTACLES_GAME_H
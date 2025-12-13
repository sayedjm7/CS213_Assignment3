
#ifndef MEMORY_TIC_TAC_TOE_H
#define MEMORY_TIC_TAC_TOE_H


#include "BoardGame_Classes.h"
using namespace std;


class memory_ui : public UI<char> {
public:




    memory_ui();


    ~memory_ui() override {};


    Player<char>* create_player(string& name, char symbol, PlayerType type);

    void display_welcome_message();
    virtual Move<char>* get_move(Player<char>* player);
};


class memory_board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
    std::vector<vector<char>> real_board;




public:


    memory_board();


    bool update_board(Move<char>* move);
    bool is_valid_move(int ox, int oy, int nx, int ny,PlayerType p);

    bool is_win(Player<char>* player);


    bool is_lose(Player<char>*) { return false; };


    bool is_draw(Player<char>* player);


    bool game_is_over(Player<char>* player);
};



#endif

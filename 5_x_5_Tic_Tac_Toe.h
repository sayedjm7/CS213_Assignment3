#ifndef FIVEXFIVE_BOARD_H
#define FIVEXFIVE_BOARD_H
#include "BoardGame_Classes.h"

class Five__Five_Board : public Board<char> {


public:
    Five__Five_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    int CountOFSeq(char sym);
    void display_board();

private:
    int num_moves;
};

#endif
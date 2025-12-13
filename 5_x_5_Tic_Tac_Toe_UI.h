#ifndef FIVEXFIVE_UI_H
#define FIVEXFIVE_UI_H

#include "BoardGame_Classes.h"

class Five_And_Five_UI : public UI<char>
{
    public:

    Five_And_Five_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    void display_welcome_message() override;
};

#endif

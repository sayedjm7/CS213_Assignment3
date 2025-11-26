#ifndef WORDTICTACTOE_UI_H
#define WORDTICTACTOE_UI_H

#include "BoardGame_Classes.h"

class WordTicTacToe_UI : public UI<char> {
public:
    WordTicTacToe_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    void display_welcome_message() override;

};


#endif
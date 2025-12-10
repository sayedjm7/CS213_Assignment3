#ifndef WORDTICTACTOE_UI_H
#define WORDTICTACTOE_UI_H

#include "BoardGame_Classes.h"
#include "Word_Tic_Tac_Toe.h"
#include <set>
#include <vector>
#include <algorithm>

class Word_Tic_Tac_Toe_UI : public UI<char>
{

private:
    set<string> aiDictionary;
    vector<string> threeLetterWords;
    bool dictionaryLoaded;

    void loadAIDictionary();
    bool isValidWordAI(const string& word);
    bool canCompleteWordAI(const string& partial, char& missingChar, int missingPos);
    bool canWinNextMoveAI(Board<char>* board, char aiSymbol, int& winX, int& winY, char& winChar);
    bool getLettersThatCreateWords(Board<char>* board, char& result, int& x, int& y, char& blockChar);
    Move<char>* getAIMove(Player<char>* player);

public:
    Word_Tic_Tac_Toe_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    void display_welcome_message() override;
};

#endif
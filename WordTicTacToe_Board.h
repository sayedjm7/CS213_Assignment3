#ifndef WORDTICTACTOE_BOARD_H
#define WORDTICTACTOE_BOARD_H

#include "BoardGame_Classes.h"
#include <set>
#include <string>
#include <fstream>
#include <cctype>
#include <iostream>

class WordTicTacToe_Board : public Board<char> {
private:
    set<string> dictionary;
    string wordwin;

    void loadDictionary() {
        string paths[] = {
            "dic.txt",
            "../dic.txt",
            "../../dic.txt",
        };

        ifstream file;
        string usedPath;

        for (const auto& path : paths) {
            file.open(path);
            if (file.is_open()) {
                usedPath = path;
                cout << "    " << "|--------------------------------------|\n";

                cout << "    " << "|    File is opend: " << setw(19) << left << path << "|\n";
                break;
            }
        }

        if (!file.is_open()) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|    ERROR: Cannot open dictionary     |\n";
            cout << "    " << "|--------------------------------------|\n";


        }

        string word;
        int count = 0;
        while (file >> word) {
            for (char& c : word) c = toupper(c);
            dictionary.insert(word);
            count++;
        }
        cout << "    " << "|--------------------------------------|\n";
        cout << "    | File loaded " << count << " words from:" << usedPath << "|\n";
        cout << "    " << "|--------------------------------------|\n";

        file.close();
    }

    bool isValidWord(string word) {
        for (char& c : word) c = toupper(c);
        return dictionary.find(word) != dictionary.end();
    }

public:
    WordTicTacToe_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    string get_win_wotd() const{ return wordwin; }

};

#endif



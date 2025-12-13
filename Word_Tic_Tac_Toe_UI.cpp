#include "Word_Tic_Tac_Toe_UI.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <cctype>
#include <fstream>
#include <set>
#include <limits>
#include <sstream>

void Word_Tic_Tac_Toe_UI::display_welcome_message() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|          WORD TIC-TAC-TOE            |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|     Welcome to Word Challenge!       |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|              GAME RULES:             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Players: Place letters A-Z         |\n";
    cout << "    " << "| * Objective: Form valid 3-letter     |\n";
    cout << "    " << "|   words in any direction             |\n";
    cout << "    " << "| * Valid words from dictionary file   |\n";
    cout << "    " << "| * Win: First to form valid word      |\n";
    cout << "    " << "|   horizontally, vertically, or       |\n";
    cout << "    " << "|   diagonally                         |\n";
    cout << "    " << "| * Draw: Board full with no valid     |\n";
    cout << "    " << "|   words formed                       |\n";
    cout << "    " << "|--------------------------------------|\n\n";


}


Word_Tic_Tac_Toe_UI::Word_Tic_Tac_Toe_UI() : UI("", 3) {
    dictionaryLoaded = false;
    srand(time(0));
    display_welcome_message();
}

void Word_Tic_Tac_Toe_UI::loadAIDictionary() {
    if (dictionaryLoaded) return;

    string paths[] = {"dic.txt", "../dic.txt", "../../dic.txt"};
    ifstream file;

    for (const auto& path : paths) {
        file.open(path);
        if (file.is_open()) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "| AI Loading dictionary from: " << setw(10) << left << path << "|\n";
            break;
        }
    }

    if (!file.is_open()) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "| AI ERROR: Cannot open dictionary     |\n";
        cout << "    " << "|--------------------------------------|\n";
        return;
    }

    string word;
    int count = 0;
    while (file >> word) {
        for (char& c : word) c = toupper(c);
        aiDictionary.insert(word);
        if (word.length() == 3) {
            threeLetterWords.push_back(word);
        }
        count++;
    }

    cout << "    " << "| AI Loaded " << threeLetterWords.size() << "/" << count << " three-letter words |\n";
    cout << "    " << "|--------------------------------------|\n";

    file.close();
    dictionaryLoaded = true;
}

bool Word_Tic_Tac_Toe_UI::isValidWordAI(const string& word) {
    string upperWord = word;
    for (char& c : upperWord) c = toupper(c);
    return aiDictionary.find(upperWord) != aiDictionary.end();
}



bool Word_Tic_Tac_Toe_UI::canCompleteWordAI(const string& partial, char& missingChar, int missingPos) {
    for (char c = 'A'; c <= 'Z'; c++) {
        string testWord = partial;
        testWord.insert(missingPos, 1, c);
        if (isValidWordAI(testWord)) {
            missingChar = c;
            return true;
        }
    }
    return false;
}

bool Word_Tic_Tac_Toe_UI::canWinNextMoveAI(Board<char>* board, char aiSymbol, int& winX, int& winY, char& winChar) {
    vector<vector<char>> current = board->get_board_matrix();

    for (int i = 0; i < 3; i++) {
        int emptyCount = 0;
        int emptyPos = -1;
        string row = "";

        for (int j = 0; j < 3; j++)
        {
            if (current[i][j] == ' ')
            {
                emptyCount++;
                emptyPos = j;
            }
            else
                {
                row += current[i][j];
            }
        }

        if (emptyCount == 1) {
            char missing;
            if (canCompleteWordAI(row, missing, emptyPos)) {
                winX = i;
                winY = emptyPos;
                winChar = missing;
                return true;
            }
        }
    }

    for (int j = 0; j < 3; j++) {
        int emptyCount = 0;
        int emptyPos = -1;
        string col = "";

        for (int i = 0; i < 3; i++) {
            if (current[i][j] == ' ') {
                emptyCount++;
                emptyPos = i;
            } else {
                col += current[i][j];
            }
        }

        if (emptyCount == 1) {
            char missing;
            if (canCompleteWordAI(col, missing, emptyPos)) {
                winX = emptyPos;
                winY = j;
                winChar = missing;
                return true;
            }
        }
    }

    int emptyCount = 0;
    int emptyPos = -1;
    string diag1 = "";
    for (int i = 0; i < 3; i++) {
        if (current[i][i] == ' ') {
            emptyCount++;
            emptyPos = i;
        } else {
            diag1 += current[i][i];
        }
    }

    if (emptyCount == 1) {
        char missing;
        if (canCompleteWordAI(diag1, missing, emptyPos)) {
            winX = emptyPos;
            winY = emptyPos;
            winChar = missing;
            return true;
        }
    }

    emptyCount = 0;
    emptyPos = -1;
    string diag2 = "";
    for (int i = 0; i < 3; i++) {
        if (current[i][2-i] == ' ') {
            emptyCount++;
            emptyPos = i;
        } else {
            diag2 += current[i][2-i];
        }
    }

    if (emptyCount == 1) {
        char missing;
        if (canCompleteWordAI(diag2, missing, emptyPos)) {
            winX = emptyPos;
            winY = 2-emptyPos;
            winChar = missing;
            return true;
        }
    }

    return false;
}

bool Word_Tic_Tac_Toe_UI::getLettersThatCreateWords(Board<char>* board, char& result, int& x, int& y, char& blockChar) {
    do
    {
        // random nun
        x = rand() % 3;
        y = rand() % 3;
    }

    while (board->get_board_matrix()[x][y] != ' ');

    char letter = 'A' + (rand() % 26);

    result = letter;
    return true;
}



Move<char>* Word_Tic_Tac_Toe_UI::getAIMove(Player<char>* player)
{
    loadAIDictionary();

    Board<char>* boardPtr = player->get_board_ptr();
    vector<vector<char>> currentBoard = boardPtr->get_board_matrix();
    char aiSymbol = player->get_symbol();

    int winX, winY;
    char winChar;
    if (canWinNextMoveAI(boardPtr, aiSymbol, winX, winY, winChar))
    {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "| AI: Found WINNING move!              |\n";
        cout << "    " << "|--------------------------------------|\n";

        return new Move<char>(winX, winY, winChar);
    }


    int x = 0;
    int y = 0;
    char resultLetter = 'A';
    char blockCharDummy = 'A';

    if ( getLettersThatCreateWords(boardPtr, resultLetter, x, y, blockCharDummy)) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "| AI: Strategic move!                  |\n";
        cout << "    " << "|--------------------------------------|\n";
         return new Move<char>(x, y, resultLetter);
    }
}

Move<char>* Word_Tic_Tac_Toe_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::COMPUTER)
    {
        return getAIMove(player);
    }

    int x, y;
    string letter;

    Board<char>* game_board = player->get_board_ptr();
    vector<vector<char>> current_board = game_board->get_board_matrix();

    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|           " << player->get_name() << "'s TURN             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|     Enter position (row col 0-2):    |\n";

    bool num = false;
    while (!num) {
        if (!(cin >> x >> y)) {
            cout << "     | Pleas Enter Numbers (0 - 2)      |\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue ;
        }

        if (x < 0 || x > 2 || y < 0 || y > 2){
            cout << "    " << "|      Please enter numbers 0-2: ";
            cin.ignore(1000, '\n');
            continue;
        }

        if (current_board[x][y] != ' ') {
            cout << "    " << "|    Position occupied! Try again.  |\n";
            cin.ignore(1000, '\n');
            continue;
        }

        num = true;
    }

    cin.ignore(1000, '\n');

    cout << "    " << "|--------------------------------------|\n\n";

    cout << "    " << "| Enter letter (A-Z): ";
    cin >> letter;

    while( letter.length() != 1 ){
        cout << "    " << "|    Please enter exactly 1 character: ";
        cin >> letter;
    }

    while (!isalpha(letter[0])) {
        cout << "    " << "|    Please enter a letter (A-Z)!    |\n";
        cin >> letter;
    }
    cout << "    " << "|    Move: (" << x << "," << y << ") with '" << letter[0] << "'     |\n";
    cout << "    " << "|--------------------------------------|\n";

    return new Move<char>(x, y, toupper(letter[0]));
}
Player<char>* Word_Tic_Tac_Toe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
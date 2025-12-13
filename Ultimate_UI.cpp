#include "Ultimate_UI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Ultimate_UI::Ultimate_UI() : UI<char>("", 3) {
    srand(time(0));
    ultimateBoard = nullptr;
}

void Ultimate_UI::display_welcome_message() {
    cout << "\n    " << string(56, '=') << "\n";
    cout << "    |                 ULTIMATE TIC-TAC-TOE                 |\n";
    cout << "    " << string(56, '=') << "\n";
    cout << "    |                                                      |\n";
    cout << "    |                     GAME RULES                       |\n";
    cout << "    |                                                      |\n";
    cout << "    " << string(56, '-') << "\n";
    cout << "    |  1. Board Structure: 3x3 main grid                   |\n";
    cout << "    |     Each cell is a 3x3 Tic-Tac-Toe board             |\n";
    cout << "    " << string(56, '-') << "\n";
    cout << "    |  2. Movement Rules:                                  |\n";
    cout << "    |     Your move sends opponent to specific small board |\n";
    cout << "    |     The small cell you choose determines where       |\n";
    cout << "    |     your opponent plays next                         |\n";
    cout << "    " << string(56, '-') << "\n";
    cout << "    |  3. Winning Conditions:                              |\n";
    cout << "    |     Win a small board → Get 3 in a row             |\n";
    cout << "    |     Win the game → Win 3 big boards in a row       |\n";
    cout << "    " << string(56, '-') << "\n";
    cout << "    |  4. Coordinates Format: 0-8 (row and column)         |\n";
    cout << "    |     Example: 2,5 means row 2, column 5               |\n";
    cout << "    " << string(56, '=') << "\n\n";
}



Move<char>* Ultimate_UI::get_human_move(Player<char>* player) {
    cout << "\n                " << string(36, '=') << "\n";
    cout << "                |           " << player->get_name() << "'s TURN              |\n";
    cout << "                |            Symbol: (" << player->get_symbol() << ")           |\n";
    cout << "                " << string(36, '=') << "\n";

    if (ultimateBoard) {
        ultimateBoard->display_main_board();
    }

    cout << "                " << string(35, '-') << "\n";
    cout << "                |    SELECT BIG BOARD LOCATION    |\n";
    cout << "                " << string(35, '-') << "\n";

    auto bigCoords = get_big_board_coords(player);
    int bigRow = bigCoords.first;
    int bigCol = bigCoords.second;

    cout << "                |   Selected: Big Board (" << bigRow << "," << bigCol << ") |\n";
    cout << "                " << string(35, '-') << "\n";

    display_small_board(bigRow, bigCol);


    cout << "                " << string(35, '-') << "\n";
    cout << "                |    SELECT SMALL CELL LOCATION   |\n";
    cout << "                " << string(35, '-') << "\n";

    auto smallCoords = get_small_board_coords(bigRow, bigCol, player);
    int smallRow = smallCoords.first;
    int smallCol = smallCoords.second;

    int globalRow = bigRow * 3 + smallRow;
    int globalCol = bigCol * 3 + smallCol;

    cout << "\n           " << string(46, '=') << "\n";
    cout << "           |           MOVE CONFIRMED            |\n";
    cout << "           " << string(46, '=') << "\n";
    cout << "           |                                     |\n";
    cout << "           |    " << player->get_symbol() << " placed at (" << smallRow << "," << smallCol
         << ")          |\n";
    cout << "           |    In small board (" << bigRow << "," << bigCol << ")        |\n";
    cout << "           |                                     |\n";
    cout << "           |      Next player goes to board (" << smallRow << ","
         << smallCol << ")    |\n";
    cout << "           |                                     |\n";
    cout << "           " << string(46, '=') << "\n";

    return new Move<char>(globalRow, globalCol, player->get_symbol());
}

Move<char>* Ultimate_UI::get_computer_move(Player<char>* player) {
    if (!ultimateBoard) {
        return new Move<char>(rand() % 9, rand() % 9, player->get_symbol());
    }

    vector<pair<int, int>> validMoves;

    int forcedBigRow = -1, forcedBigCol = -1;

    if (ultimateBoard->get_is_next_board_forced()) {
        auto forcedBoard = ultimateBoard->get_next_board();
        forcedBigRow = forcedBoard.first;
        forcedBigCol = forcedBoard.second;
    }

    for (int br = 0; br < 3; br++) {
        for (int bc = 0; bc < 3; bc++) {
            if (forcedBigRow != -1 && forcedBigCol != -1) {
                if (br != forcedBigRow || bc != forcedBigCol) {
                    continue;
                }
            }

            if (ultimateBoard->is_small_board_available(br, bc)) {
                for (int sr = 0; sr < 3; sr++) {
                    for (int sc = 0; sc < 3; sc++) {
                        int globalRow = br * 3 + sr;
                        int globalCol = bc * 3 + sc;

                        if (ultimateBoard->is_cell_empty(globalRow, globalCol)) {
                            validMoves.push_back({globalRow, globalCol});
                        }
                    }
                }
            }
        }
    }



    if (validMoves.empty()) {
        return new Move<char>(-1, -1, player->get_symbol());
    }

    int idx = rand() % validMoves.size();
    int x = validMoves[idx].first;
    int y = validMoves[idx].second;



    int bigRow = x / 3;
    int bigCol = y / 3;
    int smallRow = x % 3;
    int smallCol = y % 3;

    cout << "\n                " << string(36, '=') << "\n";
    cout << "                |           " << player->get_name() << "'s TURN              |\n";
    cout << "                |            Symbol: (" << player->get_symbol() << ")           |\n";
    cout << "                " << string(36, '=') << "\n";



    if (ultimateBoard) {
        ultimateBoard->display_main_board();
    }

    if (forcedBigRow != -1 && forcedBigCol != -1)
    {
        cout << "           " << string(36, '-') << "\n";
        cout << "           |        FORCED MOVE DETECTED        |\n";
        cout << "           " << string(36, '-') << "\n";
        cout << "           |  AI must play in big board (" << forcedBigRow
             << "," << forcedBigCol << ") |\n";
        cout << "           " << string(36, '-') << "\n";
    }


    display_small_board(bigRow, bigCol);


    cout << "\n           " << string(46, '=') << "\n";
    cout << "           |           AI MOVE EXECUTED           |\n";
    cout << "           " << string(46, '=') << "\n";
    cout << "           |                                     |\n";
    cout << "           |    AI played at (" << smallRow << "," << smallCol
         << ")              |\n";
    cout << "           |    In small board (" << bigRow << "," << bigCol
         << ")            |\n";
    cout << "           |                                     |\n";

    if (ultimateBoard->is_small_board_available(smallRow, smallCol)) {
        cout << "           |    Next player goes to board (" << smallRow
                   << "," << smallCol << ")    |\n";    }
    else
    {
        cout << "           |      Next player: ANY available board |\n";
    }
    cout << "    " << string(60, '=') << "\n";







    return new Move<char>(x, y, player->get_symbol());

}

Move<char>* Ultimate_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        return get_human_move(player);
    } else {
        return get_computer_move(player);
    }
}


Player<char>* Ultimate_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

void Ultimate_UI::display_board_matrix(const vector<vector<char>>& matrix) const {}


pair<int, int> Ultimate_UI::get_small_board_coords(int bigRow, int bigCol, Player<char>* player) {
    int sr, sc;
    bool valid = false;

    do {
        cout << "           " << string(36, '-') << "\n";
        cout << "           |  ENTER SMALL BOARD COORDINATES  |\n";
        cout << "           " << string(36, '-') << "\n";
        cout << "           |  (Row and Column: 0-2)          |\n";
        cout << "           " << string(36, '-') << "\n";
        cout << "           Your choice: ";
        cin >> sr >> sc;

        if (sr < 0 || sr > 2 || sc < 0 || sc > 2) {
            cout << "\n    " << string(31, '-') << "\n";
            cout << "    |     INVALID COORDINATES!     |\n";
            cout << "    " << string(31, '-') << "\n";
            cout << "    |  Must be between 0 and 2     |\n";
            cout << "    " << string(31, '-') << "\n";
            continue;
        }

        int globalRow = bigRow * 3 + sr;
        int globalCol = bigCol * 3 + sc;

        if (!ultimateBoard->is_cell_empty(globalRow, globalCol)) {
            cout << "\n           " << string(31, '!') << "\n";
            cout << "           |     CELL ALREADY OCCUPIED!   |\n";
            cout << "           " << string(31, '!') << "\n";
            cout << "           |  Cell (" << sr << "," << sc << ") contains '"
                 << ultimateBoard->get_cell(globalRow, globalCol) << "'  |\n";
            cout << "           " << string(31, '!') << "\n";
            continue;
        }

        valid = true;

    } while (!valid);

    return {sr, sc};
}


void Ultimate_UI::display_small_board(int bigRow, int bigCol) const {
    if (!ultimateBoard) return;

    cout << "\n    Selected: Small Board (" << bigRow <<","<< bigCol << ")\n";
    cout << "    " << string(30, '=') << "\n";

    cout << "    |----|----|----|\n";
    for (int i = 0; i < 3; i++) {
        cout << "    | ";
        for (int j = 0; j < 3; j++) {
            int globalRow = bigRow * 3 + i;
            int globalCol = bigCol * 3 + j;
            char cell = ultimateBoard->get_cell(globalRow, globalCol);

            if (cell == ' ') {
                cout << i << j << " ";
            } else {
                cout << " " << cell << " ";
            }
            cout << "| ";
        }
        cout << "\n    |----|----|----|\n";
    }
}


pair<int, int> Ultimate_UI::get_big_board_coords(Player<char>* player) {
    int br, bc;

    if (ultimateBoard && ultimateBoard->get_is_next_board_forced()) {
        auto forcedBoard = ultimateBoard->get_next_board();
        br = forcedBoard.first;
        bc = forcedBoard.second;

        if (br != -1 && bc != -1) {
            if (ultimateBoard->is_small_board_available(br, bc)) {
                cout << "\n           " << string(46, '!') << "\n";
                cout << "           |          FORCED MOVE REQUIRED!         |\n";
                cout << "           " << string(46, '!') << "\n";
                cout << "           |  You MUST play in BIG BOARD (" << br
                     << "," << bc << ")      |\n";
                cout << "           |  (Opponent's previous move)            |\n";
                cout << "           " << string(46, '!') << "\n";
                return {br, bc};
            }


            cout << "\n           " << string(46, '~') << "\n";
            cout << "           |         FORCED BOARD COMPLETED!        |\n";
            cout << "           " << string(46, '~') << "\n";
            cout << "           |  Board (" << br << "," << bc << ") is finished.     |\n";
            cout << "           |  You can play in ANY active board      |\n";
            cout << "           " << string(46, '~') << "\n";

        }
    }

    bool valid = false;
    do {
        cout << "\n           " << string(36, '-') << "\n";
        cout << "           |    SELECT BIG BOARD (0-2, 0-2)    |\n";
        cout << "           " << string(36, '-') << "\n";
        cout << "           |  Look at the main board above     |\n";
        cout << "           |  Choose an ACTIVE big board       |\n";
        cout << "           " << string(36, '-') << "\n";
        cout << "           Your choice (row column): ";
        cin >> br >> bc;

        if (br < 0 || br > 2 || bc < 0 || bc > 2) {
            cout << "\n           " << string(31, '!') << "\n";
            cout << "           |     INVALID COORDINATES!     |\n";
            cout << "           " << string(31, '!') << "\n";
            cout << "    |  Must be between 0 and 2     |\n";
            cout << "    " << string(31, '!') << "\n";
            continue;
        }

        if (!ultimateBoard->is_small_board_available(br, bc)) {
            cout << "      Big board (" << br << "," << bc << ") is already completed!\n";
            cout << "    Look at the board - it's full of '"
                 << ultimateBoard->get_small_board_status(br, bc) << "'\n";
            continue;
        }

        valid = true;

    } while (!valid);

    return {br, bc};
}
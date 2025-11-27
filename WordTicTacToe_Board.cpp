#include "WordTicTacToe_Board.h"
#include <iostream>

WordTicTacToe_Board::WordTicTacToe_Board() : Board(3, 3) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    loadDictionary();
}

bool WordTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();

    if (board[x][y] == ' ')
        {
        board[x][y] = toupper(move->get_symbol());
        n_moves++;
        return true;
    }
    return false;
}

bool WordTicTacToe_Board::is_win(Player<char>* player) {
    wordwin = " " ;
    // Check rows
    for (int i = 0; i < 3; i++) {
        string row = string(1, board[i][0]) + board[i][1] + board[i][2];
        if (isValidWord(row)) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|              WORD FORMED!            |\n";
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|  Player: " << setw(26) << left << player->get_name() << "|\n";
            cout << "    " << "|  Collect Word:   " << setw(18) << left << row << "|\n";
            cout << "    " << "|--------------------------------------|\n";

            // cout << player ->get_name() << "  ---->  " << " collect word : " << row << endl;

            return true;
        }
    }


    // Check columns
    for (int j = 0; j < 3; j++) {
        string col = string(1, board[0][j]) + board[1][j] + board[2][j];
        if (isValidWord(col)) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|              WORD FORMED!            |\n";
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|  Player: " << setw(26) << left << player->get_name() << "|\n";
            cout << "    " << "|  Collect Word:   " << setw(18) << left << col << "|\n";
            cout << "    " << "|--------------------------------------|\n";

            // cout << player ->get_name() << "  ---->  " << " collect word : " << col  << endl;
            return true;
        }
    }

    // Check diagonals
    string diag1 = string(1, board[0][0]) + board[1][1] + board[2][2];
    string diag2 = string(1, board[0][2]) + board[1][1] + board[2][0];

    if (isValidWord(diag1)) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|              WORD FORMED!            |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|  Player: " << setw(26) << left << player->get_name() << "|\n";
        cout << "    " << "|  Collect Word:   " << setw(18) << left << diag1 << "|\n";
        cout << "    " << "|--------------------------------------|\n";

        // cout << player ->get_name() << "  ---->  " << " collect word : " << diag1  << endl;
        return true;

    }
    if (isValidWord(diag2)) {

        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|              WORD FORMED!            |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|  Player: " << setw(26) << left << player->get_name() << "|\n";
        cout << "    " << "|  Collect Word:   " << setw(18) << left << diag2 << "|\n";
        cout << "    " << "|--------------------------------------|\n";

        // cout << player ->get_name() << "  ---->  " << " collect word : " << diag2  << endl;
        return true;

    }

    return false;
}

bool WordTicTacToe_Board::is_lose(Player<char>* player) {
    return false;
}

bool WordTicTacToe_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool WordTicTacToe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
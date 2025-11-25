#include "Inverse_XO_Classes.h"
#include <cctype>
#include <iostream>
using namespace std;

//======================================================
//                 Board Implementation
//======================================================

Inverse_XO_Board::Inverse_XO_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

bool Inverse_XO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char m = toupper(move->get_symbol());

    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == blank_symbol) {
        board[x][y] = m;
        n_moves++;
        return true;
    }
    return false;
}

bool Inverse_XO_Board::check_three(char sym) const {
    // helper lambda
    auto eq = [&](char a, char b, char c) {
        return a == sym && b == sym && c == sym;
        };

    // rows + columns
    for (int i = 0; i < 3; i++) {
        if (eq(board[i][0], board[i][1], board[i][2])) return true;
        if (eq(board[0][i], board[1][i], board[2][i])) return true;
    }

    // diagonals
    if (eq(board[0][0], board[1][1], board[2][2])) return true;
    if (eq(board[0][2], board[1][1], board[2][0])) return true;

    return false;
}

bool Inverse_XO_Board::is_lose(Player<char>* player) {
    return check_three(player->get_symbol());
}

bool Inverse_XO_Board::is_win(Player<char>* player) {
    char other = (player->get_symbol() == 'X' ? 'O' : 'X');
    return check_three(other);
}

bool Inverse_XO_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_lose(player) && !is_win(player));
}

bool Inverse_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

//======================================================
//                     UI Implementation
//======================================================

Inverse_XO_UI::Inverse_XO_UI() : UI<char>("Inverse Tic-Tac-Toe Game", 3) {}

Player<char>* Inverse_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Inverse_XO_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n"<<"Please enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
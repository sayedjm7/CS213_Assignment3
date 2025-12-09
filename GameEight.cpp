#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "GameEight.h"

#include <math.h>
#include <queue>
using namespace std;

// -- Pry_Board

// constractor
Pry_Board::Pry_Board() : Board<char>(3,5) {
    this->board.clear();
    this->board.push_back(vector<char>(1, black_symbol));
    this->board.push_back(vector<char>(3, black_symbol));
    this->board.push_back(vector<char>(5, black_symbol));
}

// method the Board class

bool Pry_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_eq = [&](char a, char b, char c) {
        return (a == b && b == c && a != black_symbol);
    };

    for (int j = 1; j < 3; j++) {
        for (int i = 0; i + 2 <  board[j].size(); i++) {
            if (all_eq(board[j][i], board[j][i + 1], board[j][i + 2])) {
                return true;
            }
        }
    }

    if (all_eq(board[0][0], board[1][1], board[2][2]) ||
        all_eq(board[0][0], board[1][2], board[2][4]) ||
        all_eq(board[0][0], board[1][0], board[2][0]) ) {
        return true;
    }
    return false;
}

bool Pry_Board::is_draw(Player<char> *player) {
    return (n_moves == 9 && !is_win(player));
}

bool Pry_Board::update_board(Move<char> *move) {

    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (board[x][y] == black_symbol) {
        board[x][y] = sym;
        n_moves++;
        return true;
    }
    return false;
}

bool Pry_Board::game_is_over(Player<char>* player) {
    return is_draw(player) || is_win(player);
}

//------------------------------------------------------------------------


// -- Pry_UI
bool Pry_UI::will_win(Board<char>* board,int& bx,int& by,char h_sym) {
    vector<vector<char>> current_board = board->get_board_matrix();

    // 00
    if (((current_board[1][1] == h_sym && current_board[2][2] == h_sym) && current_board[0][0] == ' ') ||
        ((current_board[2][0] == h_sym && current_board[1][0] == h_sym) && current_board[0][0] == ' ') ||
        ((current_board[2][4] == h_sym && current_board[1][2] == h_sym) && current_board[0][0] == ' ')
            ) {
        bx = 0;
        by = 0;
        return true;
    }

    // 10
    if (((current_board[1][1] == h_sym && current_board[1][2] == h_sym) ||
        (current_board[0][0] == h_sym && current_board[2][0] == h_sym )) && current_board[1][0] == ' ' ) {
        bx = 1;
        by = 0;
        return true;
    }

    // 11
    if (((current_board[0][0] == h_sym && current_board[2][2] == h_sym)||
        (current_board[1][0] == h_sym && current_board[1][2] == h_sym)) && current_board[1][1] == ' ') {
        bx = 1;
        by = 1;
        return true;
    }

    // 12
    if (((current_board[0][0] == h_sym && current_board[2][4] == h_sym)||
        (current_board[1][0] == h_sym && current_board[1][1] == h_sym)) && current_board[1][2] == ' ') {
        bx = 1;
        by = 2;
        return true;
    }

    // 20
    if (((current_board[2][1] == h_sym && current_board[2][2] == h_sym ) ||
        (current_board[1][0] == h_sym && current_board[0][0] == h_sym)) && current_board[2][0] == ' ') {
        bx = 2;
        by = 0;
        return true;
    }

    // 24
    if (((current_board[2][3] == h_sym && current_board[2][2] == h_sym) ||
        (current_board[1][2] == h_sym && current_board[0][0] == h_sym))&& current_board[2][4] == ' ') {
        bx = 2;
        by = 4;
        return true;
    }

    // 21
    if (((current_board[2][0] == h_sym && current_board[2][2] == h_sym )||
        (current_board[2][2] == h_sym && current_board[2][3] == h_sym )) && current_board[2][1] == ' ') {
        bx = 2;
        by = 1;
        return true;
    }

    // 22
    if (((current_board[2][0] == h_sym && current_board[2][1] == h_sym )||
        (current_board[2][1] == h_sym && current_board[2][3] == h_sym ) ||
        (current_board[0][0] == h_sym && current_board[1][1] == h_sym )||
        (current_board[2][4] == h_sym && current_board[2][3] == h_sym ))&& current_board[2][2] == ' ') {
        bx = 2;
        by = 2;
        return true;
    }

    // 23
    if (((current_board[2][1] == h_sym && current_board[2][2] == h_sym )||
        (current_board[2][2] == h_sym && current_board[2][4] == h_sym ))&& current_board[2][3] == ' ') {
        bx = 2;
        by = 3;
        return true;
    }

    return false;
}

Pry_UI::Pry_UI() : UI<char>("",3) {
    display_welcome_message();
}

void Pry_UI::display_message(string message) {
    cout << "    |--------------------------------------|\n";
    cout << "    | " << setw(36) << left << message << " |\n";
    cout << "    |--------------------------------------|\n";}

void Pry_UI::display_board_matrix(const vector<vector<char> > &matrix) const  {
    int rows = matrix.size();


    if (matrix.empty()) return;

    cout << "\n           ";
    for (int i = 0; i < 5; i++) {
        cout << i << string(cell_width + 1, ' ') ;
    }
    cout << "\n";

    for (int i = 0 , inde = 10; i < rows; ++i, inde -= 5) {
        cout << string(inde + 7, ' ');
        cout << string((cell_width + 2) * 2 * (i + 1) , '-') << "\n";
        cout << string(inde + 7, ' ') << i << " | ";
        for (int j = 0; j < matrix[i].size(); ++j) {
            cout << setw(cell_width) << matrix[i][j] << "| ";
        }
        cout << "\n";
    }
    cout << "       ";
    cout << string((cell_width + 2) * 6, '-') << "\n\n";
}


Player<char>* Pry_UI::create_player(string &name, char symbol, PlayerType type) {
    cout << "    |--------------------------------------|\n";
    cout << "    | Creating " << (type == PlayerType::HUMAN ? "Human  " : "Computer") << " Player       |\n";
    cout << "    | Name: " << setw(28) << left << name << " |\n";
    cout << "    | Symbol: " << symbol << "                           |\n";
    cout << "    |--------------------------------------|\n";
    return new Player<char> (name,symbol,type);
}

Move<char>* Pry_UI::get_move(Player<char>* player) {
    int x, y;
    Board<char>* game_board = player->get_board_ptr();
    vector<vector<char>> current_board = game_board->get_board_matrix();

    // human move
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    |--------------------------------------|\n";
        cout << "    | " << player->get_name() << "'s Turn (" << player->get_symbol() << ")         |\n";
        cout << "    |--------------------------------------|\n";
        cout << "    | Enter your move (row col): ";
        cin >> x >> y;

        if (x == 0) {
            y -= 2;
        }
        if (x == 1) {
            y--;
        }
    start2:
        while (x < 0 || x > 2 || y < 0 || y > 4 || (x == 0 && (y < 0 || y > 0)) || (x == 1 && (y < 0 || y > 2))) {
            cout << "Invalid position.\nOut of shape\n";
            cout << "Please, enter position in the shape: ";
            cin  >> x >> y;

            if (x == 0) {
                y -= 2;
            }
            if (x == 1) {
                y--;
            }
            if (x >= 0 || x <= 2 || y >= 0 || y <= 4 ) goto start1;
        }
    start1:
        while (current_board[x][y] != ' ') {
            cout << "Invalid position.\n";
            cout << "Please, enter empty position: ";
            cin  >> x >> y;
            if (x == 0) {
                y -= 2;
            }
            if (x == 1) {
                y--;
            }
            if (x < 0 || x > 2 || y < 0 || y > 4 ) {goto start2;}
        }
        return new Move<char>(x, y, player->get_symbol());
    }

    // computer move
    else if (player->get_type() == PlayerType::COMPUTER) {

        cout << "    |--------------------------------------|\n";
        cout << "    | Computer's Turn (" << player->get_symbol() << ")                 |\n";
        cout << "    |--------------------------------------|\n";

        char computer_symbol = player->get_symbol();
        char other_symbol = (computer_symbol == 'X') ? 'O' : 'X';
        int best_x = 1, best_y = 2;

        // block algo
        if (will_win(game_board, best_x, best_y, computer_symbol)) {
            cout << "    | Computer Strategy: Winning Move      |\n";
            cout << "    |--------------------------------------|\n";
            return new Move<char>(best_x,  best_y, computer_symbol);
        }
        if (will_win(game_board, best_x, best_y, other_symbol)) {
            cout << "    | Computer Strategy: Blocking Move     |\n";
            cout << "    |--------------------------------------|\n";
            return new Move<char>(best_x,   best_y, computer_symbol);
        }
        best_x = 2, best_y = 2;
        cout << "    | Computer Strategy: Center Priority   |\n";
        cout << "    |--------------------------------------|\n";
        if (current_board[best_x][best_y] == ' ') {
            return new Move<char>(best_x, best_y, computer_symbol);
        }
        do {
            best_x = rand() % 3;
            best_y = rand() % 5;



        }
        while (current_board[best_x][best_y] != ' ' || (best_x == 0 && best_y != 0) || (best_x == 1 && best_y > 2));
        return new Move<char>(best_x, best_y, computer_symbol);
    }
}

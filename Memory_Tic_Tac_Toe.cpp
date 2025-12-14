//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include "BoardGame_Classes.h"
#include "Memory_Tic_Tac_Toe.h"


using namespace std;


memory_board::memory_board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    real_board = vector<vector<char>>(3, vector<char>(3, blank_symbol));

}
bool memory_board::is_valid_move(int ox, int oy, int nx, int ny,PlayerType p) {
    return true;
}

bool memory_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();


    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;


    if (real_board[x][y] != blank_symbol)
        return false;


    real_board[x][y] = mark;


    board[x][y] = '#';

    n_moves++;
    return true;
}

bool memory_board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };





    // // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(real_board[i][0], real_board[i][1], real_board[i][2]) && real_board[i][0] == sym) ||
            (all_equal(real_board[0][i], real_board[1][i], real_board[2][i]) && real_board[0][i] == sym))
            return true;
    }
    // Check diagonals
    if ((all_equal(real_board[0][0], real_board[1][1], real_board[2][2]) && real_board[1][1] == sym) ||
        (all_equal(real_board[0][2], real_board[1][1], real_board[2][0]) && real_board[1][1] == sym))
        return true;

    return false;
}
bool memory_board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool memory_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

memory_ui::memory_ui() : UI<char>("", 3) {
    display_welcome_message();

}
void memory_ui::display_welcome_message() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|          MEMORY TIC-TAC-TOE          |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|     Welcome to the Memory Challenge! |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|               GAME RULES:            |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Board: 3 x 3                       |\n";
    cout << "    " << "| * Players: X and O                   |\n";
    cout << "    " << "| * When you place a mark, it becomes  |\n";
    cout << "    " << "|   hidden immediately from the board. |\n";
    cout << "    " << "| * You must remember your hidden      |\n";
    cout << "    " << "|   marks' positions to plan your play.|\n";
    cout << "    " << "| * Winning: Align 3 of your hidden    |\n";
    cout << "    " << "|   marks in a row (row/col/diagonal). |\n";
    cout << "    " << "| * Draw: Board fills with no winner.  |\n";
    cout << "    " << "|--------------------------------------|\n\n";

}

Player<char>* memory_ui::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|             PLAYER CREATED           |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|  Type:    " << setw(25) << left
         << (type == PlayerType::HUMAN ? "Human" : "Computer") << "|\n";
    cout << "    " << "|  Name:    " << setw(25) << left << name << "|\n";
    cout << "    " << "|  Symbol:  " << setw(25) << left << symbol << "|\n";
    cout << "    " << "|--------------------------------------|\n";

    return new Player<char>(name, symbol, type);
}



Move<char>* memory_ui::get_move(Player<char>* player) {
    int x, y;
    Board<char>* game_board = player->get_board_ptr();
    const char sym = player->get_symbol();
    vector<vector<char>> current_board = game_board->get_board_matrix();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|              " << player->get_name() << "'s TURN             |\n";
        cout << "    " << "|               Symbol: " << player->get_symbol() << "              |\n";
        cout << "    " << "|--------------------------------------|\n";
        do {
            cout << "    " << "| Enter your move (row col 0-2): ";
            cin >> x >> y;

            if (x < 0 || x >= 3 || y < 0 || y >= 3) {
                cout << "    " << "|--------------------------------------|\n";
                cout << "    " << "|    Invalid: Out of bounds!           |\n";
                cout << "    " << "|--------------------------------------|\n";
            }
            else if (current_board[x][y] != '.') {
                cout << "    " << "|--------------------------------------|\n";
                cout << "    " << "|    Position occupied! Try again.     |\n";
                cout << "    " << "|--------------------------------------|\n";
            }
        } while (x < 0 || x >= 3 || y < 0 || y >= 3 || current_board[x][y] != '.');

        cout << "    " << "|    Move accepted: (" << x << "," << y << ")             |\n";
        cout << "    " << "|--------------------------------------|\n";
        // if (sym == 'X') {
        //     x_moves.push_back(make_pair(x, y));
        // }
        // else {
        //     o_moves.push_back(make_pair(x, y));
        // }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {

        do {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        }
        while (current_board[x][y] != '.');

    }
    return new Move<char>(x, y, player->get_symbol());
}
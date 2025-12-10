#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Diamond Tic-Tac-Toe.h"
#include<vector>

using namespace std;
vector<vector<int>>playable = { {0,0,1,0,0},{0,1,1,1,0},{1,1,1,1,1},{0,1,1,1,0},{0,0,1,0,0} };

diamond_XO_Board::diamond_XO_Board() : Board(5, 5) {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}
bool diamond_XO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char m = toupper(move->get_symbol());

    if (playable[x][y]) {

        playable[x][y] = 0;
        board[x][y] = m;
        n_moves++;
        return true;
    }
    return false;
}
bool diamond_XO_Board::is_horizontal_four(char m) {
    return (board[2][0] == m && board[2][1] == m && board[2][2] == m && board[2][3] == m) ||
        (board[2][1] == m && board[2][2] == m && board[2][3] == m && board[2][4] == m);
}

bool diamond_XO_Board::is_vertical_four(char m) {
    return (board[0][2] == m && board[1][2] == m && board[2][2] == m && board[3][2] == m) ||
        (board[1][2] == m && board[2][2] == m && board[3][2] == m && board[4][2] == m);
}
bool diamond_XO_Board::is_three(char m) {

    if (is_horizontal_four(m)) {

        for (int i = 1; i <= 3; i++) {
            if (board[1][i] == m && board[2][i] == m && board[3][i] == m)
                return true;

            if (i == 2) {
                if (board[0][2] == m && board[1][2] == m && board[2][2] == m)
                    return true;

                if (board[2][2] == m && board[3][2] == m && board[4][2] == m)
                    return true;
            }
        }

        if (board[0][2] == m && board[1][3] == m && board[2][4] == m)
            return true;

        if (board[0][2] == m && board[1][1] == m && board[2][0] == m)
            return true;

        if (board[2][4] == m && board[3][3] == m && board[4][2] == m)
            return true;

        if (board[2][0] == m && board[3][1] == m && board[4][2] == m)
            return true;

        if (board[1][1] == m && board[2][2] == m && board[3][3] == m)
            return true;

        if (board[1][3] == m && board[2][2] == m && board[3][1] == m)
            return true;

        return false;
    }

    else if (is_vertical_four(m)) {

        for (int i = 1; i <= 3; i++) {
            if (board[i][1] == m && board[i][2] == m && board[i][3] == m)
                return true;

            if (i == 2) {
                if (board[2][0] == m && board[2][1] == m && board[2][2] == m)
                    return true;

                if (board[2][2] == m && board[2][3] == m && board[2][4] == m)
                    return true;
            }
        }

        if (board[0][2] == m && board[1][3] == m && board[2][4] == m)
            return true;

        if (board[0][2] == m && board[1][1] == m && board[2][0] == m)
            return true;

        if (board[2][4] == m && board[3][3] == m && board[4][2] == m)
            return true;

        if (board[2][0] == m && board[3][1] == m && board[4][2] == m)
            return true;

        if (board[1][1] == m && board[2][2] == m && board[3][3] == m)
            return true;

        if (board[1][3] == m && board[2][2] == m && board[3][1] == m)
            return true;

        return false;
    }

    return false;
}

bool diamond_XO_Board::is_win(Player<char>* player) {
    char m = player->get_symbol();

    if (is_horizontal_four(m) || is_vertical_four(m)) {
        if (is_three(m)) {
            return true;
        }
    }
    return false;
}

bool diamond_XO_Board::is_lose(Player<char>* player) {
    char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    if (is_horizontal_four(opponent_symbol) || is_vertical_four(opponent_symbol)) {
        if (is_three(opponent_symbol)) {
            return true;
        }
    }
    return false;
}

bool diamond_XO_Board::is_draw(Player<char>* player) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (playable[i][j]) return false;
        }
    }

    if (!is_win(player) && !is_lose(player)) {
        return true;
    }

    return false;
}













bool diamond_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}
















//diamond_XO_UI::diamond_XO_UI() : UI<char>("Diamond Tic-Tac-Toe Game", 3) {}

Player<char>* diamond_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* diamond_XO_UI::get_move(Player<char>* player) {
    int x = 0, y = 0;


    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << "Please enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        auto now = player->get_board_ptr()->get_board_matrix();
        char computer = player->get_symbol();
        char human = (computer == 'X' ? 'O' : 'X');

        if (now[2][2] == human)
        {

            if (playable[1][2])
            {
                x = 1; y = 2;
            }
            else if (playable[2][1])
            {
                x = 2; y = 1;
            }
            else if (playable[2][3])
            {
                x = 2; y = 3;
            }
            else if (playable[3][2])
            {
                x = 3; y = 2;
            }
            else {
                x = rand() % player->get_board_ptr()->get_rows();
                y = rand() % player->get_board_ptr()->get_columns();
            }

        }
        else if (now[2][2] == computer) {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        }
        else {
            x = 2;
            y = 2;
        }


    }
    return new Move<char>(x, y, player->get_symbol());
}


diamond_XO_UI::diamond_XO_UI() : UI<char>("", 3) {
    display_welcome_message();
}

void diamond_XO_UI::display_welcome_message() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|          MISERE TIC-TAC-TOE          |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|        Welcome to Inverse XO!        |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|               GAME RULES:            |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Objective: AVOID making 3 in a row |\n";
    cout << "    " << "| * Players: X and O                   |\n";
    cout << "    " << "| * You LOSE if you complete:          |\n";
    cout << "    " << "|   - 3 of your symbols in a row       |\n";
    cout << "    " << "|   - 3 of your symbols in a column    |\n";
    cout << "    " << "|   - 3 of your symbols diagonally     |\n";
    cout << "    " << "| * Draw if board fills with no        |\n";
    cout << "    " << "|     3-in-a-row                       |\n";
    cout << "    " << "|--------------------------------------|\n\n";
}


void diamond_XO_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    if (matrix.empty()) return;

    cout << "_____________________________________\n";

    vector<int> nums = { 1, 3, 5, 3, 1 };
    vector<int> start_col = { 2, 1, 0, 1, 2 };

    cout << "";
    for (int c = 0; c < 5; c++)
        cout << setw(4) << c << "   ";
    cout << "\n";
    cout << "_____________________________________\n";

    for (int i = 0; i < 5; i++) {

        int count = nums[i];
        int s_col = start_col[i];

        int spaces = (5 - count) * 3;
        cout << string(spaces, ' ');

        cout << i << "  ";

        for (int k = 0; k < count; k++) {
            char cell = matrix[i][s_col + k];
            cout << "[ " << cell << " ] ";
        }

        cout << "\n";
        cout << "_____________________________________\n";
    }
}
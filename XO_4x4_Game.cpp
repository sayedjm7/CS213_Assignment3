#include <iostream>
#include <iomanip>
#include <cctype>
#include <math.h>
#include "XO_4x4_Game.h"
#include "BoardGame_Classes.h"
using namespace std;


XO_Move::XO_Move(int oldX, int oldY, int newX, int newY, char symbol) :
    Move<char>(newX, newY, symbol), old_x(oldX), old_y(oldY) {}

int XO_Move::get_old_x() { return old_x; }
int XO_Move::get_old_y() { return old_y; }



XO_GameSeven_Board::XO_GameSeven_Board() : Board(4, 4) {
    board[0][0] = board[0][2] = board[3][1] = board[3][3] = 'O';
    board[0][1] = board[0][3] = board[3][0] = board[3][2] = 'X';
    for (int i = 1; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = blank_symbol;
        }
    }

};

bool XO_GameSeven_Board::update_board(Move<char>* move) {
    XO_Move* xo_move = static_cast<XO_Move*>(move);

    int oldX = xo_move->get_old_x();
    int oldY = xo_move->get_old_y();
    int newX = xo_move->get_x();
    int newY = xo_move->get_y();
    char sym = xo_move->get_symbol();

    if (board[newX][newY] == blank_symbol) {
        board[oldX][oldY] = blank_symbol;
        board[newX][newY] = sym;
        return true;

    }
    return false;

}

bool XO_GameSeven_Board::is_valid_move(int ox, int oy, int nx, int ny, PlayerType pt) {

    if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) {
        if (pt == PlayerType::HUMAN) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|             INVALID MOVE             |\n";
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|       Position out of the board!     |\n";
            cout << "    " << "|--------------------------------------|\n";
        }
        return false;
    }

    if (board[nx][ny] != blank_symbol) {
        if (pt == PlayerType::HUMAN) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|             INVALID MOVE             |\n";
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|      Please select empty position.   |\n";
            cout << "    " << "|--------------------------------------|\n";
        }
        return false;
    }

    if (board[ox][oy] == blank_symbol) {
        if (pt == PlayerType::HUMAN) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|             INVALID MOVE             |\n";
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|      No piece at source position!    |\n";
            cout << "    " << "|--------------------------------------|\n";
        }
        return false;
    }

    int dx = abs(ox - nx);
    int dy = abs(oy - ny);

    if (dx == 1 && dy == 1) {
        if (pt == PlayerType::HUMAN) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|             INVALID MOVE             |\n";
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|     Diagonal moves are not allowed!  |\n";
            cout << "    " << "|--------------------------------------|\n";
        }
        return false;
    }

    if (dx > 1 || dy > 1) {
        if (pt == PlayerType::HUMAN) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|             INVALID MOVE             |\n";
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|        You cannot jump 2 cells!      |\n";
            cout << "    " << "|--------------------------------------|\n";
        }
        return false;
    }

    if (dx > 1 || dy > 1 || (dx == 0 && dy == 0)) {
        if (pt == PlayerType::HUMAN) {
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|             INVALID MOVE             |\n";
            cout << "    " << "|--------------------------------------|\n";
            cout << "    " << "|       Move to adjacent cells only!   |\n";
            cout << "    " << "|          (up/down/left/right)        |\n";
            cout << "    " << "|--------------------------------------|\n";
        }
        return false;
    }

    return true;
}

bool XO_GameSeven_Board::is_win(Player<char>* player) {

    auto all_eq = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Row check
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) {
            if (all_eq(board[j][i], board[j][i + 1], board[j][i + 2])) {
                return true;
            }
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) {
            if (all_eq(board[i][j], board[i + 1][j], board[i + 2][j])) {
                return true;
            }
        }
    }
    if (all_eq(board[0][0], board[1][1], board[2][2]) ||
        all_eq(board[1][1], board[2][2], board[3][3]) ||
        all_eq(board[0][1], board[1][2], board[2][3]) ||
        all_eq(board[1][0], board[2][1], board[3][2]) ||
        all_eq(board[0][2], board[1][1], board[2][0]) ||
        all_eq(board[1][3], board[2][2], board[3][1]) ||
        all_eq(board[0][3], board[1][2], board[2][1]) ||
        all_eq(board[1][2], board[2][1], board[3][0])) {
        return true;
    }


    return false;
}



// UI Class
XO_GameSeven_UI::XO_GameSeven_UI() : UI<char>("", 3) {
    display_welcome_message();
}

bool XO_GameSeven_UI::will_win(Board<char>* board, int& bx, int& by, char sym) {
    vector<vector<char>> board_matrix;
    board_matrix = board->get_board_matrix();

    // row check
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) {
            if (board_matrix[j][i] == sym && board_matrix[j][i + 1] == sym && board_matrix[j][i + 2] == ' ') {
                bx = j;
                by = i + 2;
                return true;
            }
            if (board_matrix[j][i] == ' ' && board_matrix[j][i + 1] == sym && board_matrix[j][i + 2] == sym) {
                bx = j;
                by = i;
                return true;
            }
            if (board_matrix[j][i] == sym && board_matrix[j][i + 1] == ' ' && board_matrix[j][i + 2] == sym) {
                bx = j;
                by = i + 1;
                return true;
            }
        }
    }

    // col check
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) {
            if (board_matrix[i][j] == sym && board_matrix[i + 1][j] == sym && board_matrix[i + 2][j] == ' ') {
                bx = i + 2;
                by = j;
                return true;
            }
            if (board_matrix[i][j] == ' ' && board_matrix[i + 1][j] == sym && board_matrix[i + 2][j] == sym) {
                bx = i;
                by = j;
                return true;
            }
            if (board_matrix[i][j] == sym && board_matrix[i + 1][j] == ' ' && board_matrix[i + 2][j] == sym) {
                bx = i + 1;
                by = j;
                return true;
            }
        }
    }

    // -- diagonals
    // 00 (11 22)
    if (board_matrix[1][1] == sym && board_matrix[2][2] == sym && board_matrix[0][0] == ' ') {
        bx = 0;
        by = 0;
        return true;
    }

    // 01 (12 23)
    if (board_matrix[1][2] == sym && board_matrix[2][3] == sym && board_matrix[0][1] == ' ') {
        bx = 0;
        by = 1;
        return true;
    }

    // 02 (11 20)
    if (board_matrix[1][1] == sym && board_matrix[2][0] == sym && board_matrix[0][2] == ' ') {
        bx = 0;
        by = 2;
        return true;
    }

    // 03 (12 21)
    if (board_matrix[1][2] == sym && board_matrix[2][1] == sym && board_matrix[0][3] == ' ') {
        bx = 0;
        by = 3;
        return true;
    }

    // 10 (21 32)
    if (board_matrix[2][1] == sym && board_matrix[3][2] == sym && board_matrix[1][0] == ' ') {
        bx = 1;
        by = 0;
        return true;
    }

    // 11 (00 22) (22 33) (02 20)
    if (((board_matrix[0][0] == sym && board_matrix[2][2] == sym) ||
        (board_matrix[2][2] == sym && board_matrix[3][3] == sym) ||
        (board_matrix[0][2] == sym && board_matrix[2][0] == sym)) && board_matrix[1][1] == ' ') {
        bx = 1;
        by = 1;
        return true;
    }

    // 12 (01 23) (03 21) (21 30)
    if (((board_matrix[0][1] == sym && board_matrix[2][3] == sym) ||
        (board_matrix[0][3] == sym && board_matrix[2][1] == sym) ||
        (board_matrix[2][1] == sym && board_matrix[3][0] == sym)) && board_matrix[1][2] == ' ') {
        bx = 1;
        by = 2;
        return true;
    }

    // 13 (22 31)
    if (board_matrix[2][2] == sym && board_matrix[3][1] == sym && board_matrix[1][3] == ' ') {
        bx = 1;
        by = 3;
        return true;
    }

    // 20 (11 02)
    if (board_matrix[1][1] == sym && board_matrix[0][2] == sym && board_matrix[2][0] == ' ') {
        bx = 2;
        by = 0;
        return true;
    }

    // 21 (10 32) (03 12) (12 30)
    if (((board_matrix[1][0] == sym && board_matrix[3][2] == sym) ||
        (board_matrix[0][3] == sym && board_matrix[1][2] == sym) ||
        (board_matrix[1][2] == sym && board_matrix[3][0] == sym)) && board_matrix[2][1] == ' ') {
        bx = 2;
        by = 1;
        return true;
    }

    // 22 (00 11) (11 33) (13 31)
    if (((board_matrix[0][0] == sym && board_matrix[1][1] == sym) ||
        (board_matrix[1][1] == sym && board_matrix[3][3] == sym) ||
        (board_matrix[1][3] == sym && board_matrix[3][1] == sym)) && board_matrix[2][2] == ' ') {
        bx = 2;
        by = 2;
        return true;
    }

    // 23 (01 12)
    if (board_matrix[0][1] == sym && board_matrix[1][2] == sym && board_matrix[2][3] == ' ') {
        bx = 2;
        by = 3;
        return true;
    }

    // 30 (21 12)
    if (board_matrix[2][1] == sym && board_matrix[1][2] == sym && board_matrix[3][0] == ' ') {
        bx = 3;
        by = 0;
        return true;
    }

    // 31 (13 22)
    if (board_matrix[1][3] == sym && board_matrix[2][2] == sym && board_matrix[3][1] == ' ') {
        bx = 3;
        by = 1;
        return true;
    }

    // 32 (10 21)
    if (board_matrix[1][0] == sym && board_matrix[2][1] == sym && board_matrix[3][2] == ' ') {
        bx = 3;
        by = 2;
        return true;
    }

    // 33 (11 22)
    if (board_matrix[1][1] == sym && board_matrix[2][2] == sym && board_matrix[3][3] == ' ') {
        bx = 3;
        by = 3;
        return true;
    }
    return false;
}

Player<char>* XO_GameSeven_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|             PLAYER CREATED           |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|  Type:    " << setw(25) << left << (type == PlayerType::HUMAN ? "Human" : "Computer") << " |\n";
    cout << "    " << "|  Name:    " << setw(25) << left << name << " |\n";
    cout << "    " << "|  Symbol:  " << setw(25) << left << symbol << " |\n";
    cout << "    " << "|--------------------------------------|\n\n\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* XO_GameSeven_UI::get_move(Player<char>* player) {
    Board<char>* game_board = player->get_board_ptr();
    const char sym = player->get_symbol();
    vector<vector<char>> current_board = game_board->get_board_matrix();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|              " << player->get_name() << "'s TURN            |\n";
        cout << "    " << "|               Symbol: " << sym << "              |\n";
        cout << "    " << "|--------------------------------------|\n";
        do {
            cout << "    " << "| Select your piece (row col): ";
            cin >> oldX >> oldY;
            cout << "    " << "|--------------------------------------|\n";

            if (oldX < 0 || oldX > 3 || oldY < 0 || oldY > 3 ||
                current_board[oldX][oldY] != sym) {
                cout << "    " << "|   You can only move your " << sym << " pieces!   |\n";
                cout << "    " << "|--------------------------------------|\n";
            }
        } while (oldX < 0 || oldX > 3 || oldY < 0 || oldY > 3 ||
            current_board[oldX][oldY] != sym);

        cout << "    " << "|   Selected piece at (" << oldX << "," << oldY << ")            |\n";
        cout << "    " << "|--------------------------------------|\n";

        do {
            cout << "    " << "| Move to position (row col): ";
            cin >> newX >> newY;
            cout << "    " << "|--------------------------------------|\n\n\n";
        }

        while (!game_board->is_valid_move(oldX, oldY, newX, newY, player->get_type()));
        cout << "    " << "|    Moving to (" << newX << "," << newY << ")                   |\n";
        cout << "    " << "|--------------------------------------|\n\n\n";
        return new XO_Move(oldX, oldY, newX, newY, sym);
    }


    if (player->get_type() == PlayerType::COMPUTER) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|          COMPUTER'S TURN             |\n";
        cout << "    " << "|               Symbol: " << player->get_symbol() << "              |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|        Computer is thinking...       |\n";
        cout << "    " << "|--------------------------------------|\n";

        char com_sym = player->get_symbol();
        char diff = (com_sym == 'X' ? 'O' : 'X');

        //win algorithm
        int win_x, win_y;
        if (will_win(game_board, win_x, win_y, com_sym)) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (current_board[i][j] == com_sym &&
                        game_board->is_valid_move(i, j, win_x, win_y, player->get_type())) {
                        cout << "    " << "| Computer strategy: WINNING MOVE      |\n";
                        cout << "    " << "| Moving (" << i << "," << j << ") to (" << win_x << "," << win_y << ")                |\n";
                        cout << "    " << "|--------------------------------------|\n\n";
                        return new XO_Move(i, j, win_x, win_y, com_sym);
                    }
                }
            }
        }


        //block algorithm
        int block_x, block_y;
        if (will_win(game_board, block_x, block_y, diff)) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (current_board[i][j] == com_sym &&
                        game_board->is_valid_move(i, j, block_x, block_y, player->get_type())) {
                        cout << "    " << "| Computer strategy: BLOCKING MOVE     |\n";
                        cout << "    " << "| Blocking (" << i << "," << j << ") to (" << block_x << "," << block_y << ")              |\n";
                        cout << "    " << "|--------------------------------------|\n\n";
                        return new XO_Move(i, j, block_x, block_y, com_sym);
                    }
                }
            }
        }


        cout << "    " << "|    Computer strategy: RANDOM MOVE    |\n";
        cout << "    " << "|--------------------------------------|\n";

        do {
            oldX = rand() % 4;
            oldY = rand() % 4;
        } while (current_board[oldX][oldY] != player->get_symbol());

        bool valid_move_found = false;

        do {
            int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

            for (int d = 0; d < 4; d++) {
                newX = oldX + directions[d][0];
                newY = oldY + directions[d][1];

                if (newX >= 0 && newX < 4 && newY >= 0 && newY < 4 &&
                    current_board[newX][newY] == ' ') {
                    if (game_board->is_valid_move(oldX, oldY, newX, newY, player->get_type())) {
                        valid_move_found = true;
                        break;
                    }
                }
            }

            if (!valid_move_found) {
                do {
                    oldX = rand() % 4;
                    oldY = rand() % 4;
                } while (current_board[oldX][oldY] != com_sym);
            }
        } while (!valid_move_found);

        cout << "    " << "| Moving (" << oldX << "," << oldY << ") to (" << newX << "," << newY << ")                |\n";
        cout << "    " << "|--------------------------------------|\n\n";

        return new XO_Move(oldX, oldY, newX, newY, com_sym);
    }
}
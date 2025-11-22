#include <iostream>
#include <iomanip>
#include <cctype>
#include <math.h>
#include "BoardGame_Classes.h"
using namespace std;


class XO_Move : public Move<char> {
private:
    int old_x, old_y;
public:
    XO_Move(int oldX, int oldY, int newX, int newY, char symbol)
        : Move<char>(newX, newY, symbol), old_x(oldX), old_y(oldY) {}

    int get_old_x() const { return old_x; }
    int get_old_y() const { return old_y; }
};




class XO_GameSeven_Board : public Board<char> {
private:
    char blank_symbol = ' ';
public:

    XO_GameSeven_Board(): Board (4,4) {
        board[0][0] = board[0][2] = board[3][1] = board[3][3] = 'O';
        board[0][1] = board[0][3] = board[3][0] = board[3][2] = 'X';
        for (int i = 1; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                board[i][j] = blank_symbol;
            }
        }
    };

    bool update_board(Move<char>* move) {
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

    bool is_valid_move(int ox, int oy, int nx, int ny) {


        if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) {
            cout << "Positon out of the board!\n";
            return false;
        }

        if (board[nx][ny] != blank_symbol ) {

            cout << "Invalid position, Please select empty position.\n";
            return false;
        }

        if (board[ox][oy] == blank_symbol) {
            cout << "No piece at source position!\n";
            return false;
        }

        int dx = abs(ox - nx);
        int dy = abs(oy - ny);

        if (dx == 1 && dy == 1) {
            cout << "Diagonal moves are not allowed!\n";
            return false;
        }

        if (dx > 1 || dy > 1) {
            cout << "Invalid position, You cannot jump 2 cells\n";
            return false;
        }

        if (dx > 1 || dy > 1 || (dx == 0 && dy == 0)) {
            cout << "You can only move to adjacent cells (up/down/left/right)!\n";
            return false;
        }

        return true;
    }

    bool is_win(Player<char>* player) {
        const char sym = player->get_symbol();

        auto all_eq = [&](char a,char b, char c) {
            return a == b && b == c && a != blank_symbol;
            };
        // Row check
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 2; i++) {
                if (all_eq(board[j][i],board[j][i+1],board[j][i+2])) {
                    return true;
                }
            }
        }

        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 2; i++) {
                if (all_eq(board[i][j],board[i+1][j],board[i+2][j])) {
                    return true;
                }
            }
        }
        if (all_eq(board[0][0],board[1][1],board[2][2]) ||
            all_eq(board[1][1],board[2][2],board[3][3]) ||
            all_eq(board[0][1],board[1][2],board[2][3]) ||
            all_eq(board[1][0],board[2][1],board[3][2]) ||
            all_eq(board[0][2],board[1][1],board[2][0]) ||
            all_eq(board[1][3],board[2][2],board[3][1]) ||
            all_eq(board[0][3],board[1][2],board[2][1]) ||
            all_eq(board[1][2],board[2][1],board[3][0])) {
            return true;
        }


        return false;
        //check row
        // 00 01 02 || 01 02 03   -> Row   {j(0-3), (i(0-2) || (1-3)) }
        // 00 10 20 || 10 20 30   -> Column    {(i(0-2) (1-3)) ,j(0-3)}
        // 00 11 22 || 11 22 33   -> main digonal   i, i(0-2) (1-3) -
        // 01 12 23 || 10 21 32   -> main sub digonal ***

        // 02 11 20 || 13  22  31
        // 03 12 21 || 12  21  30




        // 00  01  02  03
        // 10  11  12  13
        // 20  21  22  23
        // 30  31  32  33

    }
    bool is_draw(Player<char>* player) {
        return false;
    };
    bool is_lose(Player<char>* player) {
        return false;
    };
    bool game_is_over(Player<char>* player) {
        return is_win(player);
    }

};

class XO_GameSeven_UI : public UI<char> {
private:
    int newX, newY;
    int oldX, oldY;
    void display_welcome_message() {
    cout << "========================================\n"
         << "           4 x 4 Tic-Tac-Toe\n"
         << "========================================\n"
         << "           Welcome to Game Seven!       \n"
         << "========================================\n\n"
         << "    GAME RULES:\n"
         << "*- Each player has 4 tokens (X or O)\n"
         << "*- Move your tokens to adjacent cells (up/down/left/right)\n"
         << "*- WINNING: Form 3 consecutive tokens in:\n"
         << "  - ROW (horizontal)  \n"
         << "  - COLUMN (vertical)  \n"
         << "  - DIAGONAL (diagonal)\n"
         << "========================================\n\n"
        ;

    }
    void display_win_message(Player<char>* player) {
        cout << "\n========================================\n"
             << "                   VICTORY!              \n"
             << "========================================\n"
             << "   Congratulations " << player->get_name() << "! \n"
             << "========================================\n";
    }


public:
    XO_GameSeven_UI() : UI<char> ("",3){
        display_welcome_message();
}



    Player<char>* create_player(string& name, char symbol, PlayerType type) {
        cout << "Creating " << (type == PlayerType::HUMAN ? "human " : "computer ") << "player: "
        << name << " (" << symbol << ") \n";

        return new Player<char> (name,symbol,type);
    };

    Move<char>* get_move(Player<char>* player) {

        Board<char>* game_board = player->get_board_ptr();
        const char sym = player->get_symbol();
        vector<vector<char>> current_board = game_board->get_board_matrix();

        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << "'s Turn (" << sym << ")\n";

            do {
                cout << "Select a token to move (e.g., 0 2):  ";
                cin >> oldX >> oldY;
                if (oldX < 0 || oldX > 3 || oldY < 0 || oldY > 3 ||
                    current_board[oldX][oldY] != sym) {
                    cout << "You can only move your own pieces. Select an (" <<  sym << "): " ;
                    }
            }
            while (oldX < 0 || oldX > 3 || oldY < 0 || oldY > 3 ||
            current_board[oldX][oldY] != sym);

            do {
                cout << "Move to which position: ";
                cin >> newX >> newY;
                if (!game_board->is_valid_move(oldX, oldY, newX, newY)) {
                    cout << "INvalid\n";
                }
            }
            while (!game_board->is_valid_move(oldX,oldY,newX,newY));

            return new XO_Move(oldX, oldY, newX, newY, sym);
        }


        else if (player->get_type() == PlayerType::COMPUTER) {
            do {
                oldX = rand() % 4;
                oldY = rand() % 4;
            }
            while (current_board[oldX][oldY] != player->get_symbol());


            do {
                newX = rand() % 4;
                newY = rand() % 4;
            }
            while (newX < 0 || newX > 3 || newY < 0 || newY > 3 ||
                 current_board[newX][newY] != ' ' ||
                 !((abs(newX - oldX) == 1 && abs(newY - oldY) == 0) ||
                   (abs(newX - oldX) == 0 && abs(newY - oldY) == 1)));
            return new XO_Move(oldX, oldY, newX, newY, sym);        }
    };
};
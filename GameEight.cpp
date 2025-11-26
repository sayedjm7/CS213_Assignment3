#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "GameEight.h"

#include <math.h>
#include <queue>
using namespace std;

// Pry_Board

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
    //      00
    //   10 11 12
    //20 21 22 23 24
//-----------------------------
    auto all_eq = [&](char a, char b, char c) {
        return (a == b && b == c && a != black_symbol);
    };


    // 1 (i 0-2)
    // 2 (i 0-4) 0-2 1-3 2-4
    for (int j = 1; j < 3; j++) {
        for (int i = 0; i + 2 <  board[j].size(); i++) {
            if (all_eq(board[j][i], board[j][i + 1], board[j][i + 2])) {
                return true;
            }
        }
    }

    // 00 11 22
    // 00 12 24 || 00 10 20 -> i(0-2) 0
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



// Pry_UI

Pry_UI::Pry_UI() : UI<char>("",3) {
    display_welcome_message();
}

void Pry_UI::display_message(string message) {
    cout << message << "\n";
}

void Pry_UI::display_board_matrix(const vector<vector<char> > &matrix) const  {

    if (matrix.empty()) return;

    int rows = matrix.size();
    int cols = 5;

    cout << "\n    ";
    for (int i = 0; i < 5; i++) {
        cout << i << string(cell_width + 1, ' ') ;
    }
    cout << "\n";

    for (int i = 0 , inde = 10; i < rows; ++i, inde -= 5) {

        cout << string(inde, ' ');
        cout << string((cell_width + 2) * 2 * (i + 1) , '-') << "\n";

        cout << string(inde, ' ') << i << " |";
        for (int j = 0; j < matrix[i].size(); ++j)
            cout << setw(cell_width) << matrix[i][j] << " |";
        cout << "\n";
    }

    cout << string((cell_width + 2) * 6, '-') << "\n\n";
}

/*
        //    0   1   2   3
        //--------------------
        //0 |  O |  X |  O |  X |
        //--------------------
        //1 |    |    |    |    |
        //--------------------
        //2 |    |    |    |    |
        //--------------------
        //3 |  X |  O |  X |  O |
        //--------------------

    */
/*       *        0    1    2    3    4
         *              ----------
         *              0 |    |
         *         --------------------
         *         1 |    |    |    |
         *    ------------------------------
         *    2 |    |    |    |    |    |
         *    ------------------------------
         *
     */
/*      10' ' 10'-'
     *  10' ' row(0) 1' |'  1 cell_width ' |'
     *  05' ' 20'-'
     *  05' ' row(1) 1' |'  3 cell_width ' |'
     *  00' ' 30'-'
     *  00' ' row(2) 1' |'  5 cell_width ' |'
     *  00' ' 30'-'
     *
     */

Player<char>* Pry_UI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " <<  (type == PlayerType::HUMAN ? "human " : "computer ") << "player: "
    << name << " (" << symbol << ")\n";

    return new Player<char> (name,symbol,type);
 }
Move<char>* Pry_UI::get_move(Player<char>* player) {
    int x, y;

    Board<char>* game_board = player->get_board_ptr();
    const char sym = player->get_symbol();
    vector<vector<char>> current_board = game_board->get_board_matrix();


    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol()
        << ") enter your move (row col): ";
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

    }
    else if (player->get_type() == PlayerType::COMPUTER){
        x =  rand() % 3;
        y = rand() % 5;
        while (x < 0 || x > 2 || y < 0 || y > 4) {
            x =  rand() % 2;
            y = rand() % 4;
        }
    }

    return new Move<char>(x, y, player->get_symbol());
}



/*
 *
 *
 *   00 01 02 03 04 05
 *   10 11 12 13 14 15
 *   20 21 22 23 24 25
 *   30 31 32 33 34 35
 *   40 41 42 43 44 45
 *   50 51 52 53 54 55
 *
 *
 *   00 01 02 03 || 01 02 03 04 || 02 03 04 05  -> i(0-5), j(0-3) (1-4) (2-5)
 *   j(0-3) (1-4) (2-5), i(0-5)
 *
 *   main diagonal
 *   02 13 24 35  i i+2,  i+1 (i+1)+2, i+2 (i+2)+2, i+3 (i+3)+2 ->     {i(0-3)  j=(i+2)}
 *   01 12 23 34 || 12 23 34 45 ||  i i+1  i+1 i+2  i+2 i+3  i+3 i+4   {i(0-1)  j=i+1, n(0-3)}   i+n j+n,
 *   00 11 22 33 || 11 22 33 44 || 22 33 44 55 -> i(0-2)  i i   i+1 i+1   i+2 i+2   i+3 i+3,   i(0-2)
 *   10 21 32 43 || 21 32 43 54  {i(1-2), j = i-1,}  i j, i+1 j+1, i+2 j+2, i+3 j+3
 *   20 31 42 53
 *
 *   inverse diagonal
 *   03 12 21 30
 *   04 13 22 31 || 13 22 31 40
 *   05 14 23 32 || 14 23 32 41 || 23 32 41 50
 *   15 24 33 42 || 24 33 42 51
 *   25 34 43 52
 *
 *
 *
 *
 *
 *
 *
 *
 */
//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "XO_Classes.h"

#include <math.h>
#include <queue>

using namespace std;

//--------------------------------------- X_O_Board Implementation

X_O_Board::X_O_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}


bool X_O_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    n_moves++;
    board[x][y] = toupper(mark);

    // FIFO
    qx.push(x);
    qy.push(y);

    // 00(X)  01(O)  10(X)  20(O)  02(X)  21(O) --> pop->front()
    if (qx.size() > 6) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|        OLDEST MOVE VANISHED!        |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "| Position (" << qx.front() << "," << qy.front() << ") disappeared |\n";
        cout << "    " << "|--------------------------------------|\n";
        board[qx.front()][qy.front()] = blank_symbol;
        qx.pop();
        qy.pop();
        n_moves--;
    }

    return true;
}

bool X_O_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
    };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }
    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool X_O_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool X_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

XO_UI::XO_UI() : UI<char>("", 3) {
    display_welcome_message();
}

void XO_UI::display_welcome_message() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|          INFINITY TIC-TAC-TOE        |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|    Welcome to the Infinite Game!     |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|              GAME RULES:             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Players: X and O                   |\n";
    cout << "    " << "| * Special: After 3 moves, the        |\n";
    cout << "    " << "|   oldest move disappears!            |\n";
    cout << "    " << "| * Win: Get 3 in a row before any     |\n";
    cout << "    " << "|   of your marks vanish               |\n";
    cout << "    " << "| * Draw: Board cycles with no winner  |\n";
    cout << "    " << "|--------------------------------------|\n\n";
}

Player<char>* XO_UI::create_player(string& name, char symbol, PlayerType type) {
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

Move<char>* XO_UI::get_move(Player<char>* player) {
    int x, y;
    Board<char>* game_board = player->get_board_ptr();
    const char sym = player->get_symbol();
    vector<vector<char>> current_board = game_board->get_board_matrix();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|              " << player->get_name() << "'s TURN             |\n";
        cout << "    " << "|               Symbol: " << player->get_symbol() << "              |\n";
        cout << "    " << "|--------------------------------------|\n";
        // cin >> x >> y;
        // start2:
        //     while (x < 0 || x >= 3 || y < 0 || y >= 3) {
        //         cout << "Invalid: out of shape\n" << "Enter position is shape: ";
        //         cin >> x >> y;
        //         if (current_board[x][y] != '.') {
        //             goto start1;
        //         }
        //     }
        // start1:
        //     while (current_board[x][y] != '.') {
        //         cout << "Enter empty position:";
        //         cin >> x >> y;
        //         if (x < 0 || x >= 3 || y < 0 || y >= 3) goto start2;
        //     }
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

bool X_O_Board::is_valid_move(int ox, int oy, int nx, int ny, PlayerType pt){
    return true;
}

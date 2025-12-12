

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include "BoardGame_Classes.h"

#include <math.h>
#include <queue>
#include "Obstacles_game.h"

using namespace std;

obstacle_board::obstacle_board() :Board(6, 6) { // 6 * 6 board game
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}
bool obstacle_board::is_valid_move(int ox, int oy, int nx, int ny,PlayerType p) {
    return true;
}
bool obstacle_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();


    char mark = move->get_symbol();



    // Validate move and apply if valid
    if (!(x < 0 || x >= 6 || y < 0 || y >= 6) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;

        }
        else {
            // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
            if (n_moves % 2 == 0 && n_moves != 0) {
                // make obstacles here ...
                x = rand() % 5;
                y = rand() % 5;
                int t = 2;
                // putting ## in random places...
                while (t > 0) {
                    if (board[x][y] != blank_symbol) {
                        while (board[x][y] != blank_symbol) {
                            x = rand() % 5;
                            y = rand() % 5;
                            if (board[x][y] == blank_symbol) {
                                board[x][y] = '#';
                                break;
                            }
                        }

                    }
                    else {
                        board[x][y] = '#';
                    }
                    t--;
                }

            }
        }

        return true;

    }
    return false;
}

bool obstacle_board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c, char d) {
        return a == b && b == c && c==d && a != blank_symbol;
        };

    // Check horizontal
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; j++) {
            if (all_equal(board[i][j], board[i][j+1], board[i][j+2], board[i][j+3]) && board[i][j] == sym) {
                return true;
            }
        }

    }


    // check virtical
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; j++) {
            if (all_equal(board[j][i], board[j][i+1], board[j][i+2], board[j][i+3])) {
                return true;
            }
        }
    }


    // check main diagonal
    if (all_equal(board[0][2], board[1][3], board[2][4], board[3][5]) && board[0][2] == sym) {
        return true;
    }
    if (all_equal(board[0][1], board[1][2], board[2][3], board[3][4]) && board[0][1] == sym) {
        return true;
    }

    if (all_equal(board[1][2], board[2][3], board[3][4], board[4][5]) && board[1][2] == sym) {
        return true;
    }

    if (all_equal(board[0][0], board[1][1], board[2][2], board[3][3]) && board[0][0] == sym) {
        return true;
    }
    if (all_equal(board[1][1], board[2][2], board[3][3], board[4][4]) && board[1][1] == sym) {
        return true;
    }
    if (all_equal(board[2][2], board[3][3], board[4][4], board[5][5]) && board[2][2] == sym) {
        return true;
    }
    if (all_equal(board[1][0], board[2][1], board[3][2], board[4][3]) && board[1][0] == sym) {
        return true;
    }
    if (all_equal(board[2][1], board[3][2], board[4][3], board[5][4]) && board[2][1] == sym) {
        return true;
    }
    if (all_equal(board[2][0], board[3][1], board[4][2], board[5][3]) && board[2][0] == sym) {
        return true;
    }

    //inverse diagonal
    if (all_equal(board[0][3], board[1][2], board[2][1], board[3][0]) && board[0][3] == sym) {
        return true;
    }
    if (all_equal(board[0][4], board[1][3], board[2][2], board[3][1]) && board[0][4] == sym) {
        return true;
    }
    if (all_equal(board[1][3], board[2][2], board[3][1], board[4][0]) && board[1][3] == sym) {
        return true;
    }
    if (all_equal(board[0][5], board[1][4], board[2][3], board[3][2]) && board[0][5] == sym) {
        return true;
    }
    if (all_equal(board[1][4], board[2][3], board[3][2], board[4][1]) && board[1][4] == sym) {
        return true;
    }

    if (all_equal(board[2][3], board[3][2], board[4][1], board[5][0]) && board[0][1] == sym) {
        return true;
    }
    if (all_equal(board[1][5], board[2][4], board[3][3], board[4][2]) && board[1][5] == sym) {
        return true;
    }
    if (all_equal(board[2][4], board[3][3], board[4][2], board[5][1]) && board[2][4] == sym) {
        return true;
    }
    if (all_equal(board[2][5], board[3][4], board[4][3], board[5][2]) && board[2][5] == sym) {
        return true;
    }



    return false;
}
bool obstacle_board::is_draw(Player<char>* player) {
    return (n_moves ==  18 && !is_win(player));
}

bool obstacle_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

obstacle_ui::obstacle_ui() : UI<char>("", 3) {
    display_welcome_message();
}

void obstacle_ui::display_welcome_message() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|            OBSTACLE GAME             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|     Welcome to the Obstacle Race!    |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|              GAME RULES:             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Board: 6x6 grid                    |\n";
    cout << "    " << "| * Players: X and O                   |\n";
    cout << "    " << "| * Special: After each round,         |\n";
    cout << "    " << "|   2 obstacles (#) are randomly added |\n";
    cout << "    " << "| * Obstacles block both players       |\n";
    cout << "    " << "| * Win: 4 in row/column/diagonal      |\n";
    cout << "    " << "| * Draw: Board full with no winner    |\n";
    cout << "    " << "|--------------------------------------|\n\n";
}

Player<char>* obstacle_ui::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|             PLAYER CREATED           |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|  Type:    " << setw(25) << left
         << (type == PlayerType::HUMAN ? "Human" : "Computer") << "|\n";
    cout << "    " << "|  Name:    " << setw(25) << left << name << "|\n";
    cout << "    " << "|  Symbol:  " << setw(25) << left << symbol << "|\n";
    cout << "    " << "|--------------------------------------|\n\n\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* obstacle_ui::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|              " << player->get_name() << "'s TURN             |\n";
        cout << "    " << "|               Symbol: " << player->get_symbol() << "              |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "| Enter your move (row col 0-5): ";
        cin >> x >> y;
        cout << "    " << "|--------------------------------------|\n";
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}



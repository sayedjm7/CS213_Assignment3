//
// Created by dell on 03/12/2025.
//
#include "four_in_row.h"
#include "BoardGame_Classes.h"

four_in_row_board::four_in_row_board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

four_in_row_ui::four_in_row_ui() : UI<char>("", 3) {
    display_welcome_message();
}

void four_in_row_ui::display_welcome_message() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|             FOUR IN A ROW            |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|          Welcome to Connect 4!       |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|               GAME RULES:            |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Players:                            |\n";
    cout << "    " << "|   - Player 1: 'X'                     |\n";
    cout << "    " << "|   - Player 2: 'O'                     |\n";
    cout << "    " << "| * Goal: Connect 4 of your symbol      |\n";
    cout << "    " << "|   vertically, horizontally, or       |\n";
    cout << "    " << "|   diagonally.                         |\n";
    cout << "    " << "| * Winner: First to connect 4 in a row |\n";
    cout << "    " << "|--------------------------------------|\n\n\n";
}

bool four_in_row_board::update_board(Move<char>* move) {
    int y = move->get_y();
    char mark = move->get_symbol();

    // Fixed: Changed y > 6 to y >= 7
    if (y < 0 || y >= 7) {
        return false;
    }

    if (board[0][y] != blank_symbol) {
        return false;
    }

    for (int row = 5; row >= 0; row--) {
        if (board[row][y] == blank_symbol) {
            board[row][y] = mark;
            return true;
        }
    }

    return false;
}

Player<char>* four_in_row_ui::create_player(string& name, char symbol, PlayerType type) {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|             PLAYER CREATED           |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|  Type:    " << setw(25) << left
         << (type == PlayerType::HUMAN ? "Human" : "Computer") << " |\n";
    cout << "    " << "|  Name:    " << setw(25) << left << name << " |\n";
    cout << "    " << "|  Symbol:  " << setw(25) << left << symbol << " |\n";
    cout << "    " << "|--------------------------------------|\n\n\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* four_in_row_ui::get_move(Player<char> *player) {
    int y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|           " << player->get_name() << "'s TURN               |\n";
        cout << "    " << "|               Symbol: " << player->get_symbol() << "              |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "| Enter column (0-6): ";
        cin >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* game_board = player->get_board_ptr();
        vector<vector<char>> board = game_board->get_board_matrix();
        char ai_symbol = player->get_symbol();
        char opponent_symbol = (ai_symbol == 'X') ? 'O' : 'X';
        char blank = '.';

        y = -1;
        int best_score = -10000;

        // Try each column
        for (int col = 0; col < 7; col++) {
            // Check if column is valid
            if (board[0][col] != blank) {
                continue;
            }

            // Find where piece would land
            int land_row = -1;
            for (int row = 5; row >= 0; row--) {
                if (board[row][col] == blank) {
                    land_row = row;
                    break;
                }
            }

            if (land_row == -1) {
                continue;
            }

            int score = 0;

            // Check if AI can win
            board[land_row][col] = ai_symbol;
            bool can_win = false; // true if ai can win & false if it cant

            // Check horizontal win
            for (int j = 0; j < 4; j++) {
                if (col >= j && col <= j + 3) {
                    int count = 0;
                    for (int k = 0; k < 4; k++) {
                        if (board[land_row][j + k] == ai_symbol) {
                            count++;
                        }
                    }
                    if (count == 4) {
                        can_win = true;
                    }
                }
            }

            // Check vertical win
            if (land_row <= 2) { // 0 , 1 , 2 only
                int count = 0;
                for (int k = 0; k < 4; k++) {
                    if (board[land_row + k][col] == ai_symbol) {
                        count++;
                    }
                }
                if (count == 4) {
                    can_win = true;
                }
            }
            // check diagonal win
            int count_down_right = 0;

            int r = land_row, c = col;
            while (r >= 0 && c >= 0 && board[r][c] == ai_symbol) {
                count_down_right++;
                r--;
                c--;
            }

            r = land_row + 1;
            c = col + 1;
            while (r < 6 && c < 7 && board[r][c] == ai_symbol) {
                count_down_right++;
                r++;
                c++;
            }
            if (count_down_right >= 4) can_win = true;


            int count_down_left = 0;
            r = land_row;
            c = col;
            while (r >= 0 && c < 7 && board[r][c] == ai_symbol) {
                count_down_left++;
                r--;
                c++;
            }
            r = land_row + 1;
            c = col - 1;
            while (r < 6 && c >= 0 && board[r][c] == ai_symbol) {
                count_down_left++;
                r++;
                c--;
            }
            if (count_down_left >= 4) {
                can_win = true;
            }

            if (can_win) {
                score += 10000;
            }

            board[land_row][col] = blank;
            // ======================================================================================================//

            // Block opponent from winning
            board[land_row][col] = opponent_symbol;
            bool opponent_can_win = false;

            // Check horizontal
            for (int j = 0; j < 4; j++) {
                if (col >= j && col <= j + 3) {
                    int count = 0;
                    for (int k = 0; k < 4; k++) {
                        if (board[land_row][j + k] == opponent_symbol) {
                            count++;
                        }
                    }
                    if (count == 4) {
                        opponent_can_win = true;
                    }
                }
            }

            // Check vertical
            if (land_row <= 2) {
                int count = 0;
                for (int k = 0; k < 4; k++) {
                    if (board[land_row + k][col] == opponent_symbol) {
                        count++;
                    }
                }
                if (count == 4) {
                    opponent_can_win = true;
                }
            }

            // Check diagonal
            count_down_right = 0;
            // Count up-left from current position
            r = land_row, c = col;
            while (r >= 0 && c >= 0 && board[r][c] == opponent_symbol) {
                count_down_right++;
                r--;
                c--;
            }
            // Count down-right from next position
            r = land_row + 1;
            c = col + 1;
            while (r < 6 && c < 7 && board[r][c] == opponent_symbol) {
                count_down_right++;
                r++;
                c++;
            }
            if (count_down_right >= 4) {
                opponent_can_win = true;
            }

            // Check diagonal
            count_down_left = 0;
            // Count up-right from current position
            r = land_row;
            c = col;
            while (r >= 0 && c < 7 && board[r][c] == opponent_symbol) {
                count_down_left++;
                r--;
                c++;
            }
            // Count down-left from next position
            r = land_row + 1;
            c = col - 1;
            while (r < 6 && c >= 0 && board[r][c] == opponent_symbol) {
                count_down_left++;
                r++;
                c--;
            }
            if (count_down_left >= 4) {
                opponent_can_win = true;
            }

            if (opponent_can_win) {
                score += 5000;
            }

            board[land_row][col] = blank;

            // ===================================================================================================== //

            // Look for 3-in-a-row opportunities
            board[land_row][col] = ai_symbol;

            // Check horizontal
            for (int j = 0; j < 4; j++) {
                if (col >= j && col <= j + 3) {
                    int ai_count = 0, empty_count = 0;
                    for (int k = 0; k < 4; k++) {
                        if (board[land_row][j + k] == ai_symbol) {
                            ai_count++;
                        }
                        else if (board[land_row][j + k] == blank) {
                            empty_count++;
                        }
                    }
                    if (ai_count == 3 && empty_count == 1) {
                        score += 100;
                    }
                }
            }

            // Check vertical
            if (land_row <= 2) {
                int ai_count = 0, empty_count = 0;
                for (int k = 0; k < 4; k++) {
                    if (board[land_row + k][col] == ai_symbol) ai_count++;
                    else if (board[land_row + k][col] == blank) empty_count++;
                }
                if (ai_count == 3 && empty_count == 1) {
                    score += 100;
                }
            }

            // Check diagonal
            count_down_right = 0;
            int empty_down_right = 0;
            // Count up-left
            r = land_row;
            c = col;
            int checked = 0;
            while (r >= 0 && c >= 0 && checked < 3) {
                if (board[r][c] == ai_symbol) count_down_right++;
                else if (board[r][c] == blank) empty_down_right++;
                else break; // opponent piece blocks
                r--;
                c--;
                checked++;
            }
            // Count down-right
            r = land_row + 1;
            c = col + 1;
            checked = 0;
            while (r < 6 && c < 7 && checked < 3) {
                if (board[r][c] == ai_symbol) count_down_right++;
                else if (board[r][c] == blank) empty_down_right++;
                else break; // opponent piece blocks
                r++;
                c++;
                checked++;
            }
            if (count_down_right == 3 && empty_down_right == 1) {
                score += 100;
            }

            count_down_left = 0;
            int empty_down_left = 0;
            // Count up-right
            r = land_row;
            c = col;
            checked = 0;
            while (r >= 0 && c < 7 && checked < 3) {
                if (board[r][c] == ai_symbol) count_down_left++;
                else if (board[r][c] == blank) empty_down_left++;
                else break;
                r--;
                c++;
                checked++;
            }
            // Count down-left
            r = land_row + 1;
            c = col - 1;
            checked = 0;
            while (r < 6 && c >= 0 && checked < 3) {
                if (board[r][c] == ai_symbol) count_down_left++;
                else if (board[r][c] == blank) empty_down_left++;
                else break;
                r++;
                c--;
                checked++;
            }
            if (count_down_left == 3 && empty_down_left == 1) {
                score += 100;
            }


            board[land_row][col] = blank;
            // ===================================================================================================== //

            // Block opponent's 3-in-a-row
            board[land_row][col] = opponent_symbol;

            // Check horizontal
            for (int j = 0; j < 4; j++) {
                if (col >= j && col <= j + 3) {
                    int opp_count = 0, empty_count = 0;
                    for (int k = 0; k < 4; k++) {
                        if (board[land_row][j + k] == opponent_symbol) {
                            opp_count++;
                        }
                        else if (board[land_row][j + k] == blank) {
                            empty_count++;
                        }
                    }
                    if (opp_count == 3 && empty_count == 1) {
                        score += 50;
                    }
                }
            }

            // Check vertical
            if (land_row <= 2) {
                int opp_count = 0, empty_count = 0;
                for (int k = 0; k < 4; k++) {
                    if (board[land_row + k][col] == opponent_symbol) opp_count++;
                    else if (board[land_row + k][col] == blank) empty_count++;
                }
                if (opp_count == 3 && empty_count == 1) {
                    score += 50;
                }
            }

            board[land_row][col] = blank;

            // ===================================================================================================== //

            // Prefer center columns
            if (col == 3) {
                score += 20;
            }
            else if (col == 2 || col == 4) {
                score += 10;
            }

            // Look for 2-in-a-row
            board[land_row][col] = ai_symbol;

            for (int j = 0; j < 4; j++) {
                if (col >= j && col <= j + 3) {
                    int ai_count = 0, empty_count = 0;
                    for (int k = 0; k < 4; k++) {
                        if (board[land_row][j + k] == ai_symbol) {
                            ai_count++;
                        }
                        else if (board[land_row][j + k] == blank) {
                            empty_count++;
                        }
                    }
                    if (ai_count == 2 && empty_count == 2) {
                        score += 5;
                    }
                }
            }

            board[land_row][col] = blank;

            // Choose best move
            if (score > best_score) {
                best_score = score;
                y = col;
            }
        }

        // random move
        if (y == -1) {
            for (int col = 0; col < 7; col++) {
                if (board[0][col] == blank) {
                    y = col;
                    break;
                }
            }
        }

        cout << "    " << " Computer chose column: " << y << "\n";
    }

    return new Move<char>(0, y, player->get_symbol());
}

Player<char>** four_in_row_ui::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

bool four_in_row_board::is_win(Player<char> *player) {
    const char sym = player->get_symbol();
    const int rows = 6;
    const int col = 7;

    // Fixed: Simplified to check symbol directly
    auto all_equal = [&](char a, char b, char c, char d) {
        return a == sym && b == sym && c == sym && d == sym;
    };

    // Horizontal
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col - 3; j++) {
            if (all_equal(board[i][j], board[i][j + 1], board[i][j + 2], board[i][j + 3])) {
                return true;
            }
        }
    }

    //Vertical
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < col; j++) {
            if (all_equal(board[i][j], board[i + 1][j], board[i + 2][j], board[i + 3][j])) {
                return true;
            }
        }
    }

    // Diagonal (down-right)
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < col - 3; j++) {
            if (all_equal(board[i][j], board[i + 1][j+1], board[i + 2][j+2], board[i + 3][j + 3])) {
                return true;
            }
        }
    }

    // Diagonal (down-left)
    for (int i = 3; i < rows; i++) {
        for (int j = 0; j < col - 3; j++) {
            if (all_equal(board[i][j], board[i - 1][j+1], board[i - 2][j+2], board[i - 3][j + 3])) {
                return true;
            }
        }
    }

    return false;
}

bool four_in_row_board::is_draw(Player<char>* player) {
    if (is_win(player)) {
        return false;
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == blank_symbol) {
                return false;
            }
        }
    }

    return true;
}

bool four_in_row_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
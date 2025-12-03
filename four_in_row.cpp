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


    if (y < 0 || y > 6) {
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
    // Create player based on type

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

Move<char> *four_in_row_ui::get_move(Player<char> *player) {
    int  x , y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|           " << player->get_name() << "'s TURN               |\n";
        cout << "    " << "|               Symbol: " << player->get_symbol() << "              |\n";
        cout << "    " << "|--------------------------------------|\n";

        cout << "    " << "| Enter your move (row - column:  ): ";
        cin >>  x >> y;


    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();

    }
    return new Move<char>(x, y, player->get_symbol());
}
Player<char>** four_in_row_ui::setup_players() { // select player human or comp
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
    int rows = 6;
    const int col = 7;
    auto all_equal = [&](char a, char b, char c, char d) {
        return a == b && b == c && c == d && a != blank_symbol;
    };



    // vertical
    for (int i = 0; i < col - 4; i++) {
        for (int j = 0; j < rows - 3; j++) {
            if (all_equal(board[i][j] , board[i + 1][j], board[i + 2][j], board[i + 3][j]) && board[i][j] == sym) {
                return true;
            }
        }
    }

    // horizontal
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col - 3; j++) {
            if (all_equal(board[i][j] , board[i][j + 1], board[i][j + 2], board[i][j + 3]) && board[i][j] == sym) {
                return true;
            }
        }
    }

    // diagonal
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < col - 3; j++) {
            if (all_equal(board[i][j], board[i + 1][j+1], board[i + 2][j+2], board[i + 3][j + 3] ) && board[i][j] == sym) {
                return true;
            }
        }
    }

    for (int i = 3; i < rows; i++) {
        for (int j = 0; j < col - 3; j++) {
            if (all_equal(board[i][j], board[i - 1][j+1], board[i - 2][j+2], board[i - 3][j + 3] ) && board[i][j] == sym) {
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



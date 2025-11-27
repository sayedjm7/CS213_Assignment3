#include "WordTicTacToe_UI.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <cctype>

WordTicTacToe_UI::WordTicTacToe_UI() : UI("", 3) {
    display_welcome_message();
}

void WordTicTacToe_UI::display_welcome_message() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|          WORD TIC-TAC-TOE            |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|     Welcome to Word Challenge!       |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|              GAME RULES:             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Players: Place letters A-Z         |\n";
    cout << "    " << "| * Objective: Form valid 3-letter     |\n";
    cout << "    " << "|   words in any direction             |\n";
    cout << "    " << "| * Valid words from dictionary file   |\n";
    cout << "    " << "| * Win: First to form valid word      |\n";
    cout << "    " << "|   horizontally, vertically, or       |\n";
    cout << "    " << "|   diagonally                         |\n";
    cout << "    " << "| * Draw: Board full with no valid     |\n";
    cout << "    " << "|   words formed                       |\n";
    cout << "    " << "|--------------------------------------|\n\n";


}


Move<char>* WordTicTacToe_UI::get_move(Player<char>* player) {

    int x, y;
    string letter;

    Board<char>* game_board = player->get_board_ptr();
    vector<vector<char>> current_board = game_board->get_board_matrix();


    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|           " << player->get_name() << "'s TURN             \n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "| Enter position (row col 0-2): ";


        cin >> x >> y;

        while (x < 0 || x > 2 || y < 0 || y > 2){
            cout << "    " << "|      Please enter numbers 0-2: ";
            cin >> x >> y;
        }
        cout << "    " << "|--------------------------------------|\n\n";

        while (current_board[x][y] != ' ') {
            cout << "    " << "|    Position occupied! Try again.  |\n";
            cout << "    " << "|      Please enter numbers 0-2: ";
            cin >> x >> y;
        }

        cout << "    " << "| Enter letter (A-Z): ";
        cin >> letter;

        while( letter.length() > 1 ){
          if(letter.length() == 1 ){break;}
            cout << "    " << "|    Please enter exactly 1 character: ";
            cin >> letter;
        }

        while (!isalpha(letter[0])) {
            cout << "    " << "|    Please enter a letter (A-Z)!    |\n";
            cin >> letter;
        }
        cout << "    " << "|    Move: (" << x << "," << y << ") with '" << letter[0] << "'     |\n";
        cout << "    " << "|--------------------------------------|\n";
    }


    else {
        Board<char>* board = player->get_board_ptr();
        do {
        // random nun
            x = rand() % 3;
            y = rand() % 3;

        }

        while (board->get_board_matrix()[x][y] != ' ');

        letter = 'A' + (rand() % 26);

        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|    Computer: (" << x << "," << y << ") with '" << letter[0] << "'          |\n";
        cout << "    " << "|--------------------------------------|\n";
    }

    return new Move<char>(x, y, letter[0]);
}

Player<char>* WordTicTacToe_UI::create_player ( string& name, char symbol, PlayerType type ) {
    return new Player < char > (name, symbol, type );
}
#include "WordTicTacToe_UI.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <cctype>

WordTicTacToe_UI::WordTicTacToe_UI() : UI("", 3) {}

void WordTicTacToe_UI::display_welcome_message() {
    cout << "Welcome to Word Tic Tac Toe Game!" << endl;
}


Move<char>* WordTicTacToe_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;

    if (player->get_type() == PlayerType::HUMAN) {





        bool valid_coordinates = false;
        while (!valid_coordinates) {
            cout << player->get_name() << " plays at (  ,  )  with letter:  ";

            if (cin >> x >> y) {

                if (x < 0 || x >= 3 || y < 0 || y >= 3) {
                    cout << "PLEASE ENTER NUM FROM 0 TO 2" << endl;
                } else {
                    valid_coordinates = true;
                }
            } else {
                cout << "Invalid input! Please enter two numbers." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool valid_letter = false;
        while (!valid_letter) {
            cout << "Enter letter: ";
            string input_line;
            getline(cin, input_line);

            stringstream ss(input_line);

            if (ss >> letter) {

                if (!isalpha(letter)) {
                    cout << "Invalid input! Please enter a valid letter (A-Z)." << endl;
                }
                else {
                    string extra_chars;
                    if (ss >> extra_chars) {
                        cout << "Invalid input! Please enter exactly one letter." << endl;
                    }
                    else
                        {
                        letter = toupper(letter);
                        valid_letter = true;
                    }
                }
            } else {
                cout << "Invalid input! Please enter a letter." << endl;
            }
        }















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

        cout << player->get_name() << " plays at (" << x << "," << y << ") with letter: " << letter << endl;
    }

    return new Move<char>(x, y, letter);
}

Player<char>* WordTicTacToe_UI::create_player ( string& name, char symbol, PlayerType type ) {
    return new Player < char > (name, symbol, type );

}
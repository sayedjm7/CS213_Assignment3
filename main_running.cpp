//========== Asignment Info =======
// Name: Zyad Ahmed Abuelyazed Ameen
// ID: 20240208
// Task: game 1, 2 & group games
//
// Name: Omar Osama Othman
// ID: 20240843
// Task: game 7, 8 & game 8 & group games
//
// Name: Omar Khaled Eid
// ID: 20240368
// Task: game 5, 6  & group games
//
// Name: Sayed Mohammed Sayed El-badawy Mohamed
// ID: 20240255
// Task: game 3,4  & group games


#include <iostream>
#include "BoardGame_Classes.h"
#include <cctype>
#include <ctime>
#include <string>
#include "SUS_game.h"
#include "Inverse_XO_Classes.h"
#include "XO_4x4_Game.h"
#include "GameEight.h"
#include "Numerical Tic-Tac-Toe.h"
#include "Obstacles_game.h"
#include "XO_Classes.h"
#include "Word_Tic_Tac_Toe.h"
#include "Word_Tic_Tac_Toe_UI.h"
#include "Diamond Tic-Tac-Toe.h"
#include "5_x_5_Tic_Tac_Toe.h"
#include "5_x_5_Tic_Tac_Toe_UI.h"
#include "four_in_row.h"
#include "Memory_Tic_Tac_Toe.h"
#include <cstdlib>
#include <ctime>
#include "Ultimate_Tic_Tac_Toe.h"
#include "Ultimate_UI.h"




using namespace std;


void SUS() {
    srand(static_cast<unsigned int>(time(0)));

    SUS_UI ui;
    Player<char>** players = ui.setup_players();
    sus_game_board board;

    GameManager<char> manager(&board, players, &ui);
    manager.run();
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}

void Misere_Tic_Tac_Toe() {
    srand(static_cast<unsigned int>(time(0)));  // Seed RNG

    UI<char>* game_ui = new Inverse_XO_UI();

    Board<char>* xo_board = new Inverse_XO_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> x_o_game(xo_board, players, game_ui);

    x_o_game.run();

    delete xo_board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}


void diamond() {
    srand(static_cast<unsigned int>(time(0)));  // Seed RNG

    UI<char>* game_ui = new diamond_XO_UI();

    Board<char>* xo_board = new diamond_XO_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> x_o_game(xo_board, players, game_ui);


    x_o_game.run();


    delete xo_board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;

}

void FourByFour() {
    srand(static_cast<unsigned int>(time(0)));
    XO_GameSeven_UI ui;
    Player<char>** players = ui.setup_players();
    XO_GameSeven_Board board;

    GameManager<char> manager(&board, players, &ui);
    manager.run();

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;

}

void GameEight() {
    srand(static_cast<unsigned int>(time(0)));
    Pry_UI ui;
    Player<char>** players = ui.setup_players();
    Pry_Board board;

    GameManager<char> manager(&board, players, &ui);
    manager.run();
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}



void Numerical_Tic_Tac_Toe() {
    srand(static_cast<unsigned int>(time(0)));
    Numaric_XO_UI ui;
    Player<int>** players = ui.setup_players();
    Numaric_XO_Board board;
    GameManager<int> manager(&board, players, &ui);
    manager.run();
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}

void Obstacle_game() {
    srand(static_cast<unsigned int>(time(0)));
    obstacle_ui ui;
    Player<char>** players = ui.setup_players();
    obstacle_board board;

    GameManager<char> manager(&board, players, &ui);
    manager.run();

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}

void Inf() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    UI<char>* game_ui = new XO_UI();
    Board<char>* xo_board = new X_O_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> x_o_game(xo_board, players, game_ui);
    x_o_game.run();
    delete xo_board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }


    delete[] players;



}

// Word Tic-tac-toe
void WordTicTacToe() {
    srand(static_cast<unsigned int>(time(0)));

    Word_Tic_Tac_Toe* board = new Word_Tic_Tac_Toe();
    Word_Tic_Tac_Toe_UI* ui = new Word_Tic_Tac_Toe_UI();

    Player<char>** players = ui->setup_players();
    GameManager<char> manager(board, players, ui);
    manager.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete board;
    delete ui;
}

//  5x5 Tic Tac Toe
void FiveByFive_Game() {
    srand(static_cast<unsigned int>(time(0)));
    Five__Five_Board* board = new Five__Five_Board();
    Five_And_Five_UI* ui = new Five_And_Five_UI();
    Player<char>** players = ui->setup_players();
    GameManager<char> manager(board, players, ui);
    manager.run();
    // Cleanup
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete board;
    delete ui;
}


void Ultimate_Tic_Tac_Toe() {
    srand(static_cast<unsigned int>(time(0)));
    Ultimate_UI ui;
    ui.display_welcome_message();

    Player<char>** players = ui.setup_players();

    Ultimate_Board board;
    ui.set_ultimate_board(&board);
    players[0]->set_board_ptr(&board);
    players[1]->set_board_ptr(&board);
    Player<char>* playerArray[2] = { players[0], players[1] };
    GameManager<char> gameManager(&board, playerArray, &ui);
    gameManager.run();
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    delete[] players;

}

void four_in_row() {
    srand(static_cast<unsigned int>(time(0)));

    four_in_row_board* board = new four_in_row_board();
    four_in_row_ui* ui = new four_in_row_ui();

    Player<char>** players = ui->setup_players();
    GameManager<char> manager(board, players, ui);
    manager.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete board;
    delete ui;
}

void Memory_game() {
    srand(static_cast<unsigned int>(time(0)));

    memory_ui ui;
    Player<char>** players = ui.setup_players();
    memory_board board;

    GameManager<char> manager(&board, players, &ui);
    manager.run();
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}



void ava() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|            GAME SELECTION            |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|  1.      SUS Game                    |\n";
    cout << "    " << "|  2.      Misere Tic-Tac-Toe          |\n";
    cout << "    " << "|  3.      4x4 Tic-Tac-Toe             |\n";
    cout << "    " << "|  4.      Pyramid Game                |\n";
    cout << "    " << "|  5.      Numerical Tic-Tac-Toe       |\n";
    cout << "    " << "|  6.      Obstacle Game               |\n";
    cout << "    " << "|  7.      Infinity Tic-Tac-Toe        |\n";
    cout << "    " << "|  8.      WordTicTacToe_Board         |\n";
    cout << "    " << "|  9.      Four_in_A_Row               |\n";
    cout << "    " << "|  10.     Memory_Tic_Tac_Toe          |\n";
    cout << "    " << "|  11.     5 x 5 Tic Tac Toe           |\n";
    cout << "    " << "|  12.     Ultimate Tic Tac Toe        |\n";
    cout << "    " << "|  13.     Diamond Tic Tac Toe         |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "Enter your choice (1-13): ";


}

void start() {
    cout << string(49, '=') << "\n";
    cout << "         Welcome to the Gaming Paradise!   " << "\n";
    cout << string(49, '=') << "\n";
}

void again() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|            GAME COMPLETED!           |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| 1. Play Same Game Again              |\n";
    cout << "    " << "| 2. Return to Game Selection          |\n";
    cout << "    " << "| 3. Exit Game Center                  |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "Enter your choice (1-3): ";
}

int main() {
    start();
    bool playAgain = true;
    while (playAgain) {
        ava();
        int game_choice;

        cin >> game_choice;
        bool same_game = true;
        while (same_game) {
            switch (game_choice) {
            case 1:
                SUS();
                break;
            case 2:
                Misere_Tic_Tac_Toe();
                break;
            case 3:
                FourByFour();
                break;
            case 4:
                GameEight();
                break;
            case 5:
                Numerical_Tic_Tac_Toe();
                break;
            case 6:
                Obstacle_game();
                break;
            case 7:
                Inf();
                break;
            case 8:
                WordTicTacToe();
                break;
            case 9:
                four_in_row();
                break;
            case 10:
                Memory_game();
                break;
            case 11:
                FiveByFive_Game();
                break;
            case 12:
                Ultimate_Tic_Tac_Toe();
                break;
            case 13:
                diamond();
                break;
            default:
                cout << "    |------------------------------------------|\n";
                cout << "    |            INVALID SELECTION             |\n";
                cout << "    |------------------------------------------|\n";
                cout << "    |    Please enter a number from 1 to 13    |\n";
                cout << "    |------------------------------------------|\n";
                cout << "      Choice: ";
                cin >> game_choice;
                continue;

            }
            cout << "\n           Press Enter to return to main menu...";
            cin.ignore();
            cin.get();
            again();
            int comp_choice;
            cin >> comp_choice;
            do {
                if (comp_choice <= 3 && comp_choice >= 1) {
                    break;
                }
                cout << "    |------------------------------------------|\n";
                cout << "    |            INVALID SELECTION             |\n";
                cout << "    |------------------------------------------|\n";
                cout << "    |    Please enter a number from 1 to 3     |\n";
                cout << "    |------------------------------------------|\n";
                cout << "    Choice: ";
                cin >> comp_choice;
            } while (comp_choice < 1 || comp_choice > 3);
            if (comp_choice == 1)
            {
                continue;
            }
            if (comp_choice == 2)
            {
                break;
            }
            if (comp_choice == 3)
            {
                same_game = false;
                playAgain = false;
                cout << "    |------------------------------------------|\n";
                cout << "    |            THANK YOU FOR PLAYING!        |\n";
                cout << "    |------------------------------------------|\n";
                cout << "    |         Hope to see you again soon!      |\n";
                cout << "    |------------------------------------------|\n";
            }

        }
    }
    return 0;
}
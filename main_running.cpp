#include <iostream>
#include "BoardGame_Classes.h"
#include "X_O_4×4_Game.h"
#include "XO_Classes.h"
#include <cctype>
#include <ctime>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include "SUS_game.h"
#include "Inverse_XO_Classes.h"
#include"Numerical Tic-Tac-Toe.h"



using namespace std;

enum class games {
    Infinity,
    FourByFour
};

void Inf () {
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
    srand(static_cast<unsigned int>(time(0)));
    Inverse_XO_UI ui;
    Player<char>** players = ui.setup_players();
    Inverse_XO_Board board;
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
    Player<char>** players = ui.setup_players();
	Numaric_XO_Board board;
    GameManager<char> manager(&board, players, &ui);
    manager.run();
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}

void ava() {
    cout << "Options\n"
         << "1. Infinity\n"
         << "2. FourByFour\n"
         << "3. SUS\n"
         <<"4. Misère Tic Tac Toe\n"
         <<"5.Numerical Tic-Tac-Toe\n";

}
void start() {
    cout << "Welcome in gamer place\n";
}
int main() {

    start();
    ava();
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            Inf();
            break;
        case 2:
            FourByFour();
            break;
        case 3:
            SUS();
            break;
		case 4:
			Misere_Tic_Tac_Toe();
			break;
		case 5:
			Numerical_Tic_Tac_Toe();
            break;
    }

}
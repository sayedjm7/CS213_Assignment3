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
void ava() {
    cout << "Options\n"
         << "1. Infinity\n"
         << "2. FourByFour\n";
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
    }

}
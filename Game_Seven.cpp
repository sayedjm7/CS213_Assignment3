// #include <iostream>
// #include "BoardGame_Classes.h"
// #include "X_O_4×4_Game.h"
// #include <cctype>
// #include <ctime>
// using namespace std;
//
// int main() {
//
//     srand(static_cast<unsigned int>(time(0)));
//
//     XO_GameSeven_UI ui;
//     Player<char>** players = ui.setup_players();
//     XO_GameSeven_Board board;
//
//     GameManager<char> manager(&board, players, &ui);
//     manager.run();
//
//     for (int i = 0; i < 2; ++i) {
//         delete players[i];
//     }
//     delete[] players;
//
//     return 0;
//
//
//
// }
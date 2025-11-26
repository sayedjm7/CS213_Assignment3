#include <iostream>
#include "BoardGame_Classes.h"
#include "X_O_4×4_Game.h"
#include "XO_Classes.h"
#include <cctype>
#include <ctime>
#include <string>
#include "SUS_game.h"
#include "Obstacles_game.h"
#include "Inverse_XO_Classes.h"
#include"Numerical Tic-Tac-Toe.h"
#include "GameEight.h"
#include "WordTicTacToe_Board.h"
#include "WordTicTacToe_UI.h"




using namespace std;

enum class games {
    Infinity,
    FourByFour
};



// Word Tic-tac-toe
void WordTicTacToe() {
    srand(static_cast<unsigned int>(time(0)));

    WordTicTacToe_Board *board = new WordTicTacToe_Board();
    WordTicTacToe_UI *ui = new WordTicTacToe_UI();

    Player<char> **players = ui->setup_players();
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
    // cout << "DONE COMMENT\n";


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

void Obstacle_game(){
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



void ava() {
    cout << "    " << "|--------------------------------------|\n" ;
    cout << "    " << "|            GAME SELECTION            |\n" ;
    cout << "    " << "|--------------------------------------|\n" ;
    cout << "    " << "|  1.      SUS Game                    |\n" ;
    cout << "    " << "|  2.      Misere Tic-Tac-Toe          |\n" ;
    cout << "    " << "|  3.      4x4 Tic-Tac-Toe             |\n" ;
    cout << "    " << "|  4.      Pyramid Game                |\n" ;
    cout << "    " << "|  5.      Numerical Tic-Tac-Toe       |\n" ;
    cout << "    " << "|  6.      Obstacle Game               |\n" ;
    cout << "    " << "|  7.      Infinity Tic-Tac-Toe        |\n" ;
    cout << "    " << "|  8.      WordTicTacToe_Board         |\n" ;
    cout << "    " << "|--------------------------------------|\n" ;
    cout << "    " << "Enter your choice (1-8): ";
}

void start() {
    cout << string(49, '=') << "\n";
    cout << "         Welcome to the Gaming Paradise!   " << "\n";
    cout << string(49, '=') << "\n";
}


int main() {
          start();
          ava();
          int choice;
          cin >> choice;
          switch (choice) {
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

          }
}
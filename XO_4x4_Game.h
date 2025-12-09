#include <iostream>
#include <iomanip>
#include <cctype>
#include <math.h>
#include "BoardGame_Classes.h"
using namespace std;

// Move Class
class XO_Move : public Move<char> {
private:
    int old_x, old_y;
public:
    XO_Move(int oldX, int oldY, int newX, int newY, char symbol);

    int get_old_x();
    int get_old_y();
};

// Board Class
class XO_GameSeven_Board : public Board<char> {
private:
    char blank_symbol = ' ';
public:

XO_GameSeven_Board();

bool update_board(Move<char>* move);

bool is_valid_move(int ox, int oy, int nx, int ny, PlayerType pt);

bool is_win(Player<char>* player);

bool is_draw(Player<char>* player) {return false;}

bool is_lose(Player<char>* player) {return false;}

bool game_is_over(Player<char>* player) {return is_win(player);}
};

// UI Class
class XO_GameSeven_UI : public UI<char> {
private:
    int newX, newY;
    int oldX, oldY;

public:
    XO_GameSeven_UI();
    void display_welcome_message() {
        cout << "\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|           4 x 4 Tic-Tac-Toe          |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|         Welcome to Game Seven!       |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|             GAME RULES               |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|  * Each player has 4 tokens (X/O)    |\n";
        cout << "    " << "|  * Move tokens to adjacent cells     |\n";
        cout << "    " << "|  * WIN: Form 3 consecutive tokens in |\n";
        cout << "    " << "|    - Horizontal rows                 |\n";
        cout << "    " << "|    - Vertical columns                |\n";
        cout << "    " << "|    - Diagonal lines                  |\n";
        cout << "    " << "|--------------------------------------|\n\n";
    }

    bool will_win(Board<char>* board,int& bx,int& by, char sym);

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Move<char>* get_move(Player<char>* player);
};
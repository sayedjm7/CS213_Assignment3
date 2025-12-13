#include <iostream>
#include <iomanip>
#include <cctype>
#include <math.h>
#include "BoardGame_Classes.h"
using namespace std;
class Pry_Board : public Board<char> {
private:
    char black_symbol = ' ';

public:
    Pry_Board();

    bool update_board(Move<char>* move);
    bool is_valid_move(int ox, int oy, int nx, int ny,PlayerType p) override {return false;};
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) {return false;};
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char> *) override;
};

class Pry_UI : public UI<char> {
private:
    int x, y;

public:

    Pry_UI();
    void display_message(string message);
    void display_welcome_message(){
        cout << "\n\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|         WELCOME TO GAME EIGHT        |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|          Pyramid Tic-Tac-Toe         |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|        Three Rows Pyramid:           |\n";
        cout << "    " << "|          - Row 0: 1 cell             |\n";
        cout << "    " << "|          - Row 1: 3 cells            |\n";
        cout << "    " << "|          - Row 2: 5 cells            |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|      Align 3 marks to win in:        |\n";
        cout << "    " << "|       - Horizontal lines             |\n";
        cout << "    " << "|       - Vertical lines               |\n";
        cout << "    " << "|       - Diagonal lines               |\n";
        cout << "    " << "|--------------------------------------|\n\n";
    }
    bool will_win(Board<char>* board,int& bx,int& by,char h_sym);
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
    Player<char>* create_player(string &name, char symbol, PlayerType type);
    Move<char>* get_move(Player<char>* player);
};
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
    bool is_valid_move(int ox, int oy, int nx, int ny) override {
        return false;};
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) {return false;};
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char> *) override;

};

class Pry_UI : public UI<char> {
private:
    int x, y;
public:
    void display_welcome_message(){
        cout << "========================================\n"
             << "          Pyramid Tic-Tac-Toe\n"
             << "========================================\n"
             << "          Welcome to Game Eight!        \n"
             << "========================================\n\n"
             << "    GAME RULES:\n"
             << "*- A pyramid-shaped board with 3 rows:\n"
             << "   Top: 1 square\n"
             << "   Middle: 3 squares\n"
             << "   Base: 5 squares\n"
             << "*- WINNING: Align 3 consecutive marks in:\n"
             << "   - ROW (horizontal)\n"
             << "   - COLUMN (vertical)\n"
             << "   - DIAGONAL (diagonal)\n"
             << "========================================\n\n";
    }

    Pry_UI();
    void display_message(string message);
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
    Player<char>* create_player(string &name, char symbol, PlayerType type);
    Move<char>* get_move(Player<char>* player);
};

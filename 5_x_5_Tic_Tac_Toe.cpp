#include <iostream>
#include <vector>
#include "5_x_5_Tic_Tac_Toe.h"
using namespace std;

Five__Five_Board::Five__Five_Board() : Board(5, 5)
{
    num_moves = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            board[i][j] = ' ';
        }
    }
}


bool Five__Five_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 5 && x >= 0 && y < 5 && y >= 0) || (board[x][y] != ' '))
        return false;

    board[x][y] = mark;
    num_moves++;
    return true;
}

int Five__Five_Board::CountOFSeq(char sym) {
    int count = 0;

    // Horizontal seq
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == sym && board[i][j+1] == sym && board[i][j+2] == sym)
                count++;
        }
    }

    // Vertical
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == sym && board[i+1][j] == sym && board[i+2][j] == sym)
                count++;
        }
    }

    // Diagonal >>>> 1
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == sym && board[i+1][j+1] == sym && board[i+2][j+2] == sym)
                count++;
        }
    }

    // Diagonal >>>>>> 2
    for (int i = 0; i < 3; i++) {
        for (int j = 2; j < 5; j++) {
            if (board[i][j] == sym && board[i+1][j-1] == sym && board[i+2][j-2] == sym)
                count++;
        }
    }

    return count;
}

bool Five__Five_Board::is_win(Player<char>* player) {
    if (num_moves < 24) return false;

    char player_symbol = player->get_symbol();
    char opponent_symbol = (player_symbol == 'X') ? 'O' : 'X';

    int player_seqs = CountOFSeq(player_symbol);
    int opponent_seqs = CountOFSeq(opponent_symbol);

    return player_seqs > opponent_seqs;
}

bool Five__Five_Board::is_lose(Player<char>* player) {
    if (num_moves < 24) return false;

    char player_symbol = player->get_symbol();
    char opponent_symbol = (player_symbol == 'X') ? 'O' : 'X';

    int player_seqs = CountOFSeq(player_symbol);
    int opponent_seqs = CountOFSeq(opponent_symbol);

    return player_seqs < opponent_seqs;
}

bool Five__Five_Board::is_draw(Player<char>* player) {
    if (num_moves < 24) return false;

    return CountOFSeq('X') == CountOFSeq('O');
}

bool Five__Five_Board::game_is_over(Player<char>* player) {
    return num_moves >= 24;
}


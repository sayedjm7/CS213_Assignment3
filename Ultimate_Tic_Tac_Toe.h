#ifndef ULTIMATE_BOARD_H
#define ULTIMATE_BOARD_H

#include "BoardGame_Classes.h"

class Ultimate_Board : public Board<char> {
private:
    char mainGrid[3][3];
    char smallGrids[3][3][3][3];
    int lastSmallRow, lastSmallCol;
    bool isNextBoardForced;

public:
    Ultimate_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool get_is_next_board_forced() const { return isNextBoardForced; }
    std::pair<int, int> get_next_board() const {
        return {lastSmallRow, lastSmallCol};
    }

    bool is_small_board_completed(int br, int bc) const {
        if (br < 0 || br >= 3 || bc < 0 || bc >= 3) return true;
        return mainGrid[br][bc] != ' ';
    }

    bool is_small_board_available(int br, int bc) const {
        return !is_small_board_completed(br, bc);
    }

    bool is_cell_empty(int x, int y) const {
        if (x < 0 || x >= 9 || y < 0 || y >= 9) return false;
        return board[x][y] == ' ';
    }

    char get_cell(int x, int y) const {
        if (x < 0 || x >= 9 || y < 0 || y >= 9) return ' ';
        return board[x][y];
    }

    char get_small_board_status(int br, int bc) const {
        if (br < 0 || br >= 3 || bc < 0 || bc >= 3) return ' ';
        return mainGrid[br][bc];
    }

    void display_main_board() const;

};

#endif
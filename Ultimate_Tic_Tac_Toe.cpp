#include "Ultimate_Tic_Tac_Toe.h"
#include <iostream>
using namespace std;

Ultimate_Board::Ultimate_Board() : Board<char>(9, 9) {
    for (int br = 0; br < 3; br++) {
        for (int bc = 0; bc < 3; bc++) {
            mainGrid[br][bc] = ' ';
            for (int sr = 0; sr < 3; sr++) {
                for (int sc = 0; sc < 3; sc++) {
                    smallGrids[br][bc][sr][sc] = ' ';
                    board[br*3 + sr][bc*3 + sc] = ' ';
                }
            }
        }
    }
    lastSmallRow = lastSmallCol = -1;
    isNextBoardForced = false;
    n_moves = 0;
}
bool Ultimate_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 9 || y < 0 || y >= 9) {
        return false;
    }

    int bigR = x / 3;
    int bigC = y / 3;
    int smallR = x % 3;
    int smallC = y % 3;

    if (is_small_board_completed(bigR, bigC)) {
        return false;
    }


    if (smallGrids[bigR][bigC][smallR][smallC] != ' ') {
        return false;
    }


    if (isNextBoardForced && lastSmallRow != -1 && lastSmallCol != -1) {
        if (is_small_board_available(lastSmallRow, lastSmallCol)) {
            if (bigR != lastSmallRow || bigC != lastSmallCol) {
                return false;
            }
        }
    }

    smallGrids[bigR][bigC][smallR][smallC] = symbol;
    board[x][y] = symbol;

    bool won = false;

    for (int r = 0; r < 3; r++) {
        if (smallGrids[bigR][bigC][r][0] == symbol &&
            smallGrids[bigR][bigC][r][1] == symbol &&
            smallGrids[bigR][bigC][r][2] == symbol) {
            won = true;
            break;
        }
    }

    for (int c = 0; c < 3; c++) {
        if (smallGrids[bigR][bigC][0][c] == symbol &&
            smallGrids[bigR][bigC][1][c] == symbol &&
            smallGrids[bigR][bigC][2][c] == symbol) {
            won = true;
            break;
        }
    }

    if (smallGrids[bigR][bigC][0][0] == symbol &&
        smallGrids[bigR][bigC][1][1] == symbol &&
        smallGrids[bigR][bigC][2][2] == symbol) {
        won = true;
    }

    if (smallGrids[bigR][bigC][0][2] == symbol &&
        smallGrids[bigR][bigC][1][1] == symbol &&
        smallGrids[bigR][bigC][2][0] == symbol) {
        won = true;
    }

    if (won) {
        mainGrid[bigR][bigC] = symbol;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[bigR*3 + i][bigC*3 + j] = symbol;
            }
        }
    } else {
        bool isFull = true;
        for (int i = 0; i < 3 && isFull; i++) {
            for (int j = 0; j < 3; j++) {
                if (smallGrids[bigR][bigC][i][j] == ' ') {
                    isFull = false;
                    break;
                }
            }
        }

        if (isFull) {
            mainGrid[bigR][bigC] = 'D';
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    board[bigR*3 + i][bigC*3 + j] = '=';
                }
            }
        }
    }

    lastSmallRow = smallR;
    lastSmallCol = smallC;

    if (lastSmallRow >= 0 && lastSmallCol >= 0) {
        if (is_small_board_completed(lastSmallRow, lastSmallCol)) {
            isNextBoardForced = false;
        } else {
            isNextBoardForced = true;
        }
    }

    n_moves++;
    return true;
}

bool Ultimate_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    for (int i = 0; i < 3; i++) {
        if (mainGrid[i][0] == sym && mainGrid[i][1] == sym && mainGrid[i][2] == sym) {
            display_main_board();
            return true;
        }

        if (mainGrid[0][i] == sym && mainGrid[1][i] == sym && mainGrid[2][i] == sym) {
            display_main_board();
            return true;
        }

    }

    if (mainGrid[0][0] == sym && mainGrid[1][1] == sym && mainGrid[2][2] == sym) {
        display_main_board();
        return true;
    }

    if (mainGrid[0][2] == sym && mainGrid[1][1] == sym && mainGrid[2][0] == sym) {
        display_main_board();
        return true;
    }

    return false;
}

bool Ultimate_Board::is_draw(Player<char>* player) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (mainGrid[i][j] == ' ') return false;
        }
    }
    return !is_win(player);
}

bool Ultimate_Board::is_lose(Player<char>* player) {
    char sym = player->get_symbol();
    char oppSym = (sym == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; i++) {
        if (mainGrid[i][0] == oppSym && mainGrid[i][1] == oppSym && mainGrid[i][2] == oppSym)
            return true;
        if (mainGrid[0][i] == oppSym && mainGrid[1][i] == oppSym && mainGrid[2][i] == oppSym)
            return true;
    }

    if (mainGrid[0][0] == oppSym && mainGrid[1][1] == oppSym && mainGrid[2][2] == oppSym)
        return true;
    if (mainGrid[0][2] == oppSym && mainGrid[1][1] == oppSym && mainGrid[2][0] == oppSym)
        return true;

    return false;
}

bool Ultimate_Board::game_is_over(Player<char>* player) {

    return is_win(player) || is_draw(player) || is_lose(player);
}

void Ultimate_Board::display_main_board() const {
    cout << "\n\n";
    cout << "           " << string(51, '=') << "\n";
    cout << "           |              ULTIMATE TIC-TAC-TOE               |\n";
    cout << "           |                 MAIN BOARD                      |\n";
    cout << "           " << string(51, '=') << "\n\n";

    cout << "                0                     1                     2\n";
    cout << "    |-----------------------------------------------------------------|\n";

    for (int bigRow = 0; bigRow < 3; bigRow++)
    {
        if (bigRow > 0)
        {
            cout << "    |                     |                     |                     |\n";
            cout << "    |---------------------|---------------------|---------------------|\n";
            cout << "    |                     |                     |                     |\n";
        }

        cout << "    |   ---------------   |   ---------------   |   ---------------   |\n";

        for (int smallRow = 0; smallRow < 3; smallRow++)
        {
            cout << "    | ";
            for (int bigCol = 0; bigCol < 3; bigCol++)
            {
                if (bigCol == 0 )
                {
                    cout << " | ";
                }
                if (bigCol == 1 )
                {
                    cout << "  | ";
                }
                if (bigCol == 2 )
                {
                    cout << "  | ";
                }


                if (is_small_board_completed(bigRow, bigCol))
                {
                    char status = mainGrid[bigRow][bigCol];
                    for (int smallCol = 0; smallCol < 3; smallCol++)
                    {
                        if (status == 'D')
                        {
                            cout << " = ";
                        }
                        else
                        {
                            cout << " " << status << " ";
                        }
                        if (smallCol < 2) cout << "| ";
                    }
                }
                else
                    {
                    for (int smallCol = 0; smallCol < 3; smallCol++)
                    {
                        char cell = smallGrids[bigRow][bigCol][smallRow][smallCol];
                        if (cell == ' ')
                        {
                            cout << smallRow << "," << smallCol;
                        } else {
                            cout << " " << cell << " ";
                        }
                        if (smallCol < 2) cout << "| ";
                    }
                }
                cout << " |  |";
            }

            if (smallRow == 1)
            {
                cout << "  " << bigRow << "  ";
            }

            cout << "\n";
        }

        cout << "    |   ---------------   |   ---------------   |   ---------------   |\n";
    }

    cout << "    |-----------------------------------------------------------------|\n";




    cout << "\n\n";
    cout << "           " << string(51, '-') << "\n";
    cout << "           |                GAME INFORMATION                 |\n";
    cout << "           " << string(51, '-') << "\n";



    if (isNextBoardForced && lastSmallRow != -1 && lastSmallCol != -1)
    {
        cout << "           |     NEXT PLAYER must play in BIG board ("
             << lastSmallRow << "," << lastSmallCol << ")    |\n";
        cout << "           |  (Your opponent's move sent you here)         |\n";
    }
    else if (!isNextBoardForced)
    {
        cout << "           |   NEXT PLAYER can play in ANY active big board  |\n";
    }

    cout << "           " << string(51, '-') << "\n";


    cout << "           |                Active Big Boards:                | \n                     ";

    bool anyActive = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!is_small_board_completed(i, j))
            {
                cout << "(" << i << "," << j << ") ";
                anyActive = true;
            }
        }
    }

    if (!anyActive) cout << "None";
    cout << "\n\n";

    cout << "    " << string(70, '=') << "\n";
}
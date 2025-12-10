#include "5_x_5_Tic_Tac_Toe_UI.h"
#include <iostream>
using namespace std;

Five_And_Five_UI::Five_And_Five_UI() : UI<char>("", 3) {
    display_welcome_message();

}

bool check_win_condition_Ai(const vector<vector<char>>& board, char symbol) {

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol)
                {
                    return true;
                }
            }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol)
            {
                return true;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol)
            {
                return true;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 2; j < 5; j++)
        {
            if (board[i][j] == symbol && board[i+1][j-1] == symbol && board[i+2][j-2] == symbol)
            {
                return true;
            }
        }
    }

    return false;
}


Move<char>* Five_And_Five_UI::get_move(Player<char>* player)
{
    int x, y;

    Board<char>* game_board = player->get_board_ptr();
    vector<vector<char>> current_board = game_board->get_board_matrix();

    if (player->get_type() == PlayerType::HUMAN)
    {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|           " << player->get_name() << "'s TURN             |\n";
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "| Enter position (row col 0-4): ";

        cin >> x >> y;


        while (x < 0 || x > 4 || y < 0 || y > 4)
        {
            cout << "    " << "|      Please enter numbers 0-4: ";
            cin >> x >> y;
        }
        cout << "    " << "|--------------------------------------|\n\n";

        while (current_board[x][y] != ' ')
        {
            cout << "    " << "|    Position occupied! Try again.  |\n";
            cout << "    " << "|      Please enter numbers 0-4: ";
            cin >> x >> y;
        }

        cout << "    " << "|    Move: (" << x << "," << y << ")            |\n";
        cout << "    " << "|--------------------------------------|\n";
    }

    else
   {
       Board<char>* board = player->get_board_ptr();
       char computer_symbol = player->get_symbol();
       char human_symbol = (computer_symbol == 'X') ? 'O' : 'X';
       vector<vector<char>> current_board = board->get_board_matrix();


        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (current_board[i][j] == ' ')
                {
                    current_board[i][j] = human_symbol;

                    if (check_win_condition_Ai(current_board, human_symbol))
                    {
                        x = i;
                        y = j;
                        cout << "    " << "|   AI PLAY :(" << x << "," << y << ") |\n";
                        cout << "    " << "|--------------------------------------|\n";
                        return new Move<char>(x, y, computer_symbol);
                    }

                    current_board[i][j] = ' ';
                }
            }
        }


        for (int i = 0; i < 5; i++)
       {
           for (int j = 0; j < 5; j++)
           {
               if (current_board[i][j] == ' ')
               {

                   current_board[i][j] = computer_symbol;

                   if (check_win_condition_Ai(current_board, computer_symbol))
                   {
                    x = i;
                    y = j;
                    cout << "    " << "| AI PLAY :(" << x << "," << y << ")   |\n";
                    cout << "    " << "|--------------------------------------|\n";
                    return new Move<char>(x, y, computer_symbol);
                   }

                   current_board[i][j] = ' ';
               }
           }
       }





       if (current_board[2][2] == ' ')
       {
            x = 2;
            y = 2;
       }

       else if (current_board[0][0] == ' ')
        {
            x = 0;
            y = 0;
        }
       else if (current_board[0][4] == ' ')
        {
            x = 0;
            y = 4;
        }

       else if (current_board[4][0] == ' ')
        {
            x = 4;
            y = 0;
        }

       else if (current_board[4][4] == ' ')
       {
           x = 4;
           y = 4;
       }



        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|  AI PLAY : (" << x << "," << y << ") |\n";
        cout << "    " << "|--------------------------------------|\n";
   }

    return new Move<char>(x, y, player->get_symbol());
}


Player<char>* Five_And_Five_UI::create_player(string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}


void Five_And_Five_UI::display_welcome_message()
{
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|          5x5 TIC-TAC-TOE             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|     Welcome to 5x5 Challenge!        |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|              GAME RULES:             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Board: 5x5 grid (0-4 rows/cols)    |\n";
    cout << "    " << "| * Players: X vs O                    |\n";
    cout << "    " << "| * Objective: Get most three-in-a-row |\n";
    cout << "    " << "|   sequences before board is almost   |\n";
    cout << "    " << "|   full (24 moves)                    |\n";
    cout << "    " << "| * Sequence: 3 same symbols in a row  |\n";
    cout << "    " << "|   (horizontal, vertical, diagonal)   |\n";
    cout << "    " << "| * Game ends after 24 moves           |\n";
    cout << "    " << "| * Winner: Player with most sequences |\n";
    cout << "    " << "| * Draw: Equal number of sequences    |\n";
    cout << "    " << "|--------------------------------------|\n\n";
}
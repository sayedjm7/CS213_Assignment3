#include"Numerical Tic-Tac-Toe.h"
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
//using namespace Board;
using namespace std;
vector<int> oddvector = { 1, 3, 5,7, 9 };
vector<int> evenvector = { 2, 4,6, 8 };
//int nmoves = 0;
//======================================================
//                 Board Implementation
//======================================================

Numaric_XO_Board::Numaric_XO_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& c : row)
            c = 0;
}

bool Numaric_XO_Board::is_there(const vector<int>& nums, int value) {
    return find(nums.begin(), nums.end(), value) != nums.end();
}

bool Numaric_XO_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int value = move->get_symbol();

    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == 0) {
        if (n_moves % 2 == 0) {
          
            if (is_there(oddvector, value)) {
                board[x][y] = value;
                n_moves++;
                auto it = find(oddvector.begin(), oddvector.end(), value);
                if (it != oddvector.end()) oddvector.erase(it);
                return true;
            }
        }
        else {
            if (is_there(evenvector, value)) {
                board[x][y] = value;
                n_moves++;
                auto it = find(evenvector.begin(), evenvector.end(), value);
                if (it != evenvector.end()) evenvector.erase(it);
                return true;
            }
        }
        return false; 
    }
    return false; 
}

bool Numaric_XO_Board::check_three(int a, int b, int c) const {
    auto eq = [&](int a, int b, int c) {
        return a != 0 && b != 0 && c != 0
            && a + b + c == 15;
        };

    for (int i = 0; i < 3; i++) {
        if (eq(board[i][0], board[i][1], board[i][2]))
            return true;
        if (eq(board[0][i], board[1][i], board[2][i]))
            return true;
    }

    if (eq(board[0][0], board[1][1], board[2][2]))
        return true;
    if (eq(board[0][2], board[1][1], board[2][0]))
        return true;

    return false;
}
bool Numaric_XO_Board::is_win(Player<int>* player) {
    if (!check_three(0, 0, 0))
        return false;

    if ((n_moves - 1) % 2 == 0)  
        return player->get_symbol() % 2 == 1;  
    else                         
        return player->get_symbol() % 2 == 0;  
}

bool Numaric_XO_Board::is_lose(Player<int>* player) {
    return is_win(player) == false && check_three(0, 0, 0);
}

bool Numaric_XO_Board::is_draw(Player<int>* player) {
    return n_moves >= 9 && !check_three(0, 0, 0);
}

bool Numaric_XO_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}
//------------------------------------------
// UI
//------------------------------------------
Numaric_XO_UI::Numaric_XO_UI() : UI<int>("", 2) {
    display_welcome_message();
}

void Numaric_XO_UI::display_welcome_message() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|        NUMERICAL TIC-TAC-TOE         |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|      Welcome to Number Battle!       |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|              GAME RULES:             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Players:                           |\n";
    cout << "    " << "|   - Player 1: Uses odd numbers       |\n";
    cout << "    " << "|   - Player 2: Uses even numbers      |\n";
    cout << "    " << "| * Numbers: 1,3,5,7,9 (odd)           |\n";
    cout << "    " << "| * Numbers: 2,4,6,8 (even)            |\n";
    cout << "    " << "| * Objective: Get 3 numbers that      |\n";
    cout << "    " << "|   sum to 15 in a row/column/diagonal |\n";
    cout << "    " << "|--------------------------------------|\n\n";
}

Player<int>* Numaric_XO_UI::create_player(string& name, int symbol, PlayerType type) {
    string playerType = (type == PlayerType::HUMAN ? "Human" : "Computer");
    string numberType = (symbol % 2 == 1 ? "Odd Numbers" : "Even Numbers");

    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|             PLAYER CREATED           |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|  Type:    " << setw(25) << left << playerType << "|\n";
    cout << "    " << "|  Name:    " << setw(25) << left << name << "|\n";
    cout << "    " << "|  Role:    " << setw(25) << left << numberType << "|\n";
    cout << "    " << "|--------------------------------------|\n";
    return new Player<int>(name, symbol, type);

}


Move<int>* Numaric_XO_UI::get_move(Player<int>* player) {
    int x, y, value;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|           " << player->get_name() << "'s TURN                |\n";
        cout << "    " << "|--------------------------------------|\n";
        if (player->get_symbol() % 2 == 1) {
            cout << "    " << "| Available odd numbers: ";
            for (int i = 0; i < oddvector.size(); i++) {
                cout << oddvector[i] << " ";
            }
            cout << "     |\n";
        }
        else{
            cout << "    " << "| Available even numbers: ";
            for (int i = 0; i < oddvector.size(); i++) {
                cout << evenvector[i] << " ";
            }
            cout << "     |\n";
        }
        cout << "    " << "| Enter row (0-2), column (0-2):          ";
        cin >> x >> y;

         cout << "    " << "| Enter the value:          ";
        cin >> value;

        cout << "    " << "|--------------------------------------|\n";
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
      //  if(n_moves)
        value= (rand() % 9) + 1;
    }
    //cin >> x >> y >> value;

    return new Move<int>(x, y, value);
}
Player<int>** Numaric_XO_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameOdd = get_player_name("Odd Numbers Player");
    PlayerType typeOdd = get_player_type_choice("Odd Numbers Player", type_options);
    players[0] = create_player(nameOdd, 1, typeOdd);

    string nameEven = get_player_name("Even Numbers Player");
    PlayerType typeEven = get_player_type_choice("Even Numbers Player", type_options);
    players[1] = create_player(nameEven, 2, typeEven);
    cout << "    " << "|--------------------------------------|\n";

    return players;
}

    
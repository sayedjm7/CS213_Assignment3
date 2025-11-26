#include "BoardGame_Classes.h"
#include "SUS_game.h"
#include "XO_Classes.h"



sus_game_board::sus_game_board() : Board(3, 3) {

    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}


sus_game_board::~sus_game_board() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|              FINAL SCORE             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|  Player S: " << setw(25) << left << p1_score << " |\n";
    cout << "    " << "|  Player U: " << setw(25) << left << p2_score << " |\n";
    cout << "    " << "|--------------------------------------|\n";}

SUS_UI::SUS_UI() : UI<char>("", 3) {
    display_welcome_message();
}

void SUS_UI::display_welcome_message() {
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|               SUS GAME               |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|            Welcome to SUS!           |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|              GAME RULES:             |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "| * Players:                           |\n";
    cout << "    " << "|   - Player 1: Places 'S' only        |\n";
    cout << "    " << "|   - Player 2: Places 'U' only        |\n";
    cout << "    " << "| * Scoring: 1 point per S-U-S sequence|\n";
    cout << "    " << "| * Winner: Most S-U-S sequences       |\n";
    cout << "    " << "|--------------------------------------|\n\n\n";

}
bool sus_game_board::update_board(Move<char> *move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = mark;
            count_sus_number(x, y , mark);
        }
        return true;
        }
    return false;
}

void sus_game_board::count_sus_number(int x, int y, char sym) { // calculate the points
    num = 0;
    auto sus_completed = [&](char a, char b, char c) {
        return (a == 'S' && b == 'U' && c == 'S');
    };

    // Horizontal
    if (sus_completed(board[x][0], board[x][1], board[x][2])) {
        num++;
    }




    // Vertical
    if (sus_completed(board[0][y], board[1][y], board[2][y])) {
        num++;
    }



    // Diagonal 1
    if (x == 0 && y==0 || x == 1 && y == 1 || x == 2 && y==2) {
        if (sus_completed(board[0][0], board[1][1], board[2][2])) {

            num++;
        }
    }


    // Diagonal 2
    if (x == 0 && y==2 || x == 1 && y == 1 || x == 2 && y==0) {
        if (sus_completed(board[0][2], board[1][1], board[2][0])) {
            num++;
        }
    }

    if(sym == 'S') // assuming P1 uses 'S'
        p1_score += num;
    else if(sym == 'U') // or 'U' if P2 uses 'U'
        p2_score += num;

}





Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type

    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|             PLAYER CREATED           |\n";
    cout << "    " << "|--------------------------------------|\n";
    cout << "    " << "|  Type:    " << setw(25) << left
         << (type == PlayerType::HUMAN ? "Human" : "Computer") << " |\n";
    cout << "    " << "|  Name:    " << setw(25) << left << name << " |\n";
    cout << "    " << "|  Symbol:  " << setw(25) << left << symbol << " |\n";
    cout << "    " << "|--------------------------------------|\n\n\n";

    return new Player<char>(name, symbol, type);
}

Move<char> *SUS_UI::get_move(Player<char> *player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "    " << "|--------------------------------------|\n";
        cout << "    " << "|           " << player->get_name() << "'s TURN               |\n";
        cout << "    " << "|               Symbol: " << player->get_symbol() << "              |\n";
        cout << "    " << "|--------------------------------------|\n";

        cout << "    " << "| Enter your move (row col 0-2): ";
        cin >> x >> y;


    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();

    }
    return new Move<char>(x, y, player->get_symbol());
}
Player<char>** SUS_UI::setup_players() { // select player human or comp
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameS = get_player_name("Player S");
    PlayerType typeS = get_player_type_choice("Player S", type_options);
    players[0] = create_player(nameS, 'S', typeS);

    string nameU = get_player_name("Player U");
    PlayerType typeU = get_player_type_choice("Player U", type_options);
    players[1] = create_player(nameU, 'U', typeU);

    return players;
}



bool sus_game_board::is_win(Player<char> *player) { // return true if s wins , return false if u wins
    if (!game_is_over(nullptr)) return false;  // Only after board full
    return p1_score > p2_score;
}
bool sus_game_board::is_draw(Player<char>* player) {
    return game_is_over(nullptr) && p1_score == p2_score;

}

bool sus_game_board::game_is_over(Player<char>* player) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (board[i][j] == blank_symbol)
                return false;
    return true;
}




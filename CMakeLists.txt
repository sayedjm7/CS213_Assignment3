cmake_minimum_required(VERSION 3.20)

project(CS213_Assignment3_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS213_Assignment3_2
        BoardGame_Classes.h
        GameEight.cpp
        GameEight.h
        Inverse_XO_Classes.cpp
        Inverse_XO_Classes.h
        main_running.cpp
        "Numerical Tic-Tac-Toe.cpp"
        "Numerical Tic-Tac-Toe.h"
        Obstacle_game.cpp
        Obstacles_game.h
        SUS_game.cpp
        SUS_game.h
        WordTicTacToe_Board.cpp
        WordTicTacToe_Board.h
        WordTicTacToe_UI.cpp
        WordTicTacToe_UI.h
        X_O_4x4_Game.h
        XO_Classes.cpp
        XO_Classes.h
        XO_Demo.cpp "Diamond Tic-Tac-Toe.h" "Diamond Tic-Tac-Toe.cpp")

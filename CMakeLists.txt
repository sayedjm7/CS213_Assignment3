cmake_minimum_required(VERSION 4.0)
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
        Word_Tic_Tac_Toe.cpp
        Word_Tic_Tac_Toe.h
        Word_Tic_Tac_Toe_UI.cpp
        Word_Tic_Tac_Toe_UI.h
        X_O_4x4_Game.h
        XO_Classes.cpp
        XO_Classes.h
        XO_Demo.cpp
        5_x_5_Tic_Tac_Toe.cpp
        5_x_5_Tic_Tac_Toe.h
        5_x_5_Tic_Tac_Toe_UI.cpp
        5_x_5_Tic_Tac_Toe_UI.h
        four_in_row.h
        four_in_row.cpp
        Ultimate_Tic_Tac_Toe.cpp
        Ultimate_UI.cpp
        Ultimate_Tic_Tac_Toe.h
        Ultimate_UI.h
        Memory_Tic_Tac_Toe.cpp
        Diamond_Tic_Tac_Toe.cpp
        Diamond_Tic_Tac_Toe.h
        X_O_4x4_Game.cpp
        X_O_4x4_Game.h
)

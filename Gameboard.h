#pragma once

#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

class GameBoard {
    protected: 
        int rows;
        int columns;
        int maxTreasures;
        int playerTreasures;
        int computerTreasures;
        std::vector<std::vector<int>> board;
        std::vector<std::vector<char>> display;
        std::string prompt = 
                            "Welcome to the Treasure Hunt Game!\n"
                            "You will be playing against the computer.\n"
                            "You will be asked to enter the coordinates of your hidden treasures.\n"
                            "The computer will randomly place its treasures on the board.\n"
                            "You will then take turns looking for each other's hidden treasures.\n"
                            "The first player to find all of the opponent's treasures wins!\n"
                            "Now, let's place your treasures on the board.\n"
                            "You can place up to 5 treasures on the board.\n\n"
                            "Please enter the coordinates of your treasures (e.g., A1, B2, etc.).\n\n";

    public:
        GameBoard(int rows = 5, int columns = 5, int maxTreasures = 5) : 
            rows(rows), columns(columns), maxTreasures(maxTreasures), playerTreasures(maxTreasures), computerTreasures(maxTreasures), 
            board(rows, std::vector<int>(columns, 0)), display(rows, std::vector<char>(columns, '.')) {};
        int getPlayerTreasures() const { return playerTreasures; }
        int getComputerTreasures() const { return computerTreasures; }
        void clearBoard();
        void displayLegend();
        void printBoard();
        void displayPrompt();
        bool foundTreasure(int row, int column, int value);
        void playerSetup();
        void computerSetup();
        void playerTurn();
        void computerTurn();
        void outputResult(); 
};

#endif  
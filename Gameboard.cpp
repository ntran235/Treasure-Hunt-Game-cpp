#include "Gameboard.h"

// The possible values for the board
int defaultValue = 0;
int playerValue = 1;
int computerValue = 2;

// The possible legend values for the board
char defaultChar = '.';
char playerTreasure = '$';
char playerMiss = 'M';
char playerHit = 'H';
char computerHit = 'X';
char computerMiss = 'O';

void GameBoard::displayLegend() {
    std::ifstream legendFile("legend.txt");// Open the legend.txt file

    if (!legendFile) {
        std::cerr << "Error opening legend file.\n";
        return;// If the file cannot be opened, display an error message
    }
    
    std::string line;
    while (std::getline(legendFile, line)) {
        std::cout << line << "\n";// Read and display each line of the legend
    }

    legendFile.close();// Close the legend file
}

void GameBoard::clearBoard() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = defaultValue;
            display[i][j] = defaultChar;
        } 
    }
}// Clear the board by setting all values to default

void GameBoard::printBoard() {
    displayLegend();// Display the legend for easy reference
    std::cout << "  ";
    for (int j = 0; j < columns; ++j) {// Print the column numbers (0 - 4)
        std::cout << j << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < rows; ++i) {// Print the row letters (A - E)
        std::cout << char (i + 65) << " ";
        for (int j = 0; j < columns; ++j) {// Print the board
            std::cout << display[i][j] << " ";
        }
        std::cout << "\n";
    }
}// Print the board with the current state of the game

void GameBoard::displayPrompt() {
    std::cout << prompt;
}// Display the game prompt to the player

void GameBoard::playerSetup() {// Set up the player's treasure positions
    int treasure = 0;
    while(treasure < maxTreasures){// Loop until the player has placed all treasures
        std::string input;
        std::cout << "Enter the coordinates of your treasure (e.g., A1, B2, etc.): ";
        std::cin >> input;// Get the input from the player

        char rowChar = input[0];
        char columnChar = input[1];
        int row = rowChar - 'A';
        int column = columnChar - '0';

        if (input.length() != 2 || row < 0 || row >= rows || column < 0 || column >= columns) {
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }// Check if the input is valid and within the board limits

        if (board[row][column] == playerValue) {
            std::cout << "You already placed a treasure there. Try again.\n";
            continue;
        }// Check if the player already placed a treasure in that spot
        board[row][column] = playerValue;
        display[row][column] = playerTreasure;
        printBoard();
        ++treasure;// Increment the number of treasures placed
    }
    std::cout << " -----------------------\n";
}

void GameBoard::computerSetup() {// Set up the computer's treasure positions randomly
    for (int i = 0; i < maxTreasures; ++i) {
        int row = rand() % rows;// Generate a random row
        int column = rand() % columns;// Generate a random column
        if (board[row][column] == defaultValue) {// Check if the spot is empty
            board[row][column] = computerValue;// Place the treasure
        } else {
            --i; // Retry if the spot is already taken
        }
    }
}

void GameBoard::playerTurn() {// Start of game after hiding treasures. Handle the player's turn 
    std::cout << "Player's turn:\n";
    std::cout << "Choose the coordinates of your attack (e.g., A1, B2, etc.): ";
    bool guessing = true;// Flag to control the guessing loop

    while (guessing) {// Loop until the player makes a valid guess
        std::string input;
        std::cin >> input;

        if (input.length() != 2) {// Check if the input is valid
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (board[input[0] - 'A'][input[1] - '0'] == playerValue) {
            std::cout << "You hid your own treasure in this spot. Try again.\n";
            continue;
        }// Check if the player is trying to hit their own treasure

        char rowChar = input[0];
        char columnChar = input[1];
        int row = rowChar - 'A';
        int column = columnChar - '0';
        if (foundTreasure(row, column, computerValue)) {// Check if the player found a treasure
            std::cout << "You found a treasure at " << input << "!\n";
            board[row][column] = defaultValue; // Remove the treasure
            display[row][column] = playerHit; // Mark as hit
            --computerTreasures;// Decrease the computer's treasure count
        } else {
            std::cout << "No treasure found at that location.\n";
            display[row][column] = playerMiss; // Mark as miss
        }
        std::cout << " -----------------------\n";
        guessing = false; // End the player's turn after one guess
    }
}

void GameBoard::computerTurn() {// Handle the computer's turn
    std::cout << "Computer's turn:\n";
    bool guessing = true;// Flag to control the guessing loop
    while (guessing) {// Loop until the computer makes a valid guess
        int row = rand() % rows;
        int column = rand() % columns;

        if (board[row][column] == computerValue) {// Check if the computer is trying to hit its own treasure
            continue; // Skip if it's a treasure
        }

        if (foundTreasure(row, column, playerValue)) {// Check if the computer found a treasure
            std::cout << "Computer found your treasure at " << char(row + 65) << column << "!\n";
            board[row][column] = defaultValue; // Remove the treasure
            display[row][column] = computerHit; // Mark as hit
            --playerTreasures;// Decrease the player's treasure count
        } else {
            std::cout << "Computer did not find any treasure.\n";
            display[row][column] = computerMiss; // Mark as miss
        }
        std::cout << " -----------------------\n";
        guessing = false; // End the computer's turn after one valid guess
    }
}

bool GameBoard::foundTreasure(int row, int column, int value) {
    if (row >= 0 && row < rows && column >= 0 && column < columns) {
        if (board[row][column] == value) {
            return true;
        }
    }
    return false;
}// Check if the treasure is found at the given coordinates

void GameBoard::outputResult() {
    std::ofstream resultFile("result.txt");// Open the result.txt file
    if (!resultFile) {//
        std::cerr << "Error opening result file.\n";
        return;
    }// If the file cannot be opened, display an error message

    if (playerTreasures == 0) {// Check if the player has no treasures left
        resultFile << "Computer wins!\n";
    } else {// Check if the computer has no treasures left
        resultFile << "You win!\n";
    }
    resultFile << "Game Over!\n";
    resultFile.close();
}// Output the result of winner of the game to result.txt

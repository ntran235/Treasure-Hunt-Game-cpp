#include "Gameboard.h"
#include <iostream>

int main(){
    GameBoard game;

    game.displayPrompt();// Display the game prompt
    game.clearBoard();// Clear the board
    game.printBoard();// Print the initial board
    game.playerSetup();// take input from the player to set up their treasures
    game.printBoard();// Print the board after player setup
    game.computerSetup();// Set up the computer's treasures randomly
    
    std::cout << "Now it's time to start the game!\n";
    //The game loop continues until one player runs out of treasures
    while (game.getPlayerTreasures() > 0 && game.getComputerTreasures() > 0){
        game.playerTurn();// Player's turn
        game.printBoard();// Print the board after player's turn
        game.computerTurn();// Computer's turn
        game.printBoard();// Print the board after computer's turn
        std::cout << "Amount of treasures left: " << game.getPlayerTreasures() << "\n";
        std::cout << "Computer's treasures left: " << game.getComputerTreasures() << "\n";
        std::cout << " -----------------------\n";
    } 
    std::cout << "Game Over! Check the result in result.txt\n";
    game.outputResult();// Output who won the game to result.txt
    return 0;
}

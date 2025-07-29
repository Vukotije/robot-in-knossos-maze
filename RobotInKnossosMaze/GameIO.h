#pragma once

#include "Field.h"
#include "Maze.h"

#include <iostream>

// This class handles all user input validation, game display,
// file operations, and message presentation for the maze game.
class GameIO {
public:
    // Gets valid maze dimensions from user input
    // Returns true if user wants to quit, false otherwise
    static bool getValidDimensions(int& rows, int& columns);
    
    // Gets valid number of items from user input
    // Returns true if user wants to quit, false otherwise
    static bool getValidItemsNum(int& items_num, int rows, int columns);
    
    // Gets robot movement direction from user input
    // Returns true if user wants to quit, false otherwise
    static bool getRobotMoveDirection(char& direction);

    static void printWelcomeMessage();
    static void printInstructions();
    static void printMaze(const Maze& maze);
    static void printFoggedMaze(const Maze& maze, Field* robot);
    static void printEndMessage(std::string& reason);
    static void printItemDescription(const std::string& description);

    // Displays the maze generation time in milliseconds (as a decimal number)
    static void printMazeGenerationTime(double time);
    
    // Writes the final maze state to a file and includes the game result message
    // If the file cannot be opened, an error message is displayed
    static void writeMazeToFile(const Maze& maze, const std::string& filename, std::string& result_message);

    static const std::string& getQuitMessage();
    static const std::string& getLostMessage();
    static const std::string& getWonMessage();
};
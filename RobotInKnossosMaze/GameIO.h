#pragma once
#include <iostream>
#include "Maze.h"
#include "Field.h"

class GameIO {
public:
    static bool getValidDimensions(int& rows, int& columns);
    static bool getValidItemsNum(int& itemsNum, int rows, int columns);
    static char getRobotMoveDirection(char& direction);

	static void printWelcomeMessage();
	static void printInstructions();
	static void printMazeGenerationTime(long long time);
	static void printMaze(const Maze& maze);
	static void printFoggedMaze(const Maze& maze, Field* robot);
    static void printEndMessage(std::string& reason);
	static void printItemDescription(const std::string& description);

	static void writeMazeToFile(const Maze& maze, const std::string& filename, std::string& result_message);

	static const std::string& getQuitMessage();
	static const std::string& getLostMessage();
	static const std::string& getWonMessage();


};
#pragma once
#include <iostream>
#include "Maze.h"

class GameIO {
public:
    static bool getValidDimensions(int& rows, int& columns);
    static bool getValidItemsNum(int& itemsNum, int rows, int columns);
    static char getRobotMoveDirection(char& direction);

	static void printWelcomeMessage();
	static void printInstructions();
	static void printMazeGenerationTime(long long time);
	static void printMaze(Maze& maze);
    static void printEndMessage(std::string& reason);

	static void writeMazeToFile(const Maze& maze, const std::string& filename, std::string& result_message);

private:
	static const std::string& getQuitMessage();
	static const std::string& getLostMessage();
	static const std::string& getWonMessage();


};


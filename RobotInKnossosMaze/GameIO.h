#pragma once
#include <iostream>
#include "Maze.h"

class GameIO {
public:
    static bool getValidDimensions(int& rows, int& columns);
    static bool getValidItemsNum(int& itemsNum, int rows, int columns);
    static char getRobotMoveDirection();
	static void printWelcomeMessage();
    static void printEndMessage();
	static void printMaze(Maze& maze);
	static void printGenerationTime(long long time);
	static void printInstructions();
	static void writeMazeToFile(const Maze& maze, const std::string& filename, bool won);
};


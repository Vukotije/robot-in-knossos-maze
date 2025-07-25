#pragma once
#include "Maze.h"
#include "Field.h"

class Game
{
public:
	Game(int rows, int columns, int itemsNum);
	~Game();
	void PlaceFields();
	void moveRobot(char direction);
	bool moveMinotaur();
	void GameOver();
	void run();
private:
	Maze maze;
	Field* robot;
	Field* minotaur;
};


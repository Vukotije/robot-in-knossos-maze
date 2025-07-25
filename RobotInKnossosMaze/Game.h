#pragma once
#include "Maze.h"
#include "Field.h"
#include "Item.h"

class Game
{
public:
	Game(int rows, int columns, int items_num);
	~Game();	
	void run();

private:
	Maze maze;
	Field* robot;
	Field* minotaur;
	std::pair<int, Item*> current_item;

	void PlaceFields(int items_num);
	bool moveRobot(char direction);
	bool moveMinotaur();
};


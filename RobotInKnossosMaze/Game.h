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

	void PlaceFields(int items_num);
	bool moveRobot(char direction, std::pair<int, Item*>& current_item);
	bool moveMinotaur(std::pair<int, Item*>& current_item);
};


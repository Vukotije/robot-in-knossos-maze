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
	std::vector<std::pair<int, Item*>> current_items;
	bool has_sword;
	bool has_shield;
	bool has_hammer;
	bool has_fog;

	void PlaceFields(int items_num);
	bool moveRobot(char direction);
	bool moveMinotaur();
	void updateItems();
};


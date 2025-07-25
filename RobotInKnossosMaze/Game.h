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
	std::pair<bool, int> sword_info;
	std::pair<bool, int> shield_info;
	std::pair<bool, int> hammer_info;
	std::pair<bool, int> war_fog_info;

	void PlaceFields(int items_num);
	bool moveRobot(char direction);
	bool moveMinotaur();
	void updateItems();
};


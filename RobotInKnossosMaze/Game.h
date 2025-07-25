#pragma once

#include "Maze.h"
#include "Field.h"
#include "Item.h"

// This class manages the complete game state, including the maze,
// entities, items, and game logic for the Robot in Knossos Maze.
class Game
{
public:
	Game(int rows, int columns, int items_num);
	~Game();
	
	// Starts and runs the main game loop
	void run();

private:
	Maze maze;
	/// Pointer to the robot's current field
	Field* robot;
	/// Pointer to the minotaur's current field
	Field* minotaur;
	
	/// For each item state: {is_active, remaining_turns}
	std::pair<bool, int> sword_info;
	std::pair<bool, int> shield_info;
	std::pair<bool, int> hammer_info;
	std::pair<bool, int> war_fog_info;

	// Places robot, minotaur, entrance, exit, and items in the maze
	// items_num - Number of items to place randomly
	void PlaceFields(int items_num);
	
	// Attempts to move the robot in the specified direction
	// If direction has a wall in front, it will not move but waste a turn
	// Returns true if combat occurred, false otherwise
	bool moveRobot(char direction);
	
	// Moves the minotaur randomly to a valid adjacent position
	// If the robot is in front of the minotaur, it will catch the robot
	// Returns true if combat occurred, false otherwise
	bool moveMinotaur();
	
	// Updates the duration of active item effects
	void updateItems();
};

enum class GameOverReason {
    QUIT,
    WON,
    LOST,
};

// Constants for the Robot in Knossos Maze game
// This header defines global constants for maze dimensions, item limits,
// and provides utility functions for calculating game parameters.

#pragma once

// Min allowed maze size for rows and columns
const int MIN_MAZE_SIZE = 15;
// Maximum so the console can display the maze properly
const int MAX_MAZE_SIZE = 170;

// Minimum number of items that must be placed in the maze
const int MIN_ITEMS_NUM = 3;

// Maximum fraction of available empty spaces that can contain items
const float MAX_ITEMS_FRACTION = 0.05f;

// Calculates the maximum number of items that can be placed in a maze
// as a fraction of the total empty spaces
// Custom logic for determining max number of items:
// min_blocks = 2 * (columns + rows)
// matrix_spaces = columns * rows
// max_empty_spaces = columns * rows - 2 * (columns + rows);
inline int get_max_items_num(int rows, int columns)
{
    return static_cast<int>(MAX_ITEMS_FRACTION * (columns * rows - 2 * (columns + rows)));
}

// War of Fog visibility range
const int WAR_FOG_RANGE = 3;

// Extra paths fraction for maze generation
const float EXTRA_PATHS_FRACTION = 0.05f;

// Fraction of maze possible where minotaur can be placed
const float MINOTAUR_PLACEMENT_FRACTION = 0.33f;
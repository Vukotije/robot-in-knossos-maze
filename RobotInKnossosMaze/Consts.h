// Constants and utility functions for the Robot in Knossos Maze game
// This header defines global constants for maze dimensions, item limits,
// and provides utility functions for calculating game parameters.

#pragma once

// Min/Max allowed maze size for rows and columns
constexpr int MIN_MAZE_SIZE = 15;
constexpr int MAX_MAZE_SIZE = 100;

// Minimum number of items that must be placed in the maze
constexpr int MIN_ITEMS_NUM = 3;

// Maximum fraction of available empty spaces that can contain items
constexpr float MAX_ITEMS_FRACTION = 0.05f;

// Calculates the maximum number of items that can be placed in a maze
// as a fraction of the total empty spaces
// Custom logic for determining max number of items:
// min_blocks = 2 * (columns + rows)
// matrix_spaces = columns * rows
// max_empty_spaces = columns * rows - 2 * (columns + rows);
const int getMaxItemsNum(int rows, int columns) {
    return static_cast<int>(MAX_ITEMS_FRACTION * (columns * rows - 2 * (columns + rows)));
}
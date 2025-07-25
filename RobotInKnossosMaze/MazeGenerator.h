#pragma once
#include <vector>
#include <utility>
#include "Maze.h"

 // This class provides static methods for generating maze layouts
 // using depth-first search algorithm with randomized paths,
 // ensuring there's always a solvable path.
class MazeGenerator {
public:
    static void generate(Maze& maze);
    
private:
    // Recursive DFS algorithm to carve paths in the maze
    static void carveMazeDFS(int x, int y, int rows, int cols,
        Maze& matrix, std::vector<std::pair<int, int>>& directions);
};

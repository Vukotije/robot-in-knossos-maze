#pragma once
#include <vector>
#include <utility>
#include "Maze.h"

class MazeGenerator {
public:
    static void generate(Maze& maze);
private:
    static void carveMazeDFS(int x, int y, int rows, int cols,
        Maze& matrix, std::vector<std::pair<int, int>>& directions);
};

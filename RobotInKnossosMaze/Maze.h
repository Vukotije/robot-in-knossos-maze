#pragma once

#include <vector>
#include <string>
#include "Field.h"

class Maze {
public:
    Maze(int rows, int columns, int numItems);
    void print() const;

private:
    int rows, columns;
    std::vector<std::vector<Field>> matrix;
    void generateMaze();
};
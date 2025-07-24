#pragma once
#include <vector>
#include "Field.h"
#include <iostream>

class Maze {
public:
    Maze(int rows, int columns, int numItems);
    ~Maze();
    int getRows() const;
    int getColumns() const;
    std::vector<std::vector<Field*>>& getMatrix();

    friend std::ostream& operator<<(std::ostream& os, const Maze& maze);

private:
    int rows, columns;
    std::vector<std::vector<Field*>> matrix;
};
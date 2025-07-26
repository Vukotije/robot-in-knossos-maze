#pragma once

#include "Field.h"

#include <iostream>
#include <vector>

// This class represents the complete maze structure
// containing all fields, and items arranged in a matrix.
class Maze {
public:
    Maze(int rows, int columns, int num_items);
    ~Maze();
    int getRows() const;
    int getColumns() const;
    
    // Provides access to a row of fields (non-const)
    std::vector<Field*>& operator[](int index);
    // Provides access to a row of fields (const)
    std::vector<Field*> const& operator[](int index) const;
    // Stream output operator for printing the maze
    friend std::ostream& operator<<(std::ostream& os, const Maze& maze);

private:
    int rows_;
    int columns_;
    std::vector<std::vector<Field*>> matrix_;
};
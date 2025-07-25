#pragma once
#include "Field.h"
#include <vector>
#include <iostream>


 // This class represents the complete maze structure
 // containing all fields, and items arranged in a matrix.
class Maze {
public:
    Maze(int rows, int columns, int numItems);
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
    int rows, columns;
    std::vector<std::vector<Field*>> matrix;
};
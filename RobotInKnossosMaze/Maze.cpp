#include "Maze.h"
#include <iostream>

using std::vector;
using std::cout;

Maze::Maze(int rows, int columns, int numItems) :
    rows(rows), columns(columns), matrix(rows, vector<Field>(columns)) 
{
    generateMaze();
}

void Maze::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << matrix[i][j].getSymbol();
        }
        cout << '\n';
    }
}

void Maze::generateMaze() {
    // TODO: Implement generation algorithm
}

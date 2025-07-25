// Implementation of the Maze class
#include "Maze.h"
#include <iostream>
#include "MazeGenerator.h"

using std::vector;
using std::ostream;

Maze::Maze(int rows, int columns, int num_items)
    : rows(rows), columns(columns), matrix(rows, vector<Field*>(columns)) {
    MazeGenerator::generate(*this);
}

Maze::~Maze() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            delete matrix[i][j];
        }
    }
}

int Maze::getRows() const
{
    return rows;
}

int Maze::getColumns() const
{
    return columns;
}

std::vector<Field*>& Maze::operator[](int index)
{
	return matrix[index];
}

std::vector<Field*> const& Maze::operator[](int index) const
{
    return matrix[index];
}

ostream& operator<<(ostream& os, const Maze& maze) {
    for (int i = 0; i < maze.rows; ++i) {
        for (int j = 0; j < maze.columns; ++j) {
            os << maze[i][j]->getSymbol();   
        }
        os << '\n';
    }
    return os;
}

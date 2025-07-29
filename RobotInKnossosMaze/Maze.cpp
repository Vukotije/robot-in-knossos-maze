#include "Maze.h"

#include "MazeGenerator.h"

#include <iostream>

using std::vector;
using std::ostream;

Maze::Maze(int rows, int columns, int num_items)
    : rows_(rows), columns_(columns), matrix_(rows, vector<Field*>(columns)) {
    MazeGenerator::generate(*this);
}

Maze::~Maze() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < columns_; ++j) {
            delete matrix_[i][j];
        }
    }
}

int Maze::getRows() const {
    return rows_;
}

int Maze::getColumns() const {
    return columns_;
}

std::vector<Field*>& Maze::operator[](int index) {
    return matrix_[index];
}

std::vector<Field*> const& Maze::operator[](int index) const {
    return matrix_[index];
}

ostream& operator<<(ostream& os, const Maze& maze) {
    for (int i = 0; i < maze.rows_; ++i) {
        for (int j = 0; j < maze.columns_; ++j) {
            os << maze[i][j]->getSymbol();   
        }
        os << '\n';
    }
    return os;
}

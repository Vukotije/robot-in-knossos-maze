#include "MazeGenerator.h"
#include "Field.h"
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <utility>

using std::vector;
using std::pair;

void MazeGenerator::carveMazeDFS(int x, int y, int rows, int cols, vector<vector<Field*>>& matrix, vector<pair<int, int>>& directions)
{
    std::random_shuffle(directions.begin(), directions.end());

    for (int i = 0; i < directions.size(); ++i) {
        int dx = directions[i].first;
        int dy = directions[i].second;
        int next_x = x + dx;
        int next_y = y + dy;
        int betweenX = x + dx / 2;
        int betweenY = y + dy / 2;

        if (next_x > 0 && next_x < rows - 1 && next_y > 0 && next_y < cols - 1
            && matrix[next_x][next_y]->getSymbol() == '#') {
            matrix[betweenX][betweenY]->setSymbol(' ');
            matrix[next_x][next_y]->setSymbol(' ');
            carveMazeDFS(next_x, next_y, rows, cols, matrix, directions);
        }
    }
}

void MazeGenerator::generate(Maze& maze) {
    int rows = maze.getRows();
    int columns = maze.getColumns();
    vector<vector<Field*>>& matrix = maze.getMatrix();

	// Initialize the maze with walls
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = new Field(pair<int, int>(i, j), '#');
        }
    }

    int odd_rows = rows;
    int odd_columns = columns;
    if (rows % 2 == 0) --odd_rows;
    if (columns % 2 == 0) --odd_columns;
    matrix[1][1]->setSymbol(' ');
    vector<pair<int, int>> directions = { {-2, 0}, {2, 0}, {0, -2}, {0, 2} };
    carveMazeDFS(1, 1, odd_rows, odd_columns, matrix, directions);
   
	// Take care of extra row and column if even dimensions
    if (rows != odd_rows) {
        for (int j = 1; j < rows - 1; ++j) {
            if (rand() % 2 == 0) {
                matrix[rows-2][j]->setSymbol(' ');
            }
        }
    }
    if (columns != odd_columns) {
        for (int i = 1; i < rows - 1; ++i) {
            if (rand() % 2 == 0) {
                matrix[i][columns - 2]->setSymbol(' ');
            }
        }
    }
    
	// Place exit, entrance and robot
	pair<int, int> robot_position;
	vector<int> random_ys;
	random_ys.reserve(columns - 2);
    for (int j = 1; j < columns - 1; ++j) {
        random_ys.push_back(j);
	}
	bool exit_set = false;
    random_shuffle(random_ys.begin(), random_ys.end());
    for(int i = 1; i < columns-1; ++i) {
        if (!exit_set && matrix[1][random_ys[i]]->getSymbol() == ' ') {
			matrix[0][random_ys[i]]->setSymbol('I');
			exit_set = true;
		}
        else if (matrix[rows - 2][random_ys[i]]->getSymbol() == ' '
            && matrix[rows - 3][random_ys[i]]->getSymbol() == ' ') {
                matrix[rows - 1][random_ys[i]]->setSymbol('U');
                matrix[rows - 2][random_ys[i]]->setSymbol('R');
				robot_position = { rows - 2, random_ys[i] };
                break;
        }
	}

    // Place minotaur
    vector<Field*> emptyFields;
    for (int i = 0; i < rows/3; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (matrix[i][j]->getSymbol() == ' ')
                emptyFields.push_back(matrix[i][j]);
        }
    }
    // Extract item by index efficiently
    int minotaur_index = rand() % (emptyFields.size() - 1);
    Field* minotaur_field = emptyFields.at(minotaur_index);
    emptyFields[minotaur_index] = emptyFields.back();
    emptyFields.pop_back();
	minotaur_field->setSymbol('M'); 
    for (int i = rows / 3; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (matrix[i][j]->getSymbol() == ' ')
                emptyFields.push_back(matrix[i][j]);
        }
    }
    // TODO: place items on random empty fields
}
#include "Game.h"
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <utility>
#include "GameIO.h"

using std::pair;
using std::vector;


Game::Game(int rows, int columns, int itemsNum)
    : maze(rows, columns, itemsNum), robot(nullptr), minotaur(nullptr)
{
    PlaceFields();
}

Game::~Game() {
}

void Game::PlaceFields() {
	int rows = maze.getRows();
	int columns = maze.getColumns();

    vector<int> shuffled_columns;
    shuffled_columns.reserve(columns - 2);
    for (int j = 1; j < columns - 2; ++j) {
        shuffled_columns.push_back(j);
    }
    random_shuffle(shuffled_columns.begin(), shuffled_columns.end());

    bool exit_set = false;
    bool entrance_set = false;
	int minotaur_x = (rand() % (rows - 2) + 1) / 4; // Minotaur is placed in the first quarter of the maze
    for (int idx : shuffled_columns) {
        if (!exit_set && maze[1][idx]->getSymbol() == ' ') {
            maze[0][idx]->setSymbol('I');
            exit_set = true;
        }
        else if (!entrance_set && maze[rows - 2][idx]->getSymbol() == ' '
            && maze[rows - 3][idx]->getSymbol() == ' ') {
            maze[rows - 1][idx]->setSymbol('U');
            maze[rows - 2][idx]->setSymbol('R');
            this->robot = maze[rows - 2][idx];
            entrance_set = true;
        }
        else if (maze[minotaur_x][idx]->getSymbol() == ' ') {
            maze[minotaur_x][idx]->setSymbol('M');
            this->minotaur = maze[minotaur_x][idx];
			break;
        }
    }
}

void Game::moveRobot(char direction)
{
}

void Game::moveMinotaur(){
    vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    pair<int, int> minotaur_postition = minotaur->getPosition();

	vector<Field*> valid_fields;
    for (pair<int, int> dir : directions) {
		int field_x = minotaur_postition.first + dir.first;
		int field_y = minotaur_postition.second + dir.second;
        if (maze[field_x][field_y]->getSymbol() == ' ' ||
            maze[field_x][field_y]->getSymbol() == 'P') {
            valid_fields.push_back(maze[field_x][field_y]);
		}
        else if (maze[field_x][field_y]->getSymbol() == 'R') {
            minotaur->setSymbol(' ');
            maze[field_x][field_y]->setSymbol('M');
            minotaur = maze[field_x][field_y];
			GameOver();
			return;
		}
	}
    Field* next_field = valid_fields[rand() % valid_fields.size()];
    minotaur->setSymbol(' ');
    next_field->setSymbol('M');
	minotaur = next_field;
    
}

void Game::GameOver()
{
	// TODO: Implement game over logic
    GameIO::printEndMessage();
}

void Game::run()
{
		GameIO::printMaze(maze);
}

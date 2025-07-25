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

    for (int idx : shuffled_columns) {
        if (maze[1][idx]->getSymbol() == ' ') {
            maze[0][idx]->setSymbol('I');
            break;
        }        
    }
    for (int idx : shuffled_columns) {
        if (maze[rows - 2][idx]->getSymbol() == ' '
            && maze[rows - 3][idx]->getSymbol() == ' ') {
            maze[rows - 1][idx]->setSymbol('U');
            maze[rows - 2][idx]->setSymbol('R');
            this->robot = maze[rows - 2][idx];
			break;
        }
    }

    int minotaur_x = rand() % (rows / 3) + 1;
    for (int idx : shuffled_columns) {
        if (maze[minotaur_x][idx]->getSymbol() == ' ') {
            maze[minotaur_x][idx]->setSymbol('M');
            this->minotaur = maze[minotaur_x][idx];
            break;
        }
    }
}

void Game::moveRobot(char direction)
{
    pair<int, int> robot_position = robot->getPosition();
    int new_x = robot_position.first;
    int new_y = robot_position.second;
    switch (direction) {
        case 'W': case 'w': new_x--; break;
        case 'S': case 's': new_x++; break;
        case 'A': case 'a': new_y--; break;
        case 'D': case 'd': new_y++; break;
    }
    if (maze[new_x][new_y]->getSymbol() == ' ' ||
        maze[new_x][new_y]->getSymbol() == 'I') {
        robot->setSymbol(' ');
        maze[new_x][new_y]->setSymbol('R');
        robot = maze[new_x][new_y];
    }
}

bool Game::moveMinotaur(){
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
			return true;
		}
	}
    Field* next_field = valid_fields[rand() % valid_fields.size()];
    minotaur->setSymbol(' ');
    next_field->setSymbol('M');
	minotaur = next_field;
	return false;
}


void Game::run()
{
	int end_reason = 0;
    std::string quit_message;
    do {
        GameIO::printMaze(maze);
		char direction;
        bool wants_to_quit = GameIO::getRobotMoveDirection(direction);
        if (wants_to_quit) {
            break;
        }
        moveRobot(direction);
        bool lost = moveMinotaur();
        if (robot->getPosition().first == 0) {
			end_reason = 1;
            break;
		}
        if (lost) {
			end_reason = 2;
            break;
        }
	} while (true);

    switch (end_reason) {
        case 0:
			quit_message = GameIO::getQuitMessage();
            break;
        case 1: 
			quit_message = GameIO::getWonMessage();
            break;
        case 2:
			quit_message = GameIO::getLostMessage();
            break;
	}
    GameIO::printEndMessage(quit_message);
	GameIO::writeMazeToFile(maze, "last_maze_state.txt", quit_message);

}
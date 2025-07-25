#include "Game.h"
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <utility>
#include "GameIO.h"
#include "Item.h"

using std::pair;
using std::vector;

Game::Game(int rows, int columns, int items_num)
	: maze(rows, columns, items_num), robot(nullptr), minotaur(nullptr), current_items(),
	has_sword(false), has_shield(false), has_hammer(false), has_fog(false)
{
    PlaceFields(items_num);
}

Game::~Game() {
}


void Game::PlaceFields(int items_num) {
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

    int minotaur_x = 1 + rand() % (rows / 3);
    for (int idx : shuffled_columns) {
        if (maze[minotaur_x][idx]->getSymbol() == ' ') {
            maze[minotaur_x][idx]->setSymbol('M');
            this->minotaur = maze[minotaur_x][idx];
            break;
        }
    }
    vector<pair<int, int>> emptyFields;
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < columns - 1; ++j) {
            if (maze[i][j]->getSymbol() == ' ')
                emptyFields.push_back(maze[i][j]->getPosition());
        }
    }
    random_shuffle(emptyFields.begin(), emptyFields.end());
    for (int i = 0; i < items_num && !emptyFields.empty(); ++i) {
        pair<int, int> pos= emptyFields.back();
        emptyFields.pop_back();
        Field* item = Item::createRandomItem(pos);
        delete maze[pos.first][pos.second];
        maze[pos.first][pos.second] = item;
    }
}

bool Game::moveRobot(char direction)
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
    if ((maze[new_x][new_y]->getSymbol() == ' ' ||
        maze[new_x][new_y]->getSymbol() == 'I') ||
        (has_hammer && maze[new_x][new_y]->getSymbol() == '#'
         && new_x != 0 && new_x != maze.getRows() - 1
         && new_y != 0 && new_y != maze.getColumns() - 1)) {
        robot->setSymbol(' ');
        maze[new_x][new_y]->setSymbol('R');
        robot = maze[new_x][new_y];
    }
    else if (maze[new_x][new_y]->getSymbol() == 'M') {
        if (has_sword) {
            robot->setSymbol(' ');
            minotaur->setSymbol('R');
            return true;
        }
        else if (has_shield) {
            return false;
        }
        else {
            robot->setSymbol(' ');
            return true;
        }
    }
    
    else if (maze[new_x][new_y]->getSymbol() == 'P') {
        pair<int, Item*> item = { 3, static_cast<Item*>(maze[new_x][new_y]) };
        GameIO::printItemDescription(item.second->get_description());
        current_items.push_back(item);
        robot->setSymbol(' ');
        maze[new_x][new_y]->setSymbol('R');
        robot = maze[new_x][new_y];
    }
	return false;
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
            if (has_sword) {
                maze[minotaur_postition.first][minotaur_postition.second]->setSymbol(' ');
                return true;
            } 
            else if (has_shield) {
                continue;
}
            else {
                minotaur->setSymbol(' ');
                robot->setSymbol('M');
                minotaur = maze[field_x][field_y];
                return true;
            }            
		}
	}
    if (!valid_fields.empty()) {
        Field* next_field = valid_fields[rand() % valid_fields.size()];
        minotaur->setSymbol(' ');
        next_field->setSymbol('M');
        minotaur = next_field;
	}
	return false;
}

void Game::updateItems()
{
    for (pair<int, Item*> item : current_items) {
        if (item.first >= 0) {

            if (item.second->getType() == ItemType::SWORD) {
                has_sword = true;
            }
            else if (item.second->getType() == ItemType::SHIELD) {
                has_shield = true;
            }
            else if (item.second->getType() == ItemType::HAMMER) {
                has_hammer = true;
            }
            else if (item.second->getType() == ItemType::WAR_FOG) {
                has_fog = true;
            }
        }
    }
}


void Game::run()
{
	int end_reason = 0;
    std::string quit_message;
	bool fight = false;
	char direction;
	bool wants_to_quit = false;

    do {
        if (has_fog) {
            GameIO::printFoggedMaze(maze, robot);
        } else {
            GameIO::printMaze(maze);
		}
                
        wants_to_quit = GameIO::getRobotMoveDirection(direction);
        if (wants_to_quit) {
            break;
        }

        fight = moveRobot(direction);
		updateItems();
        if (fight) {
            if (has_sword) {
                end_reason = 2;
                break;
            }
            end_reason = 1;
            break;
		}
        fight = moveMinotaur();        
        if (fight) {
            if (has_sword) {
				end_reason = 1;
				break;
            }
			end_reason = 2;
            break;
        }

        if (robot->getPosition().first == 0) {
			end_reason = 1;
            break;
		}

        for (pair<int, Item*>& current_item : current_items) {
			current_item.first--;
            if (current_item.first < 0) {
                switch (current_item.second->getType())
                {
                case ItemType::SWORD:
                    has_sword = false;
                    break;
                case ItemType::SHIELD:
                    has_shield = false;
                    break;
                case ItemType::HAMMER:
                    has_hammer = false;
                    break;
                case ItemType::WAR_FOG:
                    has_fog = false;
                    break;
                }
            }
		}
	}
    while (true);


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
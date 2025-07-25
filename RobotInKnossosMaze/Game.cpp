// Implementation of the main game controller and logic

#include "Game.h"
#include "GameIO.h"
#include "Item.h"
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <utility>

using std::pair;
using std::vector;

Game::Game(int rows, int columns, int items_num)
	: maze(rows, columns, items_num), robot(nullptr), minotaur(nullptr),
    sword_info{ false, 0 }, shield_info{ false, 0 }, hammer_info{ false, 0 }, war_fog_info{ false, 0 }
{
    PlaceFields(items_num);
}

Game::~Game() {
}

void Game::PlaceFields(int items_num) {
	int rows = maze.getRows();
	int columns = maze.getColumns();

    // Create shuffled list of column indices for random placement
    vector<int> shuffled_columns;
    shuffled_columns.reserve(columns - 2);
    for (int j = 1; j < columns - 2; ++j) {
        shuffled_columns.push_back(j);
    }
    random_shuffle(shuffled_columns.begin(), shuffled_columns.end());

    // Place entrance at the top row
    for (int idx : shuffled_columns) {
        if (maze[1][idx]->getSymbol() == ' ') {
            maze[0][idx]->setSymbol('I');
            break;
        }        
    }    
    // Place exit and robot at the bottom row
    for (int idx : shuffled_columns) {
        if (maze[rows - 2][idx]->getSymbol() == ' '
            && maze[rows - 3][idx]->getSymbol() == ' ') {
            maze[rows - 1][idx]->setSymbol('U');
            maze[rows - 2][idx]->setSymbol('R');
            this->robot = maze[rows - 2][idx];
			break;
        }
    }
    // Place minotaur in the upper third of the maze
    int minotaur_x = 1 + rand() % (rows / 3);
    for (int idx : shuffled_columns) {
        if (maze[minotaur_x][idx]->getSymbol() == ' ') {
            maze[minotaur_x][idx]->setSymbol('M');
            this->minotaur = maze[minotaur_x][idx];
            break;
        }
    }    
    // Find all empty fields for item placement
    vector<pair<int, int>> emptyFields;
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < columns - 1; ++j) {
            if (maze[i][j]->getSymbol() == ' ')
                emptyFields.push_back(maze[i][j]->getPosition());
        }
    }    
    // Place random items in empty fields
    random_shuffle(emptyFields.begin(), emptyFields.end());
    for (int i = 0; i < items_num && !emptyFields.empty(); ++i) {
        pair<int, int> pos = emptyFields.back();
        emptyFields.pop_back();
        Field* item = Item::createRandomItem(pos);
        delete maze[pos.first][pos.second];
        maze[pos.first][pos.second] = item;
    }
}

bool Game::moveRobot(char direction)
{    
    // Calculate new position based on direction
    pair<int, int> robot_position = robot->getPosition();
    int new_x = robot_position.first;
    int new_y = robot_position.second;    
    switch (direction) {
        case 'W': case 'w': new_x--; break;
        case 'S': case 's': new_x++; break;
        case 'A': case 'a': new_y--; break;
        case 'D': case 'd': new_y++; break;
    }

    // Check if movement to empty space or entrance is valid
    // Allow breaking walls with hammer, except border walls
    if ((maze[new_x][new_y]->getSymbol() == ' ' ||
        maze[new_x][new_y]->getSymbol() == 'I') ||
        (hammer_info.first && maze[new_x][new_y]->getSymbol() == '#'
         && new_x != 0 && new_x != maze.getRows() - 1
         && new_y != 0 && new_y != maze.getColumns() - 1)) {
        robot->setSymbol(' ');
        maze[new_x][new_y]->setSymbol('R');
        robot = maze[new_x][new_y];
    }
    // Handle collision with minotaur
    else if (maze[new_x][new_y]->getSymbol() == 'M') {
        // Robot defeats minotaur with sword
        if (sword_info.first) {
            robot->setSymbol(' ');
            minotaur->setSymbol('R');
            return true;
        }
        // Shield blocks minotaur attack, no movement
        else if (shield_info.first) {
            return false;
        }
        // Robot is caught by minotaur
        else {
            robot->setSymbol(' ');
            return true;
        }
    }
    // Handle item collection
    else if (maze[new_x][new_y]->getSymbol() == 'P') {
        Item* item = static_cast<Item*>(maze[new_x][new_y]);
        GameIO::printItemDescription(item->get_description());
        
        // Activate item and set its effect duration
        switch (item->getType()) {
            case ItemType::HAMMER:
                hammer_info.first = true;
                hammer_info.second = 3;
                break;
            case ItemType::SHIELD:
                shield_info.first = true;
                shield_info.second = 3;
                break;
            case ItemType::SWORD:
                sword_info.first = true;
                sword_info.second = 3;
                break;
            case ItemType::WAR_FOG:
                war_fog_info.first = true;
                war_fog_info.second = 3;
                break;
        }
        robot->setSymbol(' ');
        maze[new_x][new_y]->setSymbol('R');
        robot = maze[new_x][new_y];
    }
	return false;
}

bool Game::moveMinotaur(){
    vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    pair<int, int> minotaur_postition = minotaur->getPosition();

    // Check all directions for valid moves
	vector<Field*> valid_fields;
    for (pair<int, int> dir : directions) {
		int field_x = minotaur_postition.first + dir.first;
		int field_y = minotaur_postition.second + dir.second;
        // Can move to empty spaces or destroy items
        if (maze[field_x][field_y]->getSymbol() == ' ' ||
            maze[field_x][field_y]->getSymbol() == 'P') {
            valid_fields.push_back(maze[field_x][field_y]);
		}
        // Handle collision with robot
        else if (maze[field_x][field_y]->getSymbol() == 'R') {
            // Robot defeats minotaur with sword
            if (sword_info.first) {
                maze[minotaur_postition.first][minotaur_postition.second]->setSymbol(' ');
                return true;
            } 
            // Shield blocks minotaur, minotaur moves away
            else if (shield_info.first) {
                continue;
            }
            // Minotaur catches robot
            else {
                minotaur->setSymbol(' ');
                robot->setSymbol('M');
                minotaur = maze[field_x][field_y];
                return true;
            }            
		}
	}
    
    // Move to random valid field
    // Only case of no valid moves is when minotaur is blocked by robot with shield
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
    // Decrease remaining turns for all active items
    sword_info.second--;
    if (sword_info.first && sword_info.second < 0) sword_info.first = false;
    shield_info.second--;
    if (shield_info.first && shield_info.second < 0) shield_info.first = false;
    hammer_info.second--;
    if (hammer_info.first && hammer_info.second < 0) hammer_info.first = false;
    war_fog_info.second--;
    if (war_fog_info.first && war_fog_info.second < 0) war_fog_info.first = false;
}


void Game::run()
{
	GameOverReason game_over_reason = GameOverReason::QUIT;
    std::string quit_message;
	bool fight = false;
	bool wants_to_quit = false;
	char direction;

    // Main game loop
    do {
        // Display maze, fogged or normal view based on war fog item
        if (war_fog_info.first) {
            GameIO::printFoggedMaze(maze, robot);
        } else {
            GameIO::printMaze(maze);
		}
                
        // Process robot movement
        wants_to_quit = GameIO::getRobotMoveDirection(direction);
        if (wants_to_quit) {
            break;
        }
        fight = moveRobot(direction);
        if (fight) {
            if (sword_info.first) {
                game_over_reason = GameOverReason::WON;
                break;
            }
            game_over_reason = GameOverReason::LOST;
            break;
		}
        
        // Process minotaur movement
        fight = moveMinotaur();        
        if (fight) {
            if (sword_info.first) {
				game_over_reason = GameOverReason::WON;
				break;
            }
			game_over_reason = GameOverReason::LOST;    
            break;
        }

        // Check if robot reached the exit
        if (robot->getPosition().first == 0) {
            game_over_reason = GameOverReason::WON;
            break;
        }
		updateItems();
	}
    while (true);

    // End game 
    switch (game_over_reason) {
        case GameOverReason::QUIT:
            quit_message = GameIO::getQuitMessage();
            break;
        case GameOverReason::WON: 
            quit_message = GameIO::getWonMessage();
            break;
        case GameOverReason::LOST:
            quit_message = GameIO::getLostMessage();
            break;
    }
    GameIO::printEndMessage(quit_message);
    GameIO::writeMazeToFile(maze, "last_maze_state.txt", quit_message);
}
// Implementation of the main game controller and logic

#include "Game.h"

#include "Consts.h"
#include "GameIO.h"
#include "Item.h"

#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>

using std::pair;
using std::vector;

Game::Game(int rows, int columns, int items_num)
    : maze_(rows, columns, items_num), robot_(nullptr), minotaur_(nullptr),
    sword_state_{ false, 0 }, shield_state_{ false, 0 }, hammer_state_{ false, 0 }, war_fog_state_{ false, 0 } {
    placeFields(items_num);
}

Game::~Game() {
}

void Game::placeFields(int items_num) {
    int rows = maze_.getRows();
    int columns = maze_.getColumns();

    // Create shuffled list of column indices for random placement
    vector<int> shuffledColumns;
    shuffledColumns.reserve(columns - 2);
    for (int j = 1; j < columns - 2; ++j) {
        shuffledColumns.push_back(j);
    }
    random_shuffle(shuffledColumns.begin(), shuffledColumns.end());

    // Place entrance at the top row
    for (int idx : shuffledColumns) {
        if (maze_[1][idx]->getSymbol() == ' ') {
            maze_[0][idx]->setSymbol('I');
            break;
        }        
    }    
    // Place exit and robot at the bottom row
    for (int idx : shuffledColumns) {
        if (maze_[rows - 2][idx]->getSymbol() == ' '
            && maze_[rows - 3][idx]->getSymbol() == ' ') {
            maze_[rows - 1][idx]->setSymbol('U');
            maze_[rows - 2][idx]->setSymbol('R');
            this->robot_ = maze_[rows - 2][idx];
            break;
        }
    }
    // Place minotaur in the fraction of the maze
    int minotaurX = 1 + rand() % int(rows * MINOTAUR_PLACEMENT_FRACTION);
    for (int idx : shuffledColumns) {
        if (maze_[minotaurX][idx]->getSymbol() == ' ') {
            maze_[minotaurX][idx]->setSymbol('M');
            this->minotaur_ = maze_[minotaurX][idx];
            break;
        }
    }    
    // Find all empty fields for item placement
    vector<pair<int, int>> emptyFields;
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < columns - 1; ++j) {
            if (maze_[i][j]->getSymbol() == ' ')
                emptyFields.push_back(maze_[i][j]->getPosition());
        }
    }    
    // Place random items in empty fields
    random_shuffle(emptyFields.begin(), emptyFields.end());
    for (int i = 0; i < items_num && !emptyFields.empty(); ++i) {
        pair<int, int> pos = emptyFields.back();
        emptyFields.pop_back();
        Field* item = Item::createRandomItem(pos);
        delete maze_[pos.first][pos.second];
        maze_[pos.first][pos.second] = item;
    }
}

bool Game::moveRobot(char direction) {    
    // Calculate new position based on direction
    pair<int, int> robotPosition = robot_->getPosition();
    int newX = robotPosition.first;
    int newY = robotPosition.second;    
    switch (direction) {
        case 'W': case 'w': newX--; break;
        case 'S': case 's': newX++; break;
        case 'A': case 'a': newY--; break;
        case 'D': case 'd': newY++; break;
    }

    // Check if movement to empty space or entrance is valid
    // Allow breaking walls with hammer, except border walls
    if ((maze_[newX][newY]->getSymbol() == ' ' ||
        maze_[newX][newY]->getSymbol() == 'I') ||
        (hammer_state_.first && maze_[newX][newY]->getSymbol() == '#'
         && newX != 0 && newX != maze_.getRows() - 1
         && newY != 0 && newY != maze_.getColumns() - 1)) {
        robot_->setSymbol(' ');
        maze_[newX][newY]->setSymbol('R');
        robot_ = maze_[newX][newY];
    }
    // Handle collision with minotaur
    else if (maze_[newX][newY]->getSymbol() == 'M') {
        // Robot defeats minotaur with sword
        if (sword_state_.first) {
            robot_->setSymbol(' ');
            minotaur_->setSymbol('R');
            return true;
        }
        // Shield blocks minotaur attack, no movement
        else if (shield_state_.first) {
            return false;
        }
        // Robot is caught by minotaur
        else {
            robot_->setSymbol(' ');
            return true;
        }
    }
    // Handle item collection
    else if (maze_[newX][newY]->getSymbol() == 'P') {
        Item* item = static_cast<Item*>(maze_[newX][newY]);
        GameIO::printItemDescription(item->getDescription());
        
        // Activate item and set its effect duration
        switch (item->getType()) {
            case ItemType::HAMMER:
                hammer_state_.first = true;
                hammer_state_.second = 3;
                break;
            case ItemType::SHIELD:
                shield_state_.first = true;
                shield_state_.second = 3;
                break;
            case ItemType::SWORD:
                sword_state_.first = true;
                sword_state_.second = 3;
                break;
            case ItemType::WAR_FOG:
                war_fog_state_.first = true;
                war_fog_state_.second = 3;
                break;
        }
        robot_->setSymbol(' ');
        maze_[newX][newY]->setSymbol('R');
        robot_ = maze_[newX][newY];
    }
    return false;
}

bool Game::moveMinotaur() {
    vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    pair<int, int> minotaurPosition = minotaur_->getPosition();

    // Check all directions for valid moves
    vector<Field*> validFields;
    for (pair<int, int> dir : directions) {
        int fieldX = minotaurPosition.first + dir.first;
        int fieldY = minotaurPosition.second + dir.second;
        // Can move to empty spaces or destroy items
        if (maze_[fieldX][fieldY]->getSymbol() == ' ' ||
            maze_[fieldX][fieldY]->getSymbol() == 'P') {
            validFields.push_back(maze_[fieldX][fieldY]);
        }
        // Handle collision with robot
        else if (maze_[fieldX][fieldY]->getSymbol() == 'R') {
            // Robot defeats minotaur with sword
            if (sword_state_.first) {
                maze_[minotaurPosition.first][minotaurPosition.second]->setSymbol(' ');
                return true;
            } 
            // Shield blocks minotaur, minotaur moves away
            else if (shield_state_.first) {
                continue;
            }
            // Minotaur catches robot
            else {
                minotaur_->setSymbol(' ');
                robot_->setSymbol('M');
                minotaur_ = maze_[fieldX][fieldY];
                return true;
            }            
        }
    }
    
    // Move to random valid field
    // Only case of no valid moves is when minotaur is blocked by robot with shield
    if (!validFields.empty()) {
        Field* nextField = validFields[rand() % validFields.size()];
        minotaur_->setSymbol(' ');
        nextField->setSymbol('M');
        minotaur_ = nextField;
    }
    return false;
}

void Game::updateItems() {
    // Decrease remaining turns for all active items
    sword_state_.second--;
    if (sword_state_.first && sword_state_.second < 0) sword_state_.first = false;
    shield_state_.second--;
    if (shield_state_.first && shield_state_.second < 0) shield_state_.first = false;
    hammer_state_.second--;
    if (hammer_state_.first && hammer_state_.second < 0) hammer_state_.first = false;
    war_fog_state_.second--;
    if (war_fog_state_.first && war_fog_state_.second < 0) war_fog_state_.first = false;
}

void Game::run() {
    GameOverReason gameOverReason = GameOverReason::QUIT;
    std::string quitMessage;
    bool fight = false;
    bool wantsToQuit = false;
    char direction;

    // Main game loop
    do {
        // Display maze, fogged or normal view based on war fog item
        if (war_fog_state_.first) {
            GameIO::printFoggedMaze(maze_, robot_);
        } else {
            GameIO::printMaze(maze_);
        }
                
        // Process robot movement
        wantsToQuit = GameIO::getRobotMoveDirection(direction);
        if (wantsToQuit) {
            break;
        }
        fight = moveRobot(direction);
        if (fight) {
            if (sword_state_.first) {
                gameOverReason = GameOverReason::WON;
                break;
            }
            gameOverReason = GameOverReason::LOST;
            break;
        }
        
        // Process minotaur movement
        fight = moveMinotaur();        
        if (fight) {
            if (sword_state_.first) {
                gameOverReason = GameOverReason::WON;
                break;
            }
            gameOverReason = GameOverReason::LOST;    
            break;
        }

        // Check if robot reached the exit
        if (robot_->getPosition().first == 0) {
            gameOverReason = GameOverReason::WON;
            break;
        }
        updateItems();
    }
    while (true);

    // End game 
    switch (gameOverReason) {
        case GameOverReason::QUIT:
            quitMessage = GameIO::getQuitMessage();
            break;
        case GameOverReason::WON: 
            quitMessage = GameIO::getWonMessage();
            break;
        case GameOverReason::LOST:
            quitMessage = GameIO::getLostMessage();
            break;
    }
    GameIO::printEndMessage(quitMessage);
    GameIO::writeMazeToFile(maze_, "last_maze_state.txt", quitMessage);
}
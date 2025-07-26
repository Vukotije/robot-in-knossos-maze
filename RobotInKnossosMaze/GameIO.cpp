/**
 * @file GameIO.cpp
 * @brief Implementation of game input/output operations
 */

#include "GameIO.h"

#include "Consts.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::pair;
using std::min;
using std::max;

// Clears the input buffer after invalid input
static void clear_input() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Checks if the user wants to quit by entering 'Q' or 'q'
// returns true if user wants to quit, false otherwise
static bool wants_to_quit() {
    char ch;
    cin >> ch;
    if (ch == 'q' || ch == 'Q') {
        clear_input();
        return true;
    }
    cin.putback(ch);
    return false;
}

bool GameIO::getValidDimensions(int& r, int& c) {
    cout << " Enter the maze dimensions <rows, columns> ("
        << MIN_MAZE_SIZE << "-" << MAX_MAZE_SIZE << "): ";
    while (!wants_to_quit()) {
        if (cin >> r >> c) {
            if (r > MIN_MAZE_SIZE && r <= MAX_MAZE_SIZE &&
                c > MIN_MAZE_SIZE && c <= MAX_MAZE_SIZE) {
                clear_input();
                return true;
            }
            else {
                cout << "Error: Values must be between " << MIN_MAZE_SIZE
                    << " and " << MAX_MAZE_SIZE << "!" << endl;
            }
        }
        else {
            cout << "Error: Please enter two valid integers!" << endl;
            clear_input();
        }
    }
    return false;
}

bool GameIO::getValidItemsNum(int& n, int rows, int columns) {
    cout << " Enter the number of ingame items ("
        << MIN_ITEMS_NUM << "<" << "): ";
    while (!wants_to_quit()) {
        if (cin >> n) {
            if (n > MIN_ITEMS_NUM && n <= get_max_items_num(rows, columns)) {
                clear_input();
                return true;
            }
            else {
                cout << "Error: Value must be between " << MIN_ITEMS_NUM
                    << " and " << get_max_items_num(rows, columns) << "!" << endl;
            }
        }
        else {
            cout << "Error: Please enter a valid integer!" << endl;
            clear_input();
        }
    }
    return false;
}

bool GameIO::getRobotMoveDirection(char& direction) {
    cout << " Enter the robot move direction: ";
    while (!wants_to_quit()) {
        cin >> direction;
        if (direction == 'W' || direction == 'w' ||
            direction == 'A' || direction == 'a' ||
            direction == 'S' || direction == 's' ||
            direction == 'D' || direction == 'd') {
            clear_input();
            return false;
        }
        else {
            cout << "Invalid input! Please enter W, A, S, or D." << endl;
        }
    }
    return true;
}

void GameIO::printWelcomeMessage() {
    cout << "======================================================\n"
        << " Welcome to Robot in Knossos Maze!\n"
        << " Guide your robot through the legendary labyrinth.\n"
        << " Whenever you want to quit the game, enter 'Q'\n"
        << "=======================================================\n\n";
}

void GameIO::printInstructions() {
    cout << "=======================================================\n"
        << " - Use 'W' to move up, 'S' to move down,\n"
        << "   'A' to move left, and 'D' to move right.\n"
        << " - Reach the exit and avoid the Minotaur to win the game.\n"
        << " - Items will give you mistery effect for 3 turns.\n"
        << " - Enter 'Q' at any time to quit the game.\n"
        << "=======================================================\n\n";
}

void GameIO::printMazeGenerationTime(double time) {
    cout << "\n=======================================================\n"
        << "Maze generation took " << std::fixed << std::setprecision(3) << time << " miliseconds.\n"
        << "You can now start playing the game!\n"
        << "=======================================================\n";
}

void GameIO::printMaze(const Maze& maze) {
    cout << maze << endl;
}

void GameIO::printFoggedMaze(const Maze& maze, Field* robot) {
    pair<int, int> robotPosition = robot->getPosition();
    int robotX = robotPosition.first;
    int robotY = robotPosition.second;
    for (int i = max(0, robotX - WAR_FOG_RANGE); i <= min(robotX + WAR_FOG_RANGE, maze.getRows() - 1); ++i) {
        for (int j = max(0, robotY - WAR_FOG_RANGE); j <= min(robotY + WAR_FOG_RANGE, maze.getColumns() - 1); ++j) {
            cout << maze[i][j]->getSymbol();
        }
        cout << endl;
    }
}

void GameIO::printEndMessage(string& reason) {
    cout << reason
        << "=======================================================\n"
        << " Thank you for playing Robot in Knossos Maze!\n"
        << " We hope you enjoyed the adventure.\n"
        << "=======================================================\n";
}

void GameIO::printItemDescription(const string& description) {
    cout << "=======================================================\n"
         << "You picked up:\n"
        << description << "\n"
        << "=======================================================\n";
}

const string& GameIO::getQuitMessage() {
    static const string msg =
        "=======================================================\n"
        " You have chosen to quit the game!\n"
        "=======================================================\n";
    return msg;
}

const string& GameIO::getLostMessage() {
    static const string msg =
        "=======================================================\n"
        " Game Over!"
        " The Minotaur got the better of you.\n"
        " Better luck next time!\n"
        "=======================================================\n";
    return msg;
}

const string& GameIO::getWonMessage() {
    static const string msg =
        "=======================================================\n"
        " Congratulations!"
        " You have successfully completed the maze!\n"
        " You outsmarted the Minotaur!\n"
        "=======================================================\n";
    return msg;
}

void GameIO::writeMazeToFile(const Maze& maze, const string& filename, string& result_message) {
    string outFile = filename.empty() ? "last_maze_state.txt" : filename;
    std::ofstream ofs(outFile);
    if (!ofs) {
        cout << "Error: Unable to open file '" << outFile << "' for writing." << endl;
        return;
    }
    ofs << maze;
    ofs << "\n\n=======================================================\n"
        << result_message
        << "=======================================================\n";
    ofs.close();
    cout << "Maze successfully written to '" << outFile << "'." << endl;
}

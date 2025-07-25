#include "GameIO.h"
#include "Consts.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::pair;
using std::min;
using std::max;

static void clearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static bool wantsToQuit() {
    char ch;
    cin >> ch;
    if (ch == 'q' || ch == 'Q') {
        clearInput();
        return true;
    }
    cin.putback(ch);
    return false;
}

// Custom logic for determening max number of items:
// min_blocks = 2 * (columns + rows)
// matrix_spaces = columns * rows
// max_empty_spaces = columns * rows - 2 * (columns + rows);


bool GameIO::getValidDimensions(int& r, int& c) {
    cout << " Enter the maze dimensions <rows, columns> ("
        << MIN_MAZE_SIZE << "-" << MAX_MAZE_SIZE << "): ";
    while (!wantsToQuit()) {
        if (cin >> r >> c) {
            if (r > MIN_MAZE_SIZE && r <= MAX_MAZE_SIZE &&
                c > MIN_MAZE_SIZE && c <= MAX_MAZE_SIZE) {
                clearInput();
                return true;
            }
            else {
                cout << "Error: Values must be between " << MIN_MAZE_SIZE
                    << " and " << MAX_MAZE_SIZE << "!" << endl;
            }
        }
        else {
            cout << "Error: Please enter two valid integers!" << endl;
            clearInput();
        }
    }
    return false;
}

bool GameIO::getValidItemsNum(int& n, int row, int columns) {
    cout << " Enter the number of ingame items ("
        << MIN_ITEMS_NUM << "<" << "): ";
    while (!wantsToQuit()) {
        if (cin >> n) {
            if (n > MIN_ITEMS_NUM && n <= getMaxItemsNum(row, columns)) {
                clearInput();
                return true;
            }
            else {
                cout << "Error: Value must be between " << MIN_ITEMS_NUM
                    << " and " << getMaxItemsNum(row, columns) << "!" << endl;
            }
        }
        else {
            cout << "Error: Please enter a valid integer!" << endl;
            clearInput();
        }
    }
    return false;
}

char GameIO::getRobotMoveDirection(char& direction)
{
    cout << " Enter the robot move direction: ";
    while (!wantsToQuit()) {
        cin >> direction;
        if (direction == 'W' || direction == 'w' ||
            direction == 'A' || direction == 'a' ||
            direction == 'S' || direction == 's' ||
            direction == 'D' || direction == 'd') {
            clearInput();
            return false;
        }
        else {
            cout << "Invalid input! Please enter W, A, S, or D." << endl;
        }
    }
	return true;
}

void GameIO::printWelcomeMessage()
{
    cout << "======================================================\n"
        << " Welcome to Robot in Knossos Maze!\n"
        << " Guide your robot through the legendary labyrinth.\n"
        << " Whenever you want to quit the game, enter 'Q'\n"
        << "=======================================================\n\n";
}

void GameIO::printInstructions()
{
    cout << "=======================================================\n"
        << " - Use 'W' to move up, 'S' to move down,\n"
        << "   'A' to move left, and 'D' to move right.\n"
        << " - Reach the exit and avoid the Minotaur to win the game.\n"
        << " - Items will give you mistery effect for 3 turns.\n"
        << " - Enter 'Q' at any time to quit the game.\n"
        << "=======================================================\n\n";
}

void GameIO::printMazeGenerationTime(long long time)
{

    cout << "\n=======================================================\n"
        << "Maze generation took " << time << " miliseconds.\n"
        << "You can now start playing the game!\n"
        << "=======================================================\n";
}

void GameIO::printMaze(const Maze& maze)
{
	cout << maze << endl;
}

void GameIO::printFoggedMaze(const Maze& maze, Field* robot)
{
	pair<int, int> robot_position = robot->getPosition();
	int robot_x = robot_position.first;
	int robot_y = robot_position.second;
    for (int i = max(0, robot_x - 3); i <= min(robot_x + 3, maze.getRows() - 1); ++i) {
        for (int j = max(0, robot_y - 3); j <= min(robot_y + 3, maze.getColumns() - 1); ++j) {
            cout << maze[i][j]->getSymbol();
        }
        cout << endl;
    }
}


void GameIO::printEndMessage(string& reason)
{
    cout << reason
        << "=======================================================\n"
        << " Thank you for playing Robot in Knossos Maze!\n"
        << " We hope you enjoyed the adventure.\n"
        << "=======================================================\n";
}

void GameIO::printItemDescription(const string& description)
{
    cout << "=======================================================\n"
         << "You picked up:\n"
		<< description << "\n"
		<< "=======================================================\n";
}

const string& GameIO::getQuitMessage()
{
    static const string msg =
        "=======================================================\n"
        " You have chosen to quit the game!\n"
        "=======================================================\n";
    return msg;
}

const string& GameIO::getLostMessage()
{
    static const string msg =
        "=======================================================\n"
        " Game Over!"
        " The Minotaur got the better of you.\n"
        " Better luck next time!\n"
        "=======================================================\n";
    return msg;
}

const string& GameIO::getWonMessage()
{
    static const string msg =
        "=======================================================\n"
        " Congratulations!"
        " You have successfully completed the maze!\n"
        " You outsmarted the Minotaur!\n"
        "=======================================================\n";
    return msg;
}

void GameIO::writeMazeToFile(const Maze& maze, const string& filename, string& result_message)
{
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

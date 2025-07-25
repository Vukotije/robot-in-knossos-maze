#include "GameIO.h"
#include "Constants.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

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
const int getMaxItemsNum(int rows, int columns) {
    return MAX_ITEMS_FRACTION * (columns * rows - 2 * (columns + rows));

}

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



void GameIO::printWelcomeMessage()
{
    cout << "======================================================\n"
        << " Welcome to Robot in Knossos Maze!\n"
        << " Guide your robot through the legendary labyrinth.\n"
        << " Whenever you want to quit the game, enter 'Q'\n"
        << "=======================================================\n\n";
}

void GameIO::printEndMessage()
{
    cout << "=======================================================\n"
        << " Thank you for playing Robot in Knossos Maze!\n"
        << " We hope you enjoyed the adventure.\n"
        << "=======================================================\n";
}

void GameIO::printMaze(Maze& maze)
{
	cout << maze << endl;
}

void GameIO::printGenerationTime(long long time)
{

    cout << "\n=======================================================\n"
        << "Maze generation took " << time << " miliseconds.\n"
        << "You can now start playing the game!\n"
	    << "=======================================================\n";
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

void GameIO::writeMazeToFile(const Maze& maze, const std::string& filename, bool won)
{
    string result_message = won ? "Congratulations! You have successfully completed the maze!\n"
		: "Game Over! You failed to complete the maze.\n";
    string outFile = filename.empty() ? "last_maze_state.txt" : filename;
    std::ofstream ofs(outFile);
    if (!ofs) {
        cout << "Error: Unable to open file '" << outFile << "' for writing." << endl;
        return;
    }
    ofs << maze;
    ofs << "/n/n=======================================================\n"
        << result_message
        << "=======================================================\n";
    ofs.close();
    cout << "Maze successfully written to '" << outFile << "'." << endl;
}

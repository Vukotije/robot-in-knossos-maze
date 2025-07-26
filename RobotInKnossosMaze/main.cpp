// This file contains the main function that initializes the game,
// collects user input for game parameters, and runs the game loop.

#include "Game.h"
#include "GameIO.h"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;

// Main initializes random seed, displays welcome message, collects user input
// for maze dimensions and item count, measures maze generation time,
// and starts the game.
int main()
{
    int rows, columns, itemsNum;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GameIO::printWelcomeMessage();
    if (!GameIO::getValidDimensions(rows, columns))
        return 0;
    if (!GameIO::getValidItemsNum(itemsNum, rows, columns))
        return 0;
    steady_clock::time_point startTime = steady_clock::now();
    Game game(rows, columns, itemsNum);
    steady_clock::time_point endTime = steady_clock::now();
    double duration = duration_cast<microseconds>(endTime - startTime).count() / 1000.0;
    GameIO::printMazeGenerationTime(duration);
    GameIO::printInstructions();
    game.run();
    return 0;
}
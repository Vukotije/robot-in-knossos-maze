#include "GameIO.h"
#include "Game.h"
#include <chrono>

using std::chrono::steady_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

int main() {
    int rows, columns, items_num;
    GameIO::printWelcomeMessage();
    if (!GameIO::getValidDimensions(rows, columns)) return 0;
    if (!GameIO::getValidItemsNum(items_num, rows, columns)) return 0;
    steady_clock::time_point start_time = steady_clock::now();
    Game game(rows, columns, items_num);
    steady_clock::time_point end_time = steady_clock::now();
    long long duration = duration_cast<milliseconds>(end_time - start_time).count();
	GameIO::printMazeGenerationTime(duration);
	GameIO::printInstructions();
    game.run();
    return 0;
}
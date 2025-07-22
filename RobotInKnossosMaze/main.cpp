#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;

const int MIN_MAZE_SIZE = 15;
const int MAX_MAZE_SIZE = 100;
const int MIN_ITEMS_NUM = 3;
const float MAX_ITEMS_FRACTION = 0.1;

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


static bool get_valid_dimensions(int& r, int& c) {
    cout << " Enter the maze dimensions <rows, columns> ("
        << MIN_MAZE_SIZE << "-" << MAX_MAZE_SIZE << "): ";
    while (!wantsToQuit()) {
        if (cin >> r >> c) {
            if (r >= MIN_MAZE_SIZE && r <= MAX_MAZE_SIZE &&
                c >= MIN_MAZE_SIZE && c <= MAX_MAZE_SIZE) {
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

bool get_valid_items_num(int& n, const int max_n) {
    cout << " Enter the number of ingame items ("
        << MIN_ITEMS_NUM << "-" << max_n << "): ";
    while (!wantsToQuit()) {
        if (cin >> n) {
            if (n >= MIN_ITEMS_NUM && n <= max_n) {
                clearInput();
                return true;
            }
            else {
                cout << "Error: Value must be between " << MIN_ITEMS_NUM
                    << " and " << max_n << "!" << endl;
            }
        }
        else {
            cout << "Error: Please enter a valid integer!" << endl;
            clearInput();
        }
    }
    return false;
}


int main() {

    int rows, columns, items_num;
    cout << "======================================================\n"
        << " Welcome to Robot in Knossos Maze!\n"
        << " Guide your robot through the legendary labyrinth.\n"
        << " Whenever you want to quit the game, enter 'Q'\n"
        << "=======================================================\n\n";

    while (true) {

        if (!get_valid_dimensions(rows, columns)) break;

        // Custom logic for determening max number of items:
        // min_blocks = 2 * (columns + rows)
        // matrix_spaces = columns * rows
        // max_empty_spaces = columns * rows - 2 * (columns + rows);
        const int max_items = MAX_ITEMS_FRACTION * (columns * rows - 2 * (columns + rows));
        if (!get_valid_items_num(items_num, max_items)) break;    

        //TODO: Game game(rows, cols, numItems)....;
    }
    cout << "\n======================================================\n"
        << " Thank you for playing!\n"
        << "======================================================\n";
        
    return 0;
}
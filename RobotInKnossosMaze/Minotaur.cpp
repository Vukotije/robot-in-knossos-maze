#include "Minotaur.h"
#include <random>

using std::pair;
using std::vector;

Minotaur::Minotaur(std::pair<int, int> start) : Entity(start, 'M') {}

void Minotaur::move(vector<pair<int, int>> possible_moves) {
	setPosition(possible_moves[rand() % possible_moves.size()]);
}
#pragma once
#include "Entity.h"
#include <vector>

class Minotaur : public Entity {
public:
    Minotaur(std::pair<int, int> start);
    void move(std::vector<pair<int, int>> possible_moves) override;
};

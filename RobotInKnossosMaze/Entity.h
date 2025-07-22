#pragma once
#include <utility>
#include <vector>
#include "Field.h"

class Entity : public Field {
    public:
        Entity(std::pair<int, int> start, char symbol);
        virtual void move(std::vector<std::pair<int, int>> possible_moves) = 0;
		virtual ~Entity() = default;

};
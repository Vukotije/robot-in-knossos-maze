#pragma once
#include "Entity.h"

class Robot : public Entity {
public:
    Robot(std::pair<int, int> start);
    void move(char direction);
};

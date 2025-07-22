#include "Robot.h"
#include <iostream>

using std::pair;

Robot::Robot(pair<int, int> start) : Entity(start, 'R') {}

void Robot::move(char direction) {
	pair<int, int> position = getPosition();
    switch (direction) {
    case 'w': case 'W': --position.first; break;  
    case 'a': case 'A': --position.second; break; 
    case 's': case 'S': ++position.first; break;  
    case 'd': case 'D': ++position.second; break;
    // Validation should be done elsewhere
    default: std::cout << "Invalid move\n"; break;
    }
	setPosition(position);
}
#pragma once
#include <utility>

// Base class for all objects that can be placed in the maze, including
// walls, empty spaces, exit, entrance, robot, minotaur, and items.
class Field {
public:
    Field(std::pair<int, int>, char symbol);
    virtual ~Field() = default;
    std::pair<int, int> getPosition() const;
    void setPosition(std::pair<int, int>);
    char getSymbol() const;
    void setSymbol(char symbol);

private:
    std::pair<int, int> position;
    /// Character symbol for display representation
    char symbol;
};
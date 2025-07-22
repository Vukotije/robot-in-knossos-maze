#pragma once
#include <utility>

class Field {
public:
    Field(std::pair<int, int>, char symbol);
    virtual ~Field() = default;
    std::pair<int, int> getPosition() const;
    void setPosition(std::pair<int, int>);
    char getSymbol() const;

private:
    std::pair<int, int> position;
    char symbol;
};
#pragma once
#include <utility>

class Field {
public:
    Field(std::pair<int, int>, char symbol);
    std::pair<int, int> getPosition() const;
    void setPosition(std::pair<int, int>);
    char getSymbol() const;
	void setSymbol(char symbol);

private:
    std::pair<int, int> position;
    char symbol;
};
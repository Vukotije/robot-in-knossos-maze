#include "Field.h"

Field::Field(std::pair<int, int> position, char symbol) : position(position), symbol(symbol) {}

std::pair<int, int> Field::getPosition() const {
    return this->position;
}

void Field::setPosition(std::pair<int, int> position) {
    this->position = position;
}

char Field::getSymbol() const {
    return symbol;
}

void Field::setSymbol(char symbol)
{
	this->symbol = symbol;
}

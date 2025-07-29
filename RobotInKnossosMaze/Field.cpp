#include "Field.h"

Field::Field(std::pair<int, int> position, char symbol) : position_(position), symbol_(symbol) {}

std::pair<int, int> Field::getPosition() const {
    return this->position_;
}

void Field::setPosition(std::pair<int, int> position) {
    this->position_ = position;
}

char Field::getSymbol() const {
    return symbol_;
}

void Field::setSymbol(char symbol) {
    this->symbol_ = symbol;
}

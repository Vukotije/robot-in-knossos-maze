// This file defines the Item base class and concrete implementations
// for various power-ups that provide temporary abilities to the robot.

#pragma once
#include "Field.h"
#include <utility>
#include <string>

enum class ItemType {
    WAR_FOG,
    SWORD,
    SHIELD,
    HAMMER 
};

// Items provide temporary power-ups to the robot when collected,
// lasting for a limited number of turns.
class Item : public Field
{
public:
	Item(std::pair<int, int> position);
    virtual ~Item() = default;
    static Item* createRandomItem(std::pair<int, int> position);
    virtual ItemType getType() const = 0;
    virtual std::string get_description() const = 0;
};

 // This item provides limited vision around the robot
class WarFog : public Item {
public:
    WarFog(std::pair<int, int> position);
    ~WarFog() override;
    ItemType getType() const override;
    std::string get_description() const override;
};

// Item that allows the robot to kill the minotaur
class Sword : public Item {
public:
    Sword(std::pair<int, int> position);
    ~Sword() override;
    ItemType getType() const override;
    std::string get_description() const override;
};

// Item that provides protection from minotaur attacks
class Shield : public Item {
public:
    Shield(std::pair<int, int> position);
    ~Shield() override;
    ItemType getType() const override;
    std::string get_description() const override;
};

// Item that allows breaking through walls
class Hammer : public Item {
public:
    Hammer(std::pair<int, int> position);
    ~Hammer() override;
    ItemType getType() const override;
    std::string get_description() const override;
};

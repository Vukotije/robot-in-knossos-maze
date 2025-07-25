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

class Item : public Field
{
	public:
	Item(std::pair<int, int> postion);
    virtual ~Item() = default;
    static Item* createRandomItem(std::pair<int, int> position);

    virtual ItemType getType() const = 0;
    virtual std::string get_description() const = 0;
};

class WarFog : public Item {
public:
    WarFog(std::pair<int, int> position);
    ~WarFog() override;
    ItemType getType() const override;
    std::string get_description() const override;
};

class Sword : public Item {
public:
    Sword(std::pair<int, int> position);
    ~Sword() override;
    ItemType getType() const override;
    std::string get_description() const override;
};

class Shield : public Item {
public:
    Shield(std::pair<int, int> position);
    ~Shield() override;
    ItemType getType() const override;
    std::string get_description() const override;
};

class Hammer : public Item {
public:
    Hammer(std::pair<int, int> position);
    ~Hammer() override;
    ItemType getType() const override;
    std::string get_description() const override;
};
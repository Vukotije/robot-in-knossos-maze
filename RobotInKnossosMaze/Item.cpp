#include "Item.h"

#include <string>
#include <utility>

using std::pair;
using std::string;

Item::Item(pair<int, int> position) : Field(position, 'P') {}

Item* Item::createRandomItem(pair<int, int> position) {
    int itemType = rand() % 4;
    switch (itemType) {
        case 0: return new WarFog(position);
        case 1: return new Sword(position);
        case 2: return new Shield(position);
        case 3: return new Hammer(position);
        default: return nullptr;
    }
}


WarFog::WarFog(pair<int, int> position) : Item(position) {}
WarFog::~WarFog() {};
ItemType WarFog::getType() const {
    return ItemType::WAR_FOG;
}
string WarFog::getDescription() const {
    return "War Mist: A mystical fog that temporarily limits vision.";
}


Sword::Sword(pair<int, int> position) : Item(position) {}
Sword::~Sword() {};
ItemType Sword::getType() const {
    return ItemType::SWORD;
}
string Sword::getDescription() const {
    return "Sword: A sharp blade that can slay the minotaur.";
}


Shield::Shield(pair<int, int> position) : Item(position) {}
Shield::~Shield() {};
ItemType Shield::getType() const {
    return ItemType::SHIELD;
}
string Shield::getDescription() const {
    return "Shield: A sturdy shield that provides protection from minotaur attacks.";
}


Hammer::Hammer(pair<int, int> position) : Item(position) {}
Hammer::~Hammer() {};
ItemType Hammer::getType() const {
    return ItemType::HAMMER;
}
string Hammer::getDescription() const {
    return "Hammer: A heavy hammer that can break through walls.";
}

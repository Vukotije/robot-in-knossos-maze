#include "Item.h"
#include <string>
#include <utility>

using std::pair;
using std::string;

Item::Item(pair<int, int> position) : Field(position, 'P') {}

Item* Item::createRandomItem(pair<int, int> position) {
	int item_type = rand() % 4;
	switch (item_type) {
		case 0: return new WarFog(position);
		case 1: return new Sword(position);
		case 2: return new Shield(position);
		case 3: return new Hammer(position);
		default: return nullptr;
	}
}

// WarFog implementation
WarFog::WarFog(pair<int, int> position) : Item(position) {}
WarFog::~WarFog() {};
ItemType WarFog::getType() const {
	return ItemType::WAR_FOG;
}
string WarFog::get_description() const {
	return "War Mist: A mystical fog that temporarily limits vision.";
}

// Sword implementation
Sword::Sword(pair<int, int> position) : Item(position) {}
Sword::~Sword() {};
ItemType Sword::getType() const {
	return ItemType::SWORD;
}
string Sword::get_description() const {
	return "Sword: A sharp blade that can slay the minotaur.";
}

// Shield implementation
Shield::Shield(pair<int, int> position) : Item(position) {}
Shield::~Shield() {};
ItemType Shield::getType() const {
	return ItemType::SHIELD;
}
string Shield::get_description() const {
	return "Shield: A sturdy shield that provides protection from minotaur attacks.";
}

// Hammer implementation
Hammer::Hammer(pair<int, int> position) : Item(position) {}
Hammer::~Hammer() {};
ItemType Hammer::getType() const {
	return ItemType::HAMMER;
}
string Hammer::get_description() const {
	return "Hammer: A heavy hammer that can break through walls.";
}

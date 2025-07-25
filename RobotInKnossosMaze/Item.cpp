#include "Item.h"
#include <string>
#include <utility>

using std::pair;
using std::string;

Item::Item(pair<int, int> postion) : Field(postion, 'P') {}

Item* Item::createRandomItem(pair<int, int> position) {
	//int item_type = rand() % 4;
	int item_type = 0; // For now, we only have Hammer as a valid item type
	switch (item_type) {
		case 0: return new WarMist(position);
		//case 1: return new Sword(position);
		//case 2: return new Shield(position);
		//case 3: return new Hammer(position);
		default: return nullptr;
	}
	
}



WarMist::WarMist(pair<int, int> position) : Item(position) {}
WarMist::~WarMist() {};
ItemType WarMist::getType() const {
	return ItemType::WAR_MIST;
}
string WarMist::get_description() const {
	return "War Mist: A mystical fog that grants temporary invincibility.";
}


Sword::Sword(pair<int, int> position) : Item(position) {}
Sword::~Sword() {};
ItemType Sword::getType() const {
	return ItemType::SWORD;
}
string Sword::get_description() const {
	return "Sword: A sharp blade that increases attack power.";
}



Shield::Shield(pair<int, int> position) : Item(position) {}
Shield::~Shield() {};
ItemType Shield::getType() const {
	return ItemType::SHIELD;
}
string Shield::get_description() const {
	return "Shield: A sturdy shield that increases defense.";
}



Hammer::Hammer(pair<int, int> position) : Item(position) {}
Hammer::~Hammer() {};
ItemType Hammer::getType() const {
	return ItemType::HAMMER;
}
string Hammer::get_description() const {
	return "Hammer: A heavy hammer that can break obstacles.";
}


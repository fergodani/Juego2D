#include "Inventory.h"

Inventory::Inventory() {
	this->money = 0;
	this->wood = 0;
}


void Inventory::addItem(Item* item) {
	bool found = false;
	for (auto const& i : items) {
		if (i->id._Equal(item->id)) {
			found = true;
			i->increment();
		}
	}
	if (!found) {
		items.push_back(item);
	}
	
}

void Inventory::drawItems() {
	for (auto item : items) {
		item->drawIcon();
	}
}

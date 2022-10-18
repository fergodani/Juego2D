#include "Inventory.h"

Inventory::Inventory() {
	this->money = 0;
	this->wood = 0;
}


void Inventory::addItem(Item* item) {
	items.push_back(item);
}

void Inventory::drawItems() {
	for (auto item : items) {
		item->drawIcon();
	}
}

#include "Inventory.h"

Inventory::Inventory(Game* game) {
	this->money = 0;
	this->wood = 0;
	addItem(new Axe(game));
	addItem(new Hoe(game));
	addItem(new WateringCan(game));
	addItem(new Seed(game));
	selectedItem = items.at(index);
	frame = new Actor("res/frame.png", selectedItem->x, selectedItem->y, 16, 16, game);
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
	float gap = 0.15;
	for (auto item : items) {
		item->x = WIDTH * gap;
		item->y = HEIGHT * 0.90;
		item->draw();
		if (item->id == selectedItem->id) {
			frame->x = item->x;
			frame->y = item->y;
			frame->draw();
		}
		gap += 0.1;
	}

}

void Inventory::action() {
	selectedItem->action();
}

void Inventory::nextItem() {
	int i = ++index % (sizeof(items) / sizeof(int));
	selectedItem = items.at(i);
}

void Inventory::incrementMoney() {
	money++;
}

void Inventory::decrementMoney(int value) {
	money -= value;
}

void Inventory::incrementStone() {
	stone++;
}

void Inventory::decrementStone(int value) {
	stone -= value;
}
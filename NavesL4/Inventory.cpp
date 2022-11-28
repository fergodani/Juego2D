#include "Inventory.h"

Inventory::Inventory(Game* game) {
	addItem(new Axe(game));
	addItem(new Hoe(game));
	addItem(new WateringCan(game));
	addItem(new Seed(game));
	selectedItem = items.at(index);
	frame = new Actor("res/frame.png", selectedItem->x, selectedItem->y, 16, 16, game);
	backgroundWood = new Actor("res/wood.png",
		WIDTH * 0.05, HEIGHT * 0.10, 16, 16, game);
	backgroundRock = new Actor("res/stoneIcon.png",
		WIDTH * 0.05, HEIGHT * 0.20, 16, 16, game);
	backgroundCoin = new Actor("res/coin.png",
		WIDTH * 0.05, HEIGHT * 0.30, 16, 16, game);
	textWood = new Text("hola", WIDTH * 0.10, HEIGHT * 0.10, 14, 33, game);

	textRock = new Text("hola", WIDTH * 0.10, HEIGHT * 0.20, 14, 33, game);

	textCoin = new Text("hola", WIDTH * 0.10, HEIGHT * 0.30, 14, 33, game);
	textCoin->content = to_string(money);
	textRock->content = to_string(stone);
	textWood->content = to_string(wood);
}


void Inventory::addItem(Item* item) {
	bool found = false;
	for (auto const& i : items) {
		if (i->id._Equal(item->id)) {
			found = true;
			i->increment();
			item->~Item();
		}
	}
	if (!found) {
		items.push_back(item);
		numOfItems++;
	}
	
}

void Inventory::drawItems() {
	float gap = 0.15;
	for (auto item : items) {
		//if (item->cuantity <= 0)
			//continue;
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
	backgroundCoin->draw();
	backgroundRock->draw();
	backgroundWood->draw();
	textCoin->draw();
	textRock->draw();
	textWood->draw();
}

void Inventory::beginAction() {
	selectedItem->beginAction();
}

void Inventory::endAction() {
	selectedItem->endAction();
}

void Inventory::nextItem() {
	int i = ++index % numOfItems;
	selectedItem = items.at(i);
}

void Inventory::previousItem() {
	int i = --index % numOfItems;
	if (i < 0) {
		i = numOfItems - 1;
		index = i;
	}
	selectedItem = items.at(i);
}

void Inventory::incrementMoney() {
	money++;
	textCoin->content = to_string(money);
}

void Inventory::decrementMoney(int value) {
	money -= value;
	textCoin->content = to_string(money);
}

void Inventory::incrementStone() {
	stone++;
	textRock->content = to_string(stone);
}

void Inventory::decrementStone(int value) {
	stone -= value;
	textRock->content = to_string(stone);
}

void Inventory::incrementWood() {
	wood++;
	textWood->content = to_string(wood);
}

void Inventory::decrementWood(int value) {
	wood -= value;
	textWood->content = to_string(wood);
}
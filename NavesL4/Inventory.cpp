#include "Inventory.h"

Inventory::Inventory(Game* game) {
	this->game = game;
	Axe* axe = new Axe(game);
	axe->isWithoutQuantity = true;
	Hoe* hoe = new Hoe(game);
	hoe->isWithoutQuantity = true;
	WateringCan* waterCan = new WateringCan(game);
	waterCan->isWithoutQuantity = true;
	addItem(axe);
	addItem(hoe);
	addItem(waterCan);
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

	toolSwap = Audio::createAudio("res/toolSwap.wav", false);
}


void Inventory::addItem(Item* item) {
	bool found = false;
	int count = 0;
	for (auto const& i : items) {
		if (i->id._Equal(item->id)) {
			found = true;
			i->increment();
			quantities.at(count)->content = to_string(i->cuantity);
			item->~Item();
		}
		if(i->isWithoutQuantity == false)
			count++;
	}
	if (!found) {
		items.push_back(item);
		if(item->isWithoutQuantity == false)
			quantities.push_back(new Text("hola", WIDTH * 0.10, HEIGHT * 0.10, 4, 9, game));
		numOfItems++;
	}
	
}

void Inventory::drawItems() {
	float gap = 0.15;
	int count = 0;
	for (auto item : items) {
		item->x = WIDTH * gap;
		item->y = HEIGHT * 0.90;
		item->draw();
		if (item->isWithoutQuantity == false) {
			Text* text = quantities.at(count);
			text->content = to_string(item->cuantity);
			text->x = item->x + item->width / 2;
			text->y = item->y + item->height / 2;
			text->draw();
			count++;
		}
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
	toolSwap->play();
	int i = ++index % numOfItems;
	selectedItem = items.at(i);
}

void Inventory::previousItem() {
	toolSwap->play();
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
#include "Item.h"
#include "GameLayer.h"

Item::Item(string fileName, float x, float y, float width, float height, Game* game, int cuantity, float price)
	: Actor(fileName, x, y, width, height, game) {
	this->cuantity = cuantity;
	this->price = price;
	icon =  new Actor(fileName,
		WIDTH * 0.5, HEIGHT * 0.90, 16, 16, game);
}

void Item::drawIcon() {
	icon->draw(0, 0);
}

void Item::action() {
	// TODO
}
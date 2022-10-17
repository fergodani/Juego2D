#include "Item.h"
#include "GameLayer.h"

Item::Item(string fileName, float x, float y, float width, float height, Game* game, int cuantity, float price, list<Item*> itemPrice)
	: Actor(fileName, x, y, width, height, game) {
	this->cuantity = cuantity;
	this->price = price;
	this->itemPrice = itemPrice;
}
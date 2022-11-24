#pragma once
#include "Item.h"
#include "Axe.h"
#include "Hoe.h"
#include "WateringCan.h"
#include "Seed.h"
#include <list>
#include <vector>

class Inventory
{
public:
	Inventory(Game* game);
	int wood = 2;
	int stone = 2;
	int money = 2;
	vector<Item*> items;
	Item* selectedItem;
	void addItem(Item* item);
	void drawItems();
	void beginAction();
	void endAction();
	void nextItem();
	void previousItem();
	void incrementMoney();
	void decrementMoney(int value);
	void incrementStone();
	void decrementStone(int value);
	void incrementWood();
	void decrementWood(int value);
	int index = 0;
	int numOfItems = 0;
	Actor* frame;

	Actor* backgroundWood;
	Text* textWood;
	Actor* backgroundRock;
	Text* textRock;
	Actor* backgroundCoin;
	Text* textCoin;
};


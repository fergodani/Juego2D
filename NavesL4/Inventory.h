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
	int wood;
	int money;
	vector<Item*> items;
	Item* selectedItem;
	void addItem(Item* item);
	void drawItems();
	void action();
	void nextItem();
	void incrementMoney();
	void decrementMoney(int value);
	int index = 0;
	Actor* frame;
};


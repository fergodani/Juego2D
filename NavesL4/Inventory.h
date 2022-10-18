#pragma once
#include "Item.h"
#include <list>

class Inventory
{
public:
	Inventory();
	int wood;
	int money;
	list<Item*> items;
	void addItem(Item* item);
	void drawItems();

};


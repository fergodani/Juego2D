#pragma once
#include "Item.h"
#include "Axe.h"
#include "Hoe.h"
#include "WateringCan.h"
#include "Seed.h"
#include "Audio.h"
#include "Text.h"
#include <list>
#include <vector>

class Inventory
{
public:
	Inventory(Game* game);
	Game* game;
	int wood = 6;
	int stone = 6;
	int money = 49;
	vector<Item*> items;
	vector<Text*> quantities;
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

	Audio* toolSwap;

	Actor* uiVertical;
};


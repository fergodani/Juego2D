#pragma once
#include "Actor.h"
#include "Item.h"
#include "Sprinkler.h"
#include "Harvester.h"
#include "Text.h"
#include "Inventory.h"

class Recipe : public Actor
{
public:
	Recipe(float x, float y, int woodCuantity, int stoneCuantity, int moneyCuantity, Item* item, Game* game);
	Item* item;
	int woodCuantity;
	int stoneCuantity;
	int moneyCuantity;
	Text* woodText;
	Text* stoneText;
	Text* moneyText;
	Actor* woodBackground;
	Actor* stoneBackground;
	Actor* moneyBackground;
	int disabledTime = 0;
	int disabledCadence = 10;
	void draw(float scrollX = 0, float scrollY = 0) override;
	void update();
	Item* getItem(Inventory* inventory);
};


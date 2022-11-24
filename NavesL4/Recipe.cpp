#include "Recipe.h"

Recipe::Recipe(float x, float y, int woodCuantity, int stoneCuantity, int moneyCuantity, Item* item, Game* game)
	: Actor("", x, y, 16, 16, game) {
	this->x = x;
	this->y = y;
	this->woodCuantity = woodCuantity;
	this->stoneCuantity = stoneCuantity;
	this->moneyCuantity = moneyCuantity;
	this->item = item;
	this->item->y -= 5;
	moneyBackground = new Actor("res/coinRecipe.png",
		x - 8, y + 4, 8, 8, game);
	woodBackground = new Actor("res/woodRecipe.png",
		x, y + 4, 8, 8, game);
	stoneBackground = new Actor("res/stoneIconRecipe.png",
		x + 8, y + 4, 8, 8, game);

	stoneText = new Text("hola", stoneBackground->x + 4, stoneBackground->y + 18, 4, 9, game);
	stoneText->content = to_string(stoneCuantity);
	woodText = new Text("hola", woodBackground->x + 4, woodBackground->y + 18, 4, 9, game);
	woodText->content = to_string(woodCuantity);
	moneyText = new Text("hola", moneyBackground->x + 4, moneyBackground->y + 18, 4, 9, game);
	moneyText->content = to_string(moneyCuantity);
}

void Recipe::draw(float scrollX, float scrollY) {
	item->draw(scrollX, scrollY);
	moneyBackground->draw(scrollX, scrollY);
	woodBackground->draw(scrollX, scrollY);
	stoneBackground->draw(scrollX, scrollY);
	stoneText->draw(scrollX, scrollY);
	moneyText->draw(scrollX, scrollY);
	woodText->draw(scrollX, scrollY);
}

Item* Recipe::getItem(Inventory* inventory) {
	if (inventory->money >= moneyCuantity && inventory->wood >= woodCuantity && inventory->stone >= stoneCuantity) {
		
		Sprinkler* newItem1 = dynamic_cast<Sprinkler*>(item);
		if (newItem1 != NULL && disabledTime == 0) {
			disabledTime = disabledCadence;
			inventory->decrementMoney(moneyCuantity);
			inventory->decrementWood(woodCuantity);
			inventory->decrementStone(stoneCuantity);
			return new Sprinkler(newItem1->x, newItem1->y, game);
		}
		Harvester* newItem2 = dynamic_cast<Harvester*>(item);
		if (newItem2 != NULL && disabledTime == 0) {
			disabledTime = disabledCadence;
			inventory->decrementMoney(moneyCuantity);
			inventory->decrementWood(woodCuantity);
			inventory->decrementStone(stoneCuantity);
			return new Harvester(newItem2->x, newItem2->y, game);
		}
		return NULL;
	}
	else
		return NULL;
}

void Recipe::update() {
	if (disabledTime > 0)
		disabledTime--;
}
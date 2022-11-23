#pragma once
#include "Item.h"
#include "Text.h"
class Seed : public Item
{
public:
	Seed(Game* game);
	Text* textCuantity;
	void beginAction() override;
	void increment() override;
	void decrement() override;
	void draw(float scrollX = 0, float scrollY = 0) override;
};


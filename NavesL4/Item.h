#pragma once
#include "Actor.h"

class Item : public Actor
{
public:
	Item(string fileName, float x, float y, float width, float height, Game* game, int cuantity, float price);
	virtual void action();
	int cuantity;
	float price;
};


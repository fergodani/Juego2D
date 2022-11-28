#pragma once
#include "Item.h"	

class Sprinkler : public Item
{
public:
	Sprinkler(float x, float y, Game* game);
	void beginAction() override;
	void water();
};


#pragma once
#include "Item.h"
class Seed : public Item
{
public:
	Seed(Game* game);
	void action() override;
};


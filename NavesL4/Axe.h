#pragma once
#include "Item.h"
class Axe : public Item
{
public:
	Axe(Game* game);
	void action() override;
};


#pragma once
#include "Item.h"
class Hoe : public Item
{
public:
	Hoe(Game* game);
	void action() override;
};



#pragma once
#include "Item.h"
class Hoe : public Item
{
public:
	Hoe(Game* game);
	void beginAction() override;
	void endAction() override;
};



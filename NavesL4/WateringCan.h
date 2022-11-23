#pragma once
#include "Item.h"
class WateringCan : public Item
{
public:
	WateringCan(Game* game);
	void beginAction() override;
	void endAction() override;
};


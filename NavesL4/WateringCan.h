#pragma once
#include "Item.h"
#include "Audio.h"

class WateringCan : public Item
{
public:
	WateringCan(Game* game);
	void beginAction() override;
	void endAction() override;
	Audio* audioWater;
};


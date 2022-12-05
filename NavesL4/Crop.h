#pragma once
#include "Actor.h"
class Crop : public Actor
{
public:
	Crop(float x, float y, Game* game);
	~Crop();
	enum CropState { stage1, stage2, stage3, stage4 };
	CropState state = stage1;
	void nextStage();
	void update();
	bool canHarvest();
	string filename;
	int growTime = 600;
	int growCadence = 600;
};


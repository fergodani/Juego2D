#pragma once
#include "Actor.h"
class Crop : public Actor
{
public:
	Crop(float x, float y, Game* game);
	enum CropState { stage1, stage2, stage3, stage4 };
	CropState state = stage1;
	void nextStage();
	void update();
	string filename;
	int growTime = 250;
	int growCadence = 250;
};


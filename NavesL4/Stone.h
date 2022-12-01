#pragma once
#include "Actor.h"
#include "Audio.h"

class Stone : public Actor
{
public:
	Stone(string fileName, float x, float y, Game* game);
	~Stone();
	Audio* audioStone;
};


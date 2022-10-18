#pragma once
#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, float width, float height, bool canSpawn, Game* game);
	bool canSpawn;
};


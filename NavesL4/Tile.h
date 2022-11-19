#pragma once
#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, float width, float height, bool canSpawn, Game* game);
	virtual void draw(float scrollX = 0, float scrollY = 0);
	bool canSpawn;
	string filename;
};


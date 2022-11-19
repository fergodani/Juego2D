#pragma once
#include "Tile.h"
#include "Grass.h"
class GroundTile : public Tile
{
public:
	GroundTile(float x, float y, float width, float height, bool canSpawn, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void water();
	void plow();
	enum GroundState {normal, plowed, watered};
	Tile* groundPlowed;
	Grass* plantedGrass;
	bool isPlowed = false;
};


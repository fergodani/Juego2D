#pragma once
#include "Tile.h"
#include "Grass.h"
#include "Seed.h"
#include "Stone.h"

class GroundTile : public Tile
{
public:
	GroundTile(float x, float y, float width, float height, bool canSpawn, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void water();
	void plow();
	void plant();
	enum GroundState {normal, plowed, watered};
	Tile* groundPlowed;
	Seed* plantedSeed;
	Grass* placedGrass;
	Stone* placedStone;
	void placeStone(Stone* stone);
	void placeGrass(Grass* grass);
	void recolectGrass();
	bool isPlowed = false;
	bool isGrassPlaced = false;
	bool isStonePlaced = false;
	bool isSeedPlanted = false;
};


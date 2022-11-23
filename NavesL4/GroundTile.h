#pragma once
#include "Tile.h"
#include "Grass.h"
#include "Crop.h"
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
	Crop* plantedCrop;
	Grass* placedGrass;
	Stone* placedStone;
	void placeStone(Stone* stone);
	void placeGrass(Grass* grass);
	void recolectGrass();
	void recolectStone();
	bool isPlowed = false;
	bool isGrassPlaced = false;
	bool isStonePlaced = false;
	bool isCropPlanted = false;
	bool isWatered = false;
	int wateredTime = 0;
	int wateredCadence = 200;
	void update();
};


#pragma once
#include "Tile.h"
#include "Grass.h"
#include "Crop.h"
#include "Stone.h"
#include "Tree.h"

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
	Tree* placedTree;
	void placeStone(Stone* stone);
	void placeGrass(Grass* grass);
	void placeTree(Tree* tree);
	void recolectGrass();
	void recolectStone();
	void recolectTree();
	bool isPlowed = false;
	bool isGrassPlaced = false;
	bool isStonePlaced = false;
	bool isCropPlanted = false;
	bool isTreePlaced = false;
	bool isWatered = false;
	int wateredTime = 0;
	int wateredCadence = 500;
	void update();
	bool canSpawn();
};


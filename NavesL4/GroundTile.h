#pragma once
#include "Tile.h"
#include "Grass.h"
#include "Crop.h"
#include "Stone.h"
#include "Tree.h"
#include "Item.h"
#include "Sprinkler.h"
#include "Harvester.h"

class GroundTile : public Tile
{
public:
	GroundTile(float x, float y, float width, float height, bool canSpawn, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void water();
	void plow();
	void plant();
	Tile* groundPlowed;
	Crop* plantedCrop;
	Grass* placedGrass;
	Stone* placedStone;
	Tree* placedTree;
	Item* placedItem;
	void placeStone(Stone* stone);
	void placeGrass(Grass* grass);
	void placeTree(Tree* tree);
	void placeItem(Item* item);
	void recolectGrass();
	void recolectStone();
	void recolectTree();
	void harvest();
	bool isPlowed = false;
	bool isGrassPlaced = false;
	bool isStonePlaced = false;
	bool isCropPlanted = false;
	bool isTreePlaced = false;
	bool isItemPlaced = false;
	bool isWatered = false;
	int wateredTime = 0;
	int wateredCadence = 500;
	int itemActionTime = 0;
	int itemActionCadence = 20;
	void update();
	bool canSpawn();
};


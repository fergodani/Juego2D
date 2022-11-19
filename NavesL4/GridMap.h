#pragma once
#include <list>
#include "Tile.h"
class GridMap
{
public:
	GridMap();
	list<Tile*> tiles;
	list<Tile*> waterTiles;
	list<Tile*> detailTiles;
	//void addTile(Tile* tile);
	//void addWaterTile(Tile* tile);
	Tile* getCollisionTile(float x, float y);
	int rows;
	int columns;
};


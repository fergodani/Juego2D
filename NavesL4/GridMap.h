#pragma once
#include <list>
#include "Tile.h"
class GridMap
{
public:
	GridMap(Game* game);
	Game* game;
	list<Tile*> tiles;
	list<Tile*> waterTiles;
	list<Tile*> detailTiles;
	//void addTile(Tile* tile);
	//void addWaterTile(Tile* tile);
	Tile* getCollisionTile(float x, float y, int orientation);
	void update();
	int rows;
	int columns;
};


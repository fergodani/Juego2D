#include "GridMap.h"
GridMap::GridMap(Game* game) {
	this->game = game;
}

Tile* GridMap::getCollisionTile(float x, float y, int orientation) {
	int xAxis = (int)(x / 16);
	int yAxis = (int)(y / 16);
	if (orientation == game->orientationLeft) {
		xAxis -= 2;
	}
	else if (orientation == game->orientationUp) {
		xAxis -= 1;
		yAxis -= 1;
	}
	else if (orientation == game->orientationDown) {
		xAxis -= 1;
		yAxis += 1;
	}
	int index = yAxis * (columns+1) + xAxis + 1;
	cout << "x: " << xAxis << " y: " << yAxis << endl;
	
	Tile* tileSelected = nullptr;
	int count = 0;
	for (auto const& tile : tiles) {
		if (count == index)
			tileSelected = tile;
		count++;
	}
	return tileSelected;
}
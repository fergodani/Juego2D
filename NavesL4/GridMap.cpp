#include "GridMap.h"
GridMap::GridMap() {
}

void GridMap::getCollisionTile(float x, float y) {
	int xAxis = (int)(x / 16);
	int yAxis = (int)(y / 16);
	int index = yAxis * (columns+1) + xAxis + 1;
	cout << "x: " << xAxis << " y: " << yAxis << endl;
	
	Tile* tileSelected;
	int count = 0;
	for (auto const& tile : tiles) {
		if (count == index)
			tileSelected = tile;
		count++;
	}

}
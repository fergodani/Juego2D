#include "GroundTile.h"
GroundTile::GroundTile(float x, float y, float width, float height, bool canSpawn, Game* game)
	: Tile("res/hierba1.png", x, y, width, height, canSpawn, game) {
	
}

void GroundTile::plow() {
	if (isPlowed == false) {
		groundPlowed = new Tile("res/plowed.png", this->x, this->y, 16, 16, false, game);
		isPlowed = true;
	}
}

void GroundTile::draw(float scrollX, float scrollY) {
	Tile::draw(scrollX, scrollY);
	if (isPlowed == true) {
		groundPlowed->draw(scrollX, scrollY);
	}
}
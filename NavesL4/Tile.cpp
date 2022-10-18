#include "Tile.h"

Tile::Tile(string filename, float x, float y, float width, float height, bool canSpawn, Game* game)
	: Actor(filename, x, y, width, height, game) {
	this->canSpawn = canSpawn;
}

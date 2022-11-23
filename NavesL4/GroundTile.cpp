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
	if (isGrassPlaced == true) {
		placedGrass->draw(scrollX, scrollY);
	}
	if (isStonePlaced == true) {
		placedStone->draw(scrollX, scrollY);
	}
	if (isCropPlanted == true) {
		plantedCrop->draw(scrollX, scrollY);
	}
}

void GroundTile::placeGrass(Grass* grass) {
	if (isGrassPlaced == false && isPlowed == false && isStonePlaced == false) {
		isGrassPlaced = true;
		placedGrass = grass;
	}
}

void GroundTile::recolectGrass() {
	if (isGrassPlaced == true) {
		isGrassPlaced = false;
		placedGrass->~Grass();
	}
}

void GroundTile::recolectStone() {
	if (isStonePlaced == true) {
		isStonePlaced = false;
		placedStone->~Stone();
	}
}

void GroundTile::placeStone(Stone* stone) {
	if (isStonePlaced == false && isPlowed == false && isGrassPlaced == false) {
		isStonePlaced = true;
		placedStone = stone;
	}
}

void GroundTile::plant() {
	if(isPlowed == true) {
		plantedCrop = new Crop(this->x, this->y - this->height/2 + 3, game);
		isCropPlanted = true;
	}
}

void GroundTile::water() {
	if (isWatered == false && isPlowed == true) {
		isWatered = true;
		wateredTime = wateredCadence;
		groundPlowed->texture = game->getTexture("res/plowed_watered.png");
	}
}

void GroundTile::update() {
	if (isWatered == true) {
		if (isCropPlanted == true)
			plantedCrop->update();
		if (wateredTime > 0)
			wateredTime--;
		else {
			isWatered = false;
			groundPlowed->texture = game->getTexture("res/plowed.png");
		}
	}
}
#include "GroundTile.h"
GroundTile::GroundTile(float x, float y, float width, float height, bool canSpawn, Game* game)
	: Tile("res/hierba1.png", x, y, width, height, canSpawn, game) {
	audioPlow = Audio::createAudio("res/hoeHit.wav", false);
	audioHarvest = Audio::createAudio("res/hoe.wav", false);
	audioItem = Audio::createAudio("res/axe.wav", false);
}

GroundTile::GroundTile(string filename, float x, float y, float width, float height, bool canSpawn, Game* game)
	: Tile("res/hierba1.png", x, y, width, height, canSpawn, game) {
	audioPlow = Audio::createAudio("res/hoeHit.wav", false);
	audioHarvest = Audio::createAudio("res/hoe.wav", false);
	this->texture = game->getTexture(filename);
}

void GroundTile::plow() {
	if (isPlowed == false && isGrassPlaced == false && isStonePlaced == false && isTreePlaced == false && isItemPlaced == false) {
		audioPlow->play();
		groundPlowed = new Tile("res/plowed.png", this->x, this->y, 16, 16, false, game);
		isPlowed = true;
		if (isDetailPlaced) {
			isDetailPlaced = false;
			placedDetail->~Actor();
		}
	}
}

void GroundTile::removePlow() {
	if (isPlowed) {
		audioPlow->play();
		groundPlowed->~Tile();
		isPlowed = false;
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
	if (isTreePlaced == true) {
		placedTree->draw(scrollX, scrollY);
	}
	if (isCropPlanted == true) {
		plantedCrop->draw(scrollX, scrollY);
	}
	if (isItemPlaced == true) {
		placedItem->draw(scrollX, scrollY);
	}
	if (isDetailPlaced == true) {
		placedDetail->draw(scrollX, scrollY);
	}
}

bool GroundTile::placeGrass(Grass* grass) {
	if (isGrassPlaced == false && isPlowed == false && isStonePlaced == false && isTreePlaced == false && isItemPlaced == false && (isDetailPlaced && isRemovableDetail || !isDetailPlaced) ){
		isGrassPlaced = true;
		placedGrass = grass;
		if (isDetailPlaced) {
			isDetailPlaced = false;
			placedDetail->~Actor();
		}
		return true;
	}
	return false;
}

void GroundTile::placeItem(Item* item) {
	if (isGrassPlaced == false && isPlowed == false && isStonePlaced == false && isTreePlaced == false && isItemPlaced == false && (isDetailPlaced && isRemovableDetail || !isDetailPlaced)) {
		isItemPlaced = true;
		placedItem = item;
		if (isDetailPlaced) {
			isDetailPlaced = false;
			placedDetail->~Actor();
		}
	}
}

void GroundTile::removeItem() {
	if (isItemPlaced) {
		audioItem->play();
		isItemPlaced = false;
		placedItem->~Item();
	}
}

void GroundTile::recolectGrass() {
	if (isGrassPlaced == true) {
		audioHarvest->play();
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

bool GroundTile::placeStone(Stone* stone) {
	if (isStonePlaced == false && isPlowed == false && isGrassPlaced == false && isTreePlaced == false && isItemPlaced == false && (isDetailPlaced && isRemovableDetail || !isDetailPlaced)) {
		isStonePlaced = true;
		placedStone = stone;
		if (isDetailPlaced) {
			isDetailPlaced = false;
			placedDetail->~Actor();
		}
		return true;
	}
	return false;
}

bool GroundTile::placeTree(Tree* tree) {
	if (isStonePlaced == false && isPlowed == false && isGrassPlaced == false && isTreePlaced == false && isItemPlaced == false && (isDetailPlaced && isRemovableDetail || !isDetailPlaced)) {
		isTreePlaced = true;
		placedTree = tree;
		if (isDetailPlaced) {
			isDetailPlaced = false;
			placedDetail->~Actor();
		}
		return true;
	}
	return false;
}

void GroundTile::recolectTree() {
	if (isTreePlaced == true) {
		isTreePlaced = placedTree->nextState();
		if (isTreePlaced == false)
			placedTree->~Tree();
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
	if (isTreePlaced == true)
		placedTree->update();
	if (isItemPlaced == true && itemActionTime == 0) {
		itemActionTime = itemActionCadence;
		Sprinkler* sprinkler = dynamic_cast<Sprinkler*>(placedItem);
		if (sprinkler != NULL)
			sprinkler->water();
		Harvester* harvester = dynamic_cast<Harvester*>(placedItem);
		if (harvester != NULL)
			harvester->harvest();
	}
	if (itemActionTime > 0)
		itemActionTime--;
}

bool GroundTile::canSpawn() {
	return !(isStonePlaced || isPlowed || isGrassPlaced || isCropPlanted || isWatered || isTreePlaced || isItemPlaced);
}

void GroundTile::harvest() {
	if (isCropPlanted == true) {
		if (plantedCrop->canHarvest()) {
			audioHarvest->play();
			isCropPlanted = false;
			plantedCrop->~Crop();
		}
	}
}

void GroundTile::placeDetail(Actor* actor, bool isRemovable) {
	if (isStonePlaced == false && isGrassPlaced == false && isTreePlaced == false && !isDetailPlaced) {
		isDetailPlaced = true;
		placedDetail = actor;
		if(!isRemovable)
			placedDetail->y = this->y - this->height / 2;
		isRemovableDetail = isRemovable;
	}
}
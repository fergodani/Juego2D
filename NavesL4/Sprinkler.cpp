#include "Sprinkler.h"
#include "GameLayer.h"

Sprinkler::Sprinkler(float x, float y, Game* game)
	: Item("res/sprinkler2.png", x, y, 16, 16, game, 1, 5) {
	id = "sprinkler";
}

void Sprinkler::beginAction() {
	if (cuantity > 0) {
		GameLayer* gameLayer = (GameLayer*)game->gameLayer;
		GroundTile* tileSelected = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(gameLayer->player->x, gameLayer->player->y, gameLayer->player->orientation));
		if (tileSelected == NULL || tileSelected->canSpawn() == false)
			return;
		Sprinkler* newSprinkler = new Sprinkler(tileSelected->x, tileSelected->y, game);
		tileSelected->placeItem(newSprinkler);
		decrement();
		cout << "Sprinkler placed" << endl;
	}
}

void Sprinkler::water() {
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	GroundTile* downTile = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(this->x, this->y, gameLayer->game->orientationDown));
	GroundTile* upTile = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(this->x, this->y, gameLayer->game->orientationUp));
	GroundTile* leftTile = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(this->x, this->y, gameLayer->game->orientationLeft));
	GroundTile* rightTile = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(this->x, this->y, gameLayer->game->orientationRight));
	downTile->water();
	upTile->water();
	leftTile->water();
	rightTile->water();
}
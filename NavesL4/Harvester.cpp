#include "Harvester.h"
#include "GameLayer.h"

Harvester::Harvester(float x, float y, Game* game)
	: Item("res/harvester.png", x, y, 16, 26, game, 1, 5) {
	id = "harvester";
}

void Harvester::beginAction() {
	if (cuantity > 0) {
		GameLayer* gameLayer = (GameLayer*)game->gameLayer;
		GroundTile* tileSelected = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(gameLayer->player->x, gameLayer->player->y, gameLayer->player->orientation));
		if (tileSelected == NULL || tileSelected->canSpawn() == false)
			return;
		Harvester* harvester = new Harvester(tileSelected->x, tileSelected->y, game);
		tileSelected->placeItem(harvester);
		decrement();
		cout << "Harvester placed" << endl;
	}
}

void Harvester::harvest() {
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	GroundTile* downTile = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(this->x, this->y, gameLayer->game->orientationDown));
	GroundTile* upTile = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(this->x, this->y, gameLayer->game->orientationUp));
	GroundTile* leftTile = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(this->x, this->y, gameLayer->game->orientationLeft));
	GroundTile* rightTile = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(this->x, this->y, gameLayer->game->orientationRight));
	downTile->harvest();
	upTile->harvest();
	leftTile->harvest();
	rightTile->harvest();
}
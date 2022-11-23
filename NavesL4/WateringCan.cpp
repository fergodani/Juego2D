#include "WateringCan.h"
#include "GameLayer.h"
WateringCan::WateringCan(Game* game)
	: Item("res/water_can.png", 50, 50, 16, 16, game, 1, 0) {
	id = "water_can";
}

void WateringCan::action() {
	cout << "Water can action" << endl;
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->player->state = game->stateWatering;
	gameLayer->player->water();
	GroundTile* tileSelected = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(gameLayer->player->x, gameLayer->player->y, gameLayer->player->orientation));
	if (tileSelected == NULL)
		return;
	tileSelected->water();
}
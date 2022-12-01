#include "WateringCan.h"
#include "GameLayer.h"
WateringCan::WateringCan(Game* game)
	: Item("res/water_can.png", 50, 50, 16, 16, game, 1, 0) {
	id = "water_can";
	audioWater = Audio::createAudio("res/water.wav", false);
}

void WateringCan::beginAction() {
	audioWater->play();
	cout << "Water can action begins" << endl;
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->player->state = game->stateWatering;
	gameLayer->player->water();
}

void WateringCan::endAction() {
	cout << "Water can action ends" << endl;
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	GroundTile* tileSelected = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(gameLayer->player->x, gameLayer->player->y, gameLayer->player->orientation));
	if (tileSelected == NULL)
		return;
	tileSelected->water();
}
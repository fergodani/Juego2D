#include "Hoe.h"
#include "GameLayer.h"
#include "GroundTile.h"
Hoe::Hoe(Game* game)
	: Item("res/hoe.png", 50, 50, 16, 16, game, 1, 0) {
	id = "hoe";
}

void Hoe::beginAction() {
	cout << "Hoe action begins" << endl;
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->player->state = game->statePlowing;
	gameLayer->player->plow();
}

void Hoe::endAction() {
	cout << "Hoe action ends" << endl;
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	GroundTile* tileSelected = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(gameLayer->player->x, gameLayer->player->y, gameLayer->player->orientation));
	if (tileSelected == NULL)
		return;
	//cout << tileSelected->filename << endl;
	if (tileSelected->isStonePlaced == true) {
		tileSelected->recolectStone();
	}
	else
		tileSelected->plow();
}
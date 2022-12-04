#include "Axe.h"
#include "GameLayer.h"
Axe::Axe(Game* game)
	: Item("res/axe.png", 50, 50, 16, 16, game, 1, 0) {
	id = "axe";
}

void Axe::beginAction() {
	cout << "Axe action begins" << endl;
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->player->state = game->stateChopping;
	gameLayer->player->chop();
}

void Axe::endAction() {
	cout << "Axe action ends" << endl;
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	GroundTile* tileSelected = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(gameLayer->player->x, gameLayer->player->y, gameLayer->player->orientation));
	if (tileSelected == NULL)
		return;
	//cout << tileSelected->filename << endl;
	if (tileSelected->isGrassPlaced == true)
		tileSelected->recolectGrass();
	else if (tileSelected->isTreePlaced == true)
		tileSelected->recolectTree();
	else if (tileSelected->isCropPlanted == true) {
		tileSelected->harvest();
	}
	else if (tileSelected->isItemPlaced == true) {
		gameLayer->player->inventory->addItem(tileSelected->placedItem);
		tileSelected->removeItem();
	}
}
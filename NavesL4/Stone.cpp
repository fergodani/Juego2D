#include "Stone.h"
#include "GameLayer.h"

Stone::Stone(string fileName, float x, float y, Game* game)
	: Actor(fileName, x, y, 16, 16, game) {
}

Stone::~Stone() {
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->stoneList.remove(this);
	gameLayer->space->removeStaticActor(this);
	//gameLayer->player->inventory->addItem(new Rock(game));
}

#include "Stone.h"
#include "GameLayer.h"

Stone::Stone(string fileName, float x, float y, Game* game)
	: Actor(fileName, x, y, 16, 16, game) {
	audioStone = Audio::createAudio("res/stone.wav", false);
}

Stone::~Stone() {
	audioStone->play();
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->numberOfStone--;
	gameLayer->player->inventory->incrementStone();
}

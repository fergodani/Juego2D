#include "Actor.h"
#include "Grass.h"
#include "GameLayer.h"
#include "Seed.h"


Grass::Grass(float x, float y, Game* game)
	: Actor("res/hierbajo.png", x, y, 16, 16, game) {
}

Grass::~Grass() {
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->player->inventory->addItem(new Seed(game));
	gameLayer->numberOfGrass--;
}
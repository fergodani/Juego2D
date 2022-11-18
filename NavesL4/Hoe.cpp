#include "Hoe.h"
#include "GameLayer.h"
Hoe::Hoe(Game* game)
	: Item("res/hoe.png", 50, 50, 16, 16, game, 1, 0) {
	id = "hoe";
}

void Hoe::action() {
	cout << "Hoe action" << endl;
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->player->state = game->statePlowing;
	gameLayer->player->plow();
}
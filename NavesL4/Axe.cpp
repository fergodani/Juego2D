#include "Axe.h"
#include "GameLayer.h"
Axe::Axe(Game* game)
	: Item("res/axe.png", 50, 50, 16, 16, game, 1, 0) {
	id = "axe";
}

void Axe::action() {
	cout << "Axe action" << endl;
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->player->state = game->stateChopping;
	gameLayer->player->chop();
}
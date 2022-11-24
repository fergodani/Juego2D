#include "Crop.h"
#include "GameLayer.h"

Crop::Crop(float x, float y, Game* game)
	: Actor("res/stage1.png", x, y, 16, 16, game) {
	filename = "res/stage1.png";
}

Crop::~Crop() {
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->player->inventory->incrementMoney();
	gameLayer->textCoin->content = to_string(gameLayer->player->inventory->money);
}

void Crop::update() {
	if (growTime > 0)
		growTime--;
	else {
		nextStage();
		growTime = growCadence;
	}
}

void Crop::nextStage() {
	switch (state)
	{
	case Crop::stage1:
		state = stage2;
		filename = "res/stage2.png";
		this->texture = game->getTexture(filename);
		break;
	case Crop::stage2:
		state = stage3;
		filename = "res/stage3.png";
		this->texture = game->getTexture(filename);
		break;
	case Crop::stage3:
		filename = "res/stage4.png";
		this->texture = game->getTexture(filename);
		state = stage4;
		break;
	default:
		break;
	}
}

bool Crop::canHarvest() {
	return state == stage4;
}
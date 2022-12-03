#include "Tree.h"
#include "GameLayer.h"

Tree::Tree(float x, float y, Game* game)
	: Actor("res/tree.png", x, y, 30, 32, game) {
	audioChop = Audio::createAudio("res/axe.wav", false);
	aIdle = new Animation("res/treeAnim.png", width, height,
		576, 48, 7, 12, true, game);
}

Tree::~Tree() {
	audioChop->play();
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	gameLayer->numberOfTrees--;
	gameLayer->player->inventory->incrementWood();
}

void Tree::draw(float scrollX, float scrollY) {
	switch (state)
	{
	case Tree::entire:
		aIdle->draw(x - scrollX, y - scrollY);
		break;
	case Tree::chopped:	
		Actor::draw(scrollX, scrollY);
		break;
	default:
		break;
	}
}

bool Tree::nextState() {
	if (state == entire) {
		audioChop->play();
		state = chopped;
		GameLayer* gameLayer = (GameLayer*)game->gameLayer;
		gameLayer->player->inventory->incrementWood();
		texture = game->getTexture("res/chopped.png");
		this->height = 16;
		this->width = 16;
		this->y += 8;
		return true;
	}
	else
		return false;
}

void Tree::update() {
	aIdle->update();
}
#include "Seed.h"
#include "GameLayer.h"

Seed::Seed(Game* game)
	: Item("res/seed.png", WIDTH * 0.5, HEIGHT * 0.96, 16, 16, game, 0, 0) {
	id = "seed";
	textCuantity = new Text("hola", WIDTH * 0.10, HEIGHT * 0.10, 4, 9, game);
	textCuantity->content = to_string(cuantity);
}

void Seed::action() {
	GameLayer* gameLayer = (GameLayer*)game->gameLayer;
	GroundTile* tileSelected = dynamic_cast<GroundTile*>(gameLayer->gridMap->getCollisionTile(gameLayer->player->x, gameLayer->player->y, gameLayer->player->orientation));
	if (tileSelected == NULL || tileSelected->isPlowed == false)
		return;
	tileSelected->plant();

	cout << "Seed planted" << endl;
}

void Seed::draw(float scrollX, float scrollY) {
	textCuantity->x = this->x + this->width/2;
	textCuantity->y = this->y + this->height/2;
	Item::draw();
	textCuantity->draw();
}

void Seed::increment() {
	cuantity++;
	textCuantity->content = to_string(cuantity);
}

void Seed::decrement() {
	cuantity--;
	textCuantity->content = to_string(cuantity);
}
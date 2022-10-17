#include "Grass.h"


Grass::Grass(float x, float y, Game* game, int cuantity)
	: Item("res/hierbajo.png", x, y, 16, 16, game, cuantity, 15, {}) {
	
}
#include "Sprinkler.h"

Sprinkler::Sprinkler(float x, float y, Game* game)
	: Item("res/sprinkler.png", x, y, 16, 16, game, 1, 5) {
	id = "sprinkler";
}
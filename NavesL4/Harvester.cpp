#include "Harvester.h"

Harvester::Harvester(float x, float y, Game* game)
	: Item("res/harvester.png", x, y, 16, 26, game, 1, 5) {
	id = "harvester";
}
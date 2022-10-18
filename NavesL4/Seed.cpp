#include "Seed.h"

Seed::Seed(Game* game)
	: Item("res/seed.png", 50, 50, 16, 16, game, 1, 0) {
}

void Seed::action() {
	// TODO: plantarlas en el suelo
}
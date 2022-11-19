#pragma once

#include "Game.h"

class Text
{
public:
	Text(string content, float x, float y, float width, float height, Game* game);
	void draw();
	string content; // texto
	int x;
	int y;
	float width;
	float height;
	Game* game; // referencia al juego
};


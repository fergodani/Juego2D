#pragma once

#include "Layer.h"
#include "Player.h"

#include "Text.h"
#include "Tile.h"
#include "Pad.h"

#include "Audio.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	Actor* message;
	bool pause;
	// Elementos de interfaz
	SDL_GameController* gamePad;
	Pad* pad;
	Actor* buttonJump;
	Actor* buttonShoot;

	Space* space;
	float scrollX;
	float scrollY;
	int mapHeight;
	int mapWidth;
	list<Tile*> tiles;

	Audio* audioBackground;
	Text* textPoints;
	int points;
	int newEnemyTime = 0;
	Player* player;

	bool controlContinue = false;
	bool controlChop = false;
	int controlMoveY = 0;
	int controlMoveX = 0;


};


#pragma once

#include "Layer.h"
#include "Player.h"

#include "Text.h"
#include "Tile.h"
#include "GroundTile.h"
#include "Pad.h"
#include "Grass.h"
#include "Item.h"
#include "Stone.h"
#include "GridMap.h"
#include "Tree.h"
#include "Recipe.h"
#include "Sprinkler.h"
#include "Harvester.h"

#include "Audio.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

#define PUNTOS 25

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
	//list<Tile*> tiles;

	Audio* audioBackground;
	Player* player;

	bool controlContinue = false;
	bool controlChop = false;
	bool controlPlow = false;
	bool controlWater = false;
	bool controlAction = false;
	bool controlSwitchTool = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	int numberOfGrass = 0;
	int grassSpawnTime = 0;
	int grassSpawnCadence = 5;
	void spawnGrass();

	int numberOfStone = 0;
	int stoneSpawnTime = 0;
	int stoneSpawnCadence = 5;
	void spawnStone();

	int numberOfTrees = 0;
	int treeSpawnTime = 0;
	int treeSpawnCadence = 5;
	void spawnTree();

	int actionTime = 0;
	int actionCadence = 20;

	list<Actor*> actorList;
	list<Recipe*> recipesList;

	GridMap* gridMap;
	Actor* tileGuide;
	bool isGuide = false;

	Actor* mission;
};


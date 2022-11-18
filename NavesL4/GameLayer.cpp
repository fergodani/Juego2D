#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	gamePad = SDL_GameControllerOpen(0);
	init();
}


void GameLayer::init() {
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);

	buttonJump = new Actor("res/boton_salto.png", WIDTH * 0.9, HEIGHT * 0.55, 100, 100, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);

	space = new Space(0);
	scrollX = 0;
	scrollY = 0;
	tiles.clear();

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	//audioBackground->play();
	

	backgroundWateringCan = new Actor("res/water_can.png",
		WIDTH * 0.05, HEIGHT * 0.05, 16, 16, game);
	backgroundAxe = new Actor("res/axe.png",
		WIDTH * 0.05, HEIGHT * 0.05, 16, 16, game);
	backgroundHoe = new Actor("res/hoe.png",
		WIDTH * 0.05, HEIGHT * 0.05, 16, 16, game);
	backgroundWood = new Actor("res/wood.png",
		WIDTH * 0.05, HEIGHT * 0.10, 16, 16, game);
	backgroundRock = new Actor("res/stoneIcon.png",
		WIDTH * 0.05, HEIGHT * 0.20, 16, 16, game);
	woodCuantity = 0;
	rockCuantity = 0;
	textWood = new Text("hola", WIDTH * 0.10, HEIGHT * 0.10, game);
	textWood->content = to_string(woodCuantity);
	textRock = new Text("hola", WIDTH * 0.10, HEIGHT * 0.20, game);
	textRock->content = to_string(rockCuantity);

	loadMap("res/agua.txt");
	loadMap("res/terreno.txt");
	loadMap("res/hills.txt");
	loadMap("res/detalles.txt");
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		int lines = 0;
		for (int i = 0; getline(streamFile, line); i++) {
			lines++;
			istringstream streamLine(line);
			mapWidth = line.length() * 16; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 16 / 2 + j * 16; // x central
				float y = 16 + i * 16; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
		mapHeight = lines * 16;
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'P': {
		loadMapObject('1', x, y);
		player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case 'a': {
		Tile* tile = new Tile("res/agua.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		//space->addStaticActor(tile);
		break;
	}
	case 'q': {
		Tile* tile = new Tile("res/detalle1.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		//space->addStaticActor(tile);
		break;
	}
	case 'w': {
		Tile* tile = new Tile("res/detalle2.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		//space->addStaticActor(tile);
		break;
	}
	case 's': {
		Grass* grass = new Grass(x, y, game);
		// modificación para empezar a contar desde el suelo.
		grass->y = grass->y - grass->height / 2;
		grassList.push_back(grass);
		//space->addStaticActor(tile);
		cout << "added grass" << endl;
		break;
	}
	case 'g': {
		int rX = (rand() + 100);
		string fileName = "res/stone1.png";
		if (rX % 2 == 0) {
			fileName = "res/stone2.png";
		}
		Stone* stone = new Stone(fileName, x, y, game);
		// modificación para empezar a contar desde el suelo.
		stone->y = stone->y - stone->height / 2;
		stoneList.push_back(stone);
		space->addStaticActor(stone);
		cout << "added grass" << endl;
		break;
	}
	case 'b': {
		Tile* tile = new Tile("res/b.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'c': {
		Tile* tile = new Tile("res/c.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'n': {
		Tile* tile = new Tile("res/n.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'v': {
		Tile* tile = new Tile("res/v.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'x': {
		Tile* tile = new Tile("res/x.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		//space->addStaticActor(tile);
		break;
	}
	case 'z': {
		Tile* tile = new Tile("res/z.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '1': {
		Tile* tile = new Tile("res/hierba1.png", x, y, 32, 32, true, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case '2': {
		Tile* tile = new Tile("res/hierba2.png", x, y, 32, 32, false,  game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case '3': {
		Tile* tile = new Tile("res/hierba3.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case '4': {
		Tile* tile = new Tile("res/hierba4.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case '5': {
		Tile* tile = new Tile("res/hierba5.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case '6': {
		Tile* tile = new Tile("res/hierba6.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case '7': {
		Tile* tile = new Tile("res/hierba7.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case '8': {
		Tile* tile = new Tile("res/hierba8.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case '9': {
		Tile* tile = new Tile("res/hierba9.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case 'r': {
		Tile* tile = new Tile("res/rampa1.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case 't': {
		Tile* tile = new Tile("res/rampa2.png", x, y, 32, 32, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	}
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}

		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
		// Procesar Mando
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}


	}
	//procesar controles
	// Disparar
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}

	if (controlChop == true) {
		player->chop();
	}

	if (controlPlow == true) {
		player->plow();
	}

	if (controlWater == true) {
		player->water();
	}
	if (controlAction == true) {
		player->action();
	}
	if (controlSwitchTool == true) {
		player->nextTool();
	}

}

void GameLayer::update() {
	if (pause) {
		return;
	}

	space->update();
	player->update();

	spawnGrass();
	spawnStone();

	if (grassSpawnTime > 0) {
		grassSpawnTime--;
	}
	if (stoneSpawnTime > 0) {
		stoneSpawnTime--;
	}
}

void GameLayer::spawnGrass() {
	if (grassSpawnTime == 0 && grassList.size() < 8) {
		grassSpawnTime = grassSpawnCadence;
		srand(time(0));
		int rX = (rand() % (player->x + player->x/2) + player->x/2);
		int rY = (rand() % (player->y + player->y / 2) + player->y / 2);
		Grass* grass = new Grass(rX, rY, game);
		for (auto const& tile : tiles) {
			if (tile->isOverlap(grass) && tile->canSpawn) {
				grassList.push_back(grass);
				return;
			}
		}
		

	}
}

void GameLayer::spawnStone() {
	if (stoneSpawnTime == 0 && stoneList.size() < 8) {
		cout << "Stone spawned" << endl;
		stoneSpawnTime = stoneSpawnCadence;
		srand(time(0));
		int rX = (rand() % (player->x + player->x / 2) + player->x / 2);
		int rY = (rand() % (player->y + player->y / 2) + player->y / 2);
		string fileName = "res/stone1.png";
		if (rX % 2 == 0) {
			fileName = "res/stone2.png";
		}
		Stone* stone = new Stone(fileName, rX, rY, game);
		for (auto const& tile : tiles) {
			if (tile->isOverlap(stone) && tile->canSpawn) {
				stoneList.push_back(stone);
				return;
			}
		}


	}
}

void GameLayer::calculateScroll() {
	scrollX = player->x - WIDTH/2;
	scrollY = player->y - HEIGHT/2;
}


void GameLayer::draw() {
	calculateScroll();

	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}
	
	for (auto const& grass : grassList) {
		grass->draw(scrollX, scrollY);
	}
	for (auto const& stone : stoneList) {
		stone->draw(scrollX, scrollY);
	}
	player->draw(scrollX, scrollY);
	// HUD
	if (player->actualTool == player->axe)
		backgroundAxe->draw();
	if (player->actualTool == player->hoe)
		backgroundHoe->draw();
	if (player->actualTool == player->watering_can)
		backgroundWateringCan->draw();
	backgroundWood->draw();
	backgroundRock->draw();
	player->inventory->drawItems();
	textWood->draw();
	textRock->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA << "," << buttonB << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	cout << "stickX" << stickX << endl;

	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 4000) {
		controlMoveX = 1;
	}
	else if (stickX < -4000) {
		controlMoveX = -1;
	}
	else {
		controlMoveX = 0;
	}

	if (buttonA) {
		//controlShoot = true;
	}
	else {
		//controlShoot = false;
	}

	if (buttonB) {
		controlMoveY = -1; // Saltar
	}
	else {
		controlMoveY = 0;
	}
}


void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = true;
			// CLICK TAMBIEN TE MUEVE
			controlMoveX = pad->getOrientationX(motionX);
		}
		if (buttonShoot->containsPoint(motionX, motionY)) {
			//controlShoot = true;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			controlMoveY = -1;
		}

	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		if (pad->clicked && pad->containsPoint(motionX, motionY)) {
			controlMoveX = pad->getOrientationX(motionX);
			// Rango de -20 a 20 es igual que 0
			if (controlMoveX > -20 && controlMoveX < 20) {
				controlMoveX = 0;
			}

		}
		else {
			pad->clicked = false; // han sacado el ratón del pad
			controlMoveX = 0;
		}
		if (buttonShoot->containsPoint(motionX, motionY) == false) {
			//controlShoot = false;
		}
		if (buttonJump->containsPoint(motionX, motionY) == false) {
			controlMoveY = 0;
		}

	}
	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = false;
			// LEVANTAR EL CLICK TAMBIEN TE PARA
			controlMoveX = 0;
		}

		if (buttonShoot->containsPoint(motionX, motionY)) {
			//controlShoot = false;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			controlMoveY = 0;
		}

	}
}


void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_0:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlAction = true;
			break;
		case SDLK_e:
			controlPlow = true;
			break;
		case SDLK_q:
			controlWater = true;
			break;
		case SDLK_TAB:
			//controlSwitchTool = false;
			break;
		}
		


	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // accion
			controlAction = false;
			break;
		case SDLK_e:
			controlPlow = false;
			break;
		case SDLK_q:
			controlWater = false;
			break;
		case SDLK_TAB:
			player->nextTool();
			break;
		}

	}
	// ZOOM
	if (event.type == SDL_MOUSEWHEEL) {
		if (event.button.x == 1) {
			//if (engine->scale < engine->maxScale) engine->scale += 0.25f;
			game->zoomIn();
		}
		else if (event.button.x == -1) {
			//if (engine->scale > engine->minScale) engine->scale -= 0.25f;
			game->zoomOut();
		}
	}

}


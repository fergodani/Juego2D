#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	gamePad = SDL_GameControllerOpen(0);
	gridMap = new GridMap(game);
	init();
}


void GameLayer::init() {
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);

	buttonJump = new Actor("res/boton_salto.png", WIDTH * 0.9, HEIGHT * 0.55, 100, 100, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);

	space = new Space(0);
	scrollX = 0;
	scrollY = 0;
	gridMap->tiles.clear();

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	//audioBackground->play();
	
	backgroundWood = new Actor("res/wood.png",
		WIDTH * 0.05, HEIGHT * 0.10, 16, 16, game);
	backgroundRock = new Actor("res/stoneIcon.png",
		WIDTH * 0.05, HEIGHT * 0.20, 16, 16, game);
	backgroundCoin = new Actor("res/coin.png",
		WIDTH * 0.05, HEIGHT * 0.30, 16, 16, game);
	textWood = new Text("hola", WIDTH * 0.10, HEIGHT * 0.10, 14, 33, game);
	
	textRock = new Text("hola", WIDTH * 0.10, HEIGHT * 0.20, 14, 33, game);
	
	textCoin = new Text("hola", WIDTH * 0.10, HEIGHT * 0.30, 14, 33, game);
	


	//loadMap("res/agua.txt");
	loadMap("res/terreno.txt");
	//loadMap("res/hills.txt");
	gridMap->rows = mapHeight / 16;
	gridMap->columns = mapWidth / 16;
	loadMap("res/detalles.txt");
	textCoin->content = to_string(player->inventory->money);
	textRock->content = to_string(player->inventory->stone);
	textWood->content = to_string(player->inventory->wood);
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
		Tile* tile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		//space->addStaticActor(tile);
		break;
	}
	case 'q': {
		Tile* tile = new Tile("res/detalle1.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->detailTiles.push_back(tile);
		//space->addStaticActor(tile);
		break;
	}
	case 'w': {
		Tile* tile = new Tile("res/detalle2.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->detailTiles.push_back(tile);
		//space->addStaticActor(tile);
		break;
	}
	case 's': {
		Grass* grass = new Grass(x, y, game);
		// modificación para empezar a contar desde el suelo.
		grass->y = grass->y - grass->height / 2;

		GroundTile* tileSelected = dynamic_cast<GroundTile*>(gridMap->getCollisionTile(grass->x, grass->y, player->orientation));
		if (tileSelected == NULL)
			break;
		grass->x = tileSelected->x;
		grass->y = tileSelected->y;
		tileSelected->placeGrass(grass);
		numberOfGrass++;

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

		GroundTile* tileSelected = dynamic_cast<GroundTile*>(gridMap->getCollisionTile(stone->x, stone->y, player->orientation));
		if (tileSelected == NULL)
			break;
		stone->x = tileSelected->x;
		stone->y = tileSelected->y;
		tileSelected->placeStone(stone);
		numberOfStone++;
		//stoneList.push_back(stone);
		//space->addStaticActor(stone);
		cout << "added grass" << endl;
		break;
	}
	case 'b': {
		Tile* tile = new Tile("res/b.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->detailTiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'c': {
		Tile* tile = new Tile("res/c.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->detailTiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'n': {
		Tile* tile = new Tile("res/n.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->detailTiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'v': {
		Tile* tile = new Tile("res/v.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->detailTiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'x': {
		Tile* tile = new Tile("res/x.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->detailTiles.push_back(tile);
		//space->addStaticActor(tile);
		break;
	}
	case 'z': {
		Tile* tile = new Tile("res/z.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->detailTiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '1': {
		GroundTile* tile = new GroundTile(x, y, 16, 16, true, game);
		Tile* waterTile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		waterTile->y = waterTile->y - waterTile->height / 2;
		gridMap->waterTiles.push_back(waterTile);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		
		gridMap->tiles.push_back(tile);
		break;
	}
	case '2': {
		Tile* tile = new Tile("res/hierba2.png", x, y, 16, 16, false,  game);
		Tile* waterTile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		waterTile->y = waterTile->y - waterTile->height / 2;
		gridMap->waterTiles.push_back(waterTile);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case '3': {
		Tile* tile = new Tile("res/hierba3.png", x, y, 16, 16, false, game);
		Tile* waterTile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		waterTile->y = waterTile->y - waterTile->height / 2;
		gridMap->waterTiles.push_back(waterTile);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case '4': {
		Tile* tile = new Tile("res/hierba4.png", x, y, 16, 16, false, game);
		Tile* waterTile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		waterTile->y = waterTile->y - waterTile->height / 2;
		gridMap->waterTiles.push_back(waterTile);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case '5': {
		Tile* tile = new Tile("res/hierba5.png", x, y, 16, 16, false, game);
		Tile* waterTile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		waterTile->y = waterTile->y - waterTile->height / 2;
		gridMap->waterTiles.push_back(waterTile);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case '6': {
		Tile* tile = new Tile("res/hierba6.png", x, y, 16, 16, false, game);
		Tile* waterTile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		waterTile->y = waterTile->y - waterTile->height / 2;
		gridMap->waterTiles.push_back(waterTile);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case '7': {
		Tile* tile = new Tile("res/hierba7.png", x, y, 16, 16, false, game);
		Tile* waterTile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		waterTile->y = waterTile->y - waterTile->height / 2;
		gridMap->waterTiles.push_back(waterTile);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case '8': {
		Tile* tile = new Tile("res/hierba8.png", x, y, 16, 16, false, game);
		Tile* waterTile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		waterTile->y = waterTile->y - waterTile->height / 2;
		gridMap->waterTiles.push_back(waterTile);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case '9': {
		Tile* tile = new Tile("res/hierba9.png", x, y, 16, 16, false, game);
		Tile* waterTile = new Tile("res/agua.png", x, y, 16, 16, false, game);
		waterTile->y = waterTile->y - waterTile->height / 2;
		gridMap->waterTiles.push_back(waterTile);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case 'r': {
		Tile* tile = new Tile("res/rampa1.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case 't': {
		Tile* tile = new Tile("res/rampa2.png", x, y, 16, 16, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		gridMap->tiles.push_back(tile);
		break;
	}
	case '&': {
		Actor* actor = new Actor("res/work_station.png", x, y, 32, 32, game);
		// modificación para empezar a contar desde el suelo.
		actor->y = actor->y - actor->height / 2;
		actorList.push_back(actor);
		space->addStaticActor(actor);
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

	if (controlPlow == true) {
		player->plow();
	}

	if (controlWater == true) {
		player->water();
	}

	if (controlSwitchTool == true) {
		player->inventory->nextItem();
		controlSwitchTool = false;
	}

	if (controlAction == true) {
		player->inventory->action();
		controlAction = false;
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

	gridMap->update();

	

	if (grassSpawnTime > 0) {
		grassSpawnTime--;
	}
	if (stoneSpawnTime > 0) {
		stoneSpawnTime--;
	}
}

void GameLayer::spawnGrass() {
	if (grassSpawnTime == 0 && numberOfGrass< 8) {
		grassSpawnTime = grassSpawnCadence;
		srand(time(0));
		int rX = (rand() % (player->x + player->x/2) + player->x/2);
		int rY = (rand() % (player->y + player->y / 2) + player->y / 2);
		GroundTile* tileSelected = dynamic_cast<GroundTile*>(gridMap->getCollisionTile(rX, rY, player->orientation));
		if (tileSelected == NULL)
			return;
		Grass* grass = new Grass(tileSelected->x, tileSelected->y, game);
		tileSelected->placeGrass(grass);
		numberOfGrass++;
		cout << "Grass Spawned at x: " << tileSelected->x << " y: " << tileSelected->y << endl;
	}
}

void GameLayer::spawnStone() {
	if (stoneSpawnTime == 0 && numberOfStone < 8) {
		srand(time(0));
		int rX = (rand() % (player->x + player->x / 2) + player->x / 2);
		int rY = (rand() % (player->y + player->y / 2) + player->y / 2);
		GroundTile* tileSelected = dynamic_cast<GroundTile*>(gridMap->getCollisionTile(rX, rY, player->orientation));
		if (tileSelected == NULL)
			return;
		stoneSpawnTime = stoneSpawnCadence;
		
		string fileName = "res/stone1.png";
		if (rX % 2 == 0) {
			fileName = "res/stone2.png";
		}
		Stone* stone = new Stone(fileName, tileSelected->x, tileSelected->y, game);
		tileSelected->placeStone(stone);
		numberOfStone++;
		cout << "Stone Spawned at x: " << tileSelected->x << " y: " << tileSelected->y << endl;

	}
}

void GameLayer::calculateScroll() {
	scrollX = player->x - WIDTH/2;
	scrollY = player->y - HEIGHT/2;
}


void GameLayer::draw() {
	calculateScroll();
	for (auto const& tile : gridMap->waterTiles) {
		tile->draw(scrollX, scrollY);
	}

	for (auto const& tile : gridMap->tiles) {
		tile->draw(scrollX, scrollY);
	}

	for (auto const& tile : gridMap->detailTiles) {
		tile->draw(scrollX, scrollY);
	}

	for (auto const& actor : actorList) {
		actor->draw(scrollX, scrollY);
	}
	
	player->draw(scrollX, scrollY);
	// HUD

	backgroundWood->draw();
	backgroundRock->draw();
	backgroundCoin->draw();
	player->inventory->drawItems();
	textWood->draw();
	textRock->draw();
	textCoin->draw();

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
			controlSwitchTool = true;
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
			controlSwitchTool = false;
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


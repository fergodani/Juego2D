#include "MenuLayer.h"

MenuLayer::MenuLayer(Game* game)
	: Layer(game) {
	init();
	gamePad = SDL_GameControllerOpen(0);
}

void MenuLayer::init() {
	// Fondo normal, sin velocidad
	background = new Background("res/menu_fondo.jpg", WIDTH * 0.5, HEIGHT * 0.5, game);
	button = new Actor("res/start.png", WIDTH * 0.5, HEIGHT * 0.8, 180, 32, game);
}

void MenuLayer::draw() {
	background->draw();
	button->draw();

	SDL_RenderPresent(game->renderer); // Renderiza NO PUEDE FALTAR
}


void MenuLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
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
	}

	//procesar controles, solo tiene uno
	if (controlContinue) {
		// Cambia la capa
		game->layer = game->gameLayer;
		controlContinue = false;
	}
}

void MenuLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE: // derecha
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_SPACE: // dispara
			controlContinue = true;
			break;
		}
	}
}

void MenuLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (button->containsPoint(motionX, motionY)) {
			button->texture = game->getTexture("res/start2.png");
			button->draw();
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (button->containsPoint(motionX, motionY)) {
			controlContinue = true;
		}

	}
}




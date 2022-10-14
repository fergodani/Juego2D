#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 45, 45, game) {

	orientation = game->orientationRight;
	state = game->stateMoving;

	aRunningRight = new Animation("res/playerrun3.png", width, height,
		384, 48, 4, 8, true, game);
	aRunningLeft = new Animation("res/playerrun4.png", width, height,
		384, 48, 4, 8, true, game);
	aRunningDown = new Animation("res/playerrun1.png", width, height,
		384, 48, 4, 8, true, game);
	aRunningUp = new Animation("res/playerrun2.png", width, height,
		384, 48, 4, 8, true, game);
	aIdleRight = new Animation("res/playeridle4.png", width, height,
		384, 48, 3, 8, true, game);
	aIdleLeft = new Animation("res/playeridle3.png", width, height,
		384, 48, 3, 8, true, game);
	aIdleDown = new Animation("res/playeridle1.png", width, height,
		384, 48, 3, 8, true, game);
	aIdleUp = new Animation("res/playeridle2.png", width, height,
		384, 48, 3, 8, true, game);
	animation = aRunningRight;

}


void Player::update() {

	bool endAnimation = animation->update();


	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}


	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}
	if (vy < 0) {
		orientation = game->orientationUp;
	}
	if (vy > 0) {
		orientation = game->orientationDown;
	}


	// Selección de animación basada en estados

	if (state == game->stateMoving) {
		if (vx != 0 && vy == 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}
		if (vy != 0 && vx == 0) {
			if (orientation == game->orientationDown) {
				animation = aRunningDown;
			}
			if (orientation == game->orientationUp) {
				animation = aRunningUp;
			}
		}
		if (vx == 0 && vy == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
			if (orientation == game->orientationUp) {
				animation = aIdleUp;
			}
			if (orientation == game->orientationDown) {
				animation = aIdleDown;
			}
		}
	}
	cout << "Orientation: " << orientation << endl;
}

void Player::moveX(float axis) {
	vx = axis * 5;
}

void Player::moveY(float axis) {
	vy = axis * 5;
}

void Player::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);

}

#include "Player.h"
#include "GameLayer.h"
#include <list>

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 45, 45, game) {

	orientation = game->orientationRight;
	state = game->stateMoving;

	aRunningRight = new Animation("res/playerrun3.png", width, height,
		384, 48, 2, 8, true, game);
	aRunningLeft = new Animation("res/playerrun4.png", width, height,
		384, 48, 2, 8, true, game);
	aRunningDown = new Animation("res/playerrun1.png", width, height,
		384, 48, 2, 8, true, game);
	aRunningUp = new Animation("res/playerrun2.png", width, height,
		384, 48, 2, 8, true, game);
	aIdleRight = new Animation("res/playeridle4.png", width, height,
		384, 48, 2, 8, true, game);
	aIdleLeft = new Animation("res/playeridle3.png", width, height,
		384, 48, 2, 8, true, game);
	aIdleDown = new Animation("res/playeridle1.png", width, height,
		384, 48, 2, 8, true, game);
	aIdleUp = new Animation("res/playeridle2.png", width, height,
		384, 48, 2, 8, true, game);
	aChoppingDown = new Animation("res/chop1.png", width, height,
		384, 48, 2, 8, false, game);
	aChoppingUp = new Animation("res/chop2.png", width, height,
		384, 48, 2, 8, false, game);
	aChoppingLeft = new Animation("res/chop3.png", width, height,
		384, 48, 2, 8, false, game);
	aChoppingRight = new Animation("res/chop4.png", width, height,
		384, 48, 2, 8, false, game);
	aPlowingRight = new Animation("res/arar4.png", width, height,
		384, 48, 2, 8, false, game);
	aPlowingLeft = new Animation("res/arar3.png", width, height,
		384, 48, 2, 8, false, game);
	aPlowingDown = new Animation("res/arar1.png", width, height,
		384, 48, 2, 8, false, game);
	aPlowingUp = new Animation("res/arar2.png", width, height,
		384, 48, 2, 8, false, game);
	aWateringRight = new Animation("res/watering4.png", width, height,
		384, 48, 2, 8, false, game);
	aWateringLeft = new Animation("res/watering3.png", width, height,
		384, 48, 2, 8, false, game);
	aWateringDown = new Animation("res/watering1.png", width, height,
		384, 48, 2, 8, false, game);
	aWateringUp = new Animation("res/watering2.png", width, height,
		384, 48, 2, 8, false, game);
	animation = aRunningRight;

	inventory = new Inventory(game);
}


void Player::update() {

	bool endAnimation = animation->update();


	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		GameLayer* gameLayer = (GameLayer*)game->gameLayer;
		if (state == game->statePlowing) {
			Grass* deleteGrass{};
			for (auto const& grass : gameLayer->grassList) {
				if (this->isOverlap(grass)) {
					cout << "Overlap grass" << endl;
					deleteGrass = grass;
				}
			}
			if (deleteGrass != nullptr) {
				deleteGrass->~Grass();
			}

			Stone* deleteStone{};
			for (auto const& stone : gameLayer->stoneList) {
				if (this->isOverlap(stone)) {
					cout << "Overlap stone" << endl;
					deleteStone = stone;
				}
			}
			if (deleteStone != nullptr)
				deleteStone->~Stone();

			state = game->stateMoving;
		}
		if (state == game->statePlowing)
			state = game->stateMoving;
		if (state = game->stateWatering) {
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

	if (state == game->stateChopping) {
		if (orientation == game->orientationRight) {
			animation = aChoppingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aChoppingLeft;
		}
		if (orientation == game->orientationDown) {
			animation = aChoppingDown;
		}
		if (orientation == game->orientationUp) {
			animation = aChoppingUp;
		}
	}

	if (state == game->statePlowing) {
		if (orientation == game->orientationRight) {
			animation = aPlowingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aPlowingLeft;
		}
		if (orientation == game->orientationDown) {
			animation = aPlowingDown;
		}
		if (orientation == game->orientationUp) {
			animation = aPlowingUp;
		}
	}

	if (state == game->stateWatering) {
		if (orientation == game->orientationRight) {
			animation = aWateringRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aWateringLeft;
		}
		if (orientation == game->orientationDown) {
			animation = aWateringDown;
		}
		if (orientation == game->orientationUp) {
			animation = aWateringUp;
		}
	}

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

		if (chopTime > 0) {
			chopTime--;
		}
		if (plowTime > 0) {
			plowTime--;
		}

		if (waterTime > 0) {
			waterTime--;
		}
	}

}

void Player::moveX(float axis) {
	vx = axis * 3.5;
}

void Player::moveY(float axis) {
	vy = axis * 3.5;
}

void Player::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);

}

void Player::chop() {
	if (chopTime == 0) {
		state = game->stateChopping;
		chopTime = chopCadence;
		// "Rebobinar" animaciones
		aChoppingRight->currentFrame = 0; 
		aChoppingLeft->currentFrame = 0; 
		aChoppingDown->currentFrame = 0; 
		aChoppingUp->currentFrame = 0; 
		
	}
}

void Player::plow() {
	if (plowTime == 0) {
		state = game->statePlowing;
		plowTime = plowCadence;
		// "Rebobinar" animaciones
		aPlowingRight->currentFrame = 0;
		aPlowingLeft->currentFrame = 0;
		aPlowingDown->currentFrame = 0;
		aPlowingUp->currentFrame = 0;
	}
}

void Player::water() {
	if (waterTime == 0) {
		state = game->stateWatering;
		waterTime = waterCadence;
		// "Rebobinar" animaciones
		aWateringRight->currentFrame = 0;
		aWateringLeft->currentFrame = 0;
		aWateringDown->currentFrame = 0;
		aWateringUp->currentFrame = 0;
	}
}


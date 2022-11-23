#pragma once

#include "Actor.h"
#include "Audio.h"
#include "Animation.h" // incluir animacion 
#include "Inventory.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Inventory* inventory;
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	int orientation;
	int state;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aRunningDown;
	Animation* aRunningUp;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aIdleDown;
	Animation* aIdleUp;
	Animation* aChoppingRight;
	Animation* aChoppingLeft;
	Animation* aChoppingDown;
	Animation* aChoppingUp;
	Animation* aPlowingRight;
	Animation* aPlowingLeft;
	Animation* aPlowingDown;
	Animation* aPlowingUp;
	Animation* aWateringRight;
	Animation* aWateringLeft;
	Animation* aWateringDown;
	Animation* aWateringUp;
	Animation* animation; // Referencia a la animación mostrada

	// Talado
	void chop();
	int chopTime = 0;
	int chopCadence = 5;

	// Arado
	void plow();
	int plowTime = 0;
	int plowCadence = 5;

	// Regado
	void water();
	int waterTime = 0;
	int waterCadence = 5;

	void action();
	bool isDoingAction = false;
};


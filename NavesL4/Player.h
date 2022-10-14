#pragma once

#include "Actor.h"
#include "Audio.h"
#include "Animation.h" // incluir animacion 

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
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
	Animation* animation; // Referencia a la animación mostrada

	void chop();
	int chopTime = 0;
	int chopCadence = 20;
};


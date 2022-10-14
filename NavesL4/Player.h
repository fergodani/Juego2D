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
	Animation* aChop;
	Animation* animation; // Referencia a la animación mostrada
};


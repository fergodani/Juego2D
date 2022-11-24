#pragma once
#include "Actor.h"
#include "Animation.h" // incluir animacion 

class Tree : public Actor
{
public:
	Tree(float x, float y, Game* game);
	~Tree();
	Animation* aIdle;
	enum State {entire, chopped};
	State state = entire;
	void draw(float scrollX = 0, float scrollY = 0) override;
	bool nextState();
	void update();
};


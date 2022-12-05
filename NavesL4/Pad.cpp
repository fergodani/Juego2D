#include "Pad.h"

Pad::Pad(float x, float y, Game* game)
	: Actor("res/onscreenControlls/transparentDark07.png", x, y, 120, 120, game) {

}


float Pad::getOrientationX(float clickX) {
	return clickX - x;
}

float Pad::getOrientationY(float clickY) {
	return clickY - y;
}
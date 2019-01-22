#include "Bullets.h"
#include "PlayState.h"

Bullets::Bullets(SDL_Renderer* r, Texture* text, Vector2D p, GameState* g) : MovingObject(r, text) {
	pState = g;

	h = BULLET_DIMENSIONS.first;
	w = BULLET_DIMENSIONS.second;

	vel = initVel;

	pos = p;
	x = pos.getX();
	y = pos.getY();

	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;
}

void Bullets::update() {
	if (active) {
		Vector2D prevPos = pos;

		pos = prevPos + vel;
		x = pos.getX();
		y = pos.getY();

		destRect.x = x;
		destRect.y = y;

		destroy();
	}
}

void Bullets::destroy() {
	if (pos.getY() < 0 || static_cast<PlayState*>(pState)->collides_Bullet_Block(destRect)) {
		active = false;
	}
}

void Bullets::render() {
	if (active) texture->renderFrame(destRect, 4, 4);
}

Bullets::~Bullets() {
}

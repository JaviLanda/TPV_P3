#pragma once

#include "MovingObject.h"

class Ball : public MovingObject {
public:
	Ball() {};
	Ball(SDL_Renderer* r, Texture* text, GameState* g);
	virtual ~Ball();

	virtual void update();
	virtual void loadFromFile(ifstream& f);
	virtual void saveToFile(fstream& f);

	void respawn();

private:
	int initV = 2;
	bool resp = false;

	Vector2D initVel = Vector2D(initV, -initV);
};
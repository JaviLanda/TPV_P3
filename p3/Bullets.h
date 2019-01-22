#pragma once

#include "MovingObject.h"

class Bullets : public MovingObject {
public:
	Bullets() {}
	Bullets(SDL_Renderer* r, Texture* text, Vector2D p, GameState* g);
	virtual ~Bullets();

	virtual void update();
	virtual void render();
	//virtual void loadFromFile(ifstream& f);
	//virtual void saveToFile(fstream& f);

	void destroy();

private:
	int initV = 2;

	Vector2D initVel = Vector2D(0, -initV);
};


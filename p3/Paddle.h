#pragma once
#include "MovingObject.h"

enum PowerUps { None, Big, Small, VidaExtra, NextLv, Bullet };

class Paddle : public MovingObject {
public:
	Paddle(SDL_Renderer* r, Texture* text, GameState* g, Game* a);
	virtual ~Paddle();

	virtual void saveToFile(fstream& f);
	virtual void loadFromFile(ifstream& f);
	virtual void update();

	bool handleEvent(SDL_Event& event);

	bool collides(const SDL_Rect& r);
	bool collidesBall(const SDL_Rect& r, Vector2D& collVector); //Comprobacion de choque con la pelota
	bool collidesReward(const SDL_Rect& r);

	void powerUp(int type);
	void givePower(int p);
	void respawn();

protected:
	Game* app;

	bool moveL, moveR;
	bool activeBullets = false;
	int numBullets = 0;
	int maxBullets = 5;
	int power = 0;
};
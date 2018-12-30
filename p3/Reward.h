#pragma once
#include "MovingObject.h"

enum Reward_Type { Nada, BigPaddle, SmallPaddle, ExtraHp, LvUp};

class Reward : public MovingObject {
public:
	Reward() {};
	Reward(SDL_Renderer* r, Texture* text, int x, int y, GameState* g);
	virtual ~Reward();

	virtual void render();
	virtual void update();
	virtual void action();
	virtual void loadFromFile(ifstream& f);
	virtual void saveToFile(fstream& f);

	void setIt(list<ArkanoidObject*>::iterator i) { it = i; }
	list<ArkanoidObject*>::iterator getIt() { return it; }

protected:
	int cont = 0;
	int fRow, fCol;
	int type;

	Vector2D initVel = Vector2D(0, 1);

	list<ArkanoidObject*>::iterator it;
};
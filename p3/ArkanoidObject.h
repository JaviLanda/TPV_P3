#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Vector2D.h"

class ArkanoidObject : public GameObject {
public:
	ArkanoidObject() {};
	ArkanoidObject(SDL_Renderer* r, Texture* text);
	virtual ~ArkanoidObject();

	virtual void render();
	virtual void update() {};
	bool handleEvent(SDL_Event& e) { return true; }

	virtual void loadFromFile(ifstream& f);
	virtual void saveToFile(fstream& f);
	virtual SDL_Rect getRect() { return destRect; }
	bool getActive() { return active; }
	void setActive(bool a) { active = a; }

protected:
	Vector2D pos;

	float w, h;
	float x = 0;
	float y = 0;
	SDL_Rect destRect;

	Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool active;
private:
};
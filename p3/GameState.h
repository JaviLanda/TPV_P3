#pragma once

#include <iterator>
#include "Texture.h"
#include "SDL_ttf.h"
#include <list>
#include "GameObject.h"

using namespace std;

class Game;

class GameState {
public:
	GameState(Game* g);
	virtual ~GameState();

	virtual void update();
	virtual void render();
	virtual bool handleEvent(SDL_Event &e);

	virtual bool OnEnter() = 0;

protected:
	Game* app;
	list<GameObject*> objects;
};
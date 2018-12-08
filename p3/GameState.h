#pragma once

#include <vector>
#include "Texture.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <list>
#include "Game.h"
#include <fstream>
#include <string>
#include <iostream>
#include "GameObject.h"

using namespace std;

class GameState
{
public:
	GameState(Game* g);
	virtual void update();
	virtual void render();
	virtual void handleEvent(SDL_Event &e);
	Texture* text;
	SDL_Rect src, rect;
	~GameState();

protected:
	list<GameObject*> stage;
	Game* app;
	int x, y;	//Posicion para los botones
};


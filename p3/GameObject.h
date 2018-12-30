#pragma once
#include <list>
#include <fstream>
#include "Game.h"

class GameObject {
public:
	virtual void render() = 0;
	virtual void update() = 0;
	virtual bool handleEvent(SDL_Event & e) = 0;
	virtual ~GameObject() {}

	GameState* pState = nullptr;
	Game* pGame = nullptr;
};
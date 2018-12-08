#pragma once
#include "GameState.h"
class PlayState : public GameState
{
public:
	PlayState(Game* game);
	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);
	~PlayState();
};


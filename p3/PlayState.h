#pragma once
#include "GameState.h"

class PlayState : public GameState {
public:
	PlayState(Game* game);
	~PlayState();

	virtual void update() {};
	virtual void render() {};
	virtual void handleEvents(SDL_Event& e) {};

	virtual bool OnEnter();
	virtual bool OnExit();
};
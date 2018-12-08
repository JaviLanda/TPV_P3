#include "GameState.h"



GameState::GameState(Game* game) : app(game)
{
}


void GameState::update() {

	for (GameObject* c : stage) {
		c->update();
	}
}

void GameState::render() {
	for (GameObject* c : stage) {
		c->render();
	}
}

void GameState::handleEvent(SDL_Event &e) {
	bool handled = false;
	auto it = stage.begin();
	while (!handled && it != stage.end()) {
		if ((*it)->handleEvents())
			handled = true;
		else
			++it;
	}
}

GameState::~GameState()
{
	for (GameObject* o : stage) delete o;
}
}


#include "GameState.h"

GameState::GameState(Game *game) : app(game) {}

void GameState::update() {
	for (GameObject* c : objects) c->update();
}

void GameState::render() {
	for (GameObject* c : objects) c->render();
}

void GameState::handleEvents(SDL_Event &e) {
	bool handled = false;
	auto it = objects.begin();
	
	while (!handled && it != objects.end()) {
		if ((*it)->handleEvent(e)) handled = true;
		else ++it;
	}
	//return handled;
}

GameState::~GameState() {
	for (GameObject* o : objects) {
		delete o;
		o = nullptr;
	}
}
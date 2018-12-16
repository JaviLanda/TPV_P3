#include "GameState.h"

GameState::GameState(Game* game) : app(game) {
}

void GameState::update() {
	for (GameObject* c : objects) c->update();
}

void GameState::render() {
	for (GameObject* c : objects) c->render();
}

bool GameState::handleEvent(SDL_Event &e) {
	bool handled = false;
	//list<GameObject*>::iterator it = objects.begin();
	
	/*while (!handled && it != objects.end()) {
		if ((*it)->handleEvents()) handled = true;
		else ++it;
	}*/

	//for (GameObject* c : objects) c->handleEvents();
	auto it = objects.begin();
	
	while (it != objects.end()) {
		(*it)->handleEvents();
	}
	//return handled;
	return true;
}

GameState::~GameState() {
	for (GameObject* o : objects) {
		delete o;
		o = nullptr;
	}
}
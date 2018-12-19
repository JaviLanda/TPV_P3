#include "PlayState.h"
#include "PauseState.h"

PlayState::PlayState(Game* g) : GameState(g) {
	app = g;
	rend = g->getRend();

	initObjects();
}

void PlayState::initObjects() {
	initMap();
}

void PlayState::initMap() {
	blockMap = new BlockMap(rend, app->getText(Game::TBrick));
	if (level < 3) blockMap->load(maps[level]);
	if (blockMap == nullptr) {
		//throw FileNotFoundError(SDL_GetError());
		cout << "Map cannot be loaded! \nSDL_Error: " << SDL_GetError() << '\n';
	}
	objects.push_front(blockMap);
	mapIt = objects.begin();
}

bool PlayState::OnEnter() {
	cout << "En el PlayState" << endl;
	return true;
}

bool PlayState::OnExit() {
	cout << "Saliendo del PlayState" << endl;
	return true;
}

bool PlayState::handleEvent(SDL_Event& e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_p:
			app->getStateMachine()->pushState(new PauseState(app));
			break;
		default:
			break;
		}
	}

	GameState::handleEvent(e);
	return true;
}
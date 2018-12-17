#include "PlayState.h"

PlayState::PlayState(Game* g) : GameState(g) {
	app = g;
}

PlayState::~PlayState() {}

bool PlayState::OnEnter() {
	cout << "En el PlayState" << endl;
	return true;
}

bool PlayState::OnExit() {
	cout << "Saliendo del PlayState" << endl;
	return true;
}
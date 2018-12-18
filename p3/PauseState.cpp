#include "PauseState.h"

PauseState::PauseState(Game* g) : GameState(g) {
	app = g;
	
	initBoton();
}

void PauseState::initBoton() {
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonContinue, 100, 150, Continue));
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonSave, 500, 150, Save));
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonMenu, 300, 400, Menu));
}

bool PauseState::OnEnter() {
	cout << "En el PauseState" << endl;
	return true;
}

bool PauseState::OnExit() {
	cout << "Saliendo del PauseState" << endl;
	return true;
}
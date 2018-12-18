#include "EndState.h"
#include "MainMenuState.h"

EndState::EndState(Game* g) : GameState(g) {
	app = g;

	initBoton();
}

bool EndState::OnEnter() {
	cout << "En el EndState" << endl;
	//app->getStateMachine()->changeState(new MainMenuState(app));
	return true;
}

bool EndState::OnExit() {
	cout << "Saliendo del EndState" << endl;
	return true;
}

void EndState::Menu(Game * g) {
	//g->getStateMachine()->changeState(new MainMenuState(g));
}

void EndState::initBoton() {
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonExit, 500, 450, Exit));
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonMenu, 100, 450, Menu));
}
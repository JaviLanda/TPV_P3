#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
//#include "EndState.h"

MainMenuState::MainMenuState(Game* g) : GameState(g) {
	app = g;

	initBoton();
}

MainMenuState::~MainMenuState() {}

bool MainMenuState::OnEnter() {
	cout << "En el MainMenu" << endl;
	//app->getStateMachine()->changeState(new PauseState(app));
	return true;
}

bool MainMenuState::OnExit() {
	cout << "Saliendo del MainMenu" << endl;
	return true;
}

void MainMenuState::initBoton() {
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonPlay, 100, 150, Play));
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonExit, 300, 400, Exit));
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonLoad, 500, 150, Load));
}

void MainMenuState::Play(Game* g) {	g->getStateMachine()->changeState(new PlayState(g)); }

void MainMenuState::Exit(Game* g) { g->endGame(true); }
#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* g) : GameState(g) {
	app = g;

	initBoton();
}

MainMenuState::~MainMenuState() {}

bool MainMenuState::OnEnter() {
	cout << "En el MainMenu" << endl;
	//app->getStateMachine()->changeState(new PlayState(app));
	return true;
}

bool MainMenuState::OnExit() {
	cout << "Saliendo del MainMenu" << endl;
	return true;
}

void MainMenuState::initBoton() {
	objects.emplace_back(new Button(app, Game::Textures_T::TPlay, 250, 50, Play));
	//stage.emplace_back(new Button(app, game->nTexturas[TLoad], x, y + 150, Load));
	//stage.emplace_back(new Button(app, game->nTexturas[TExit], x, y + 300, Exit));
}

void MainMenuState::Play(Game* g) {	g->getStateMachine()->changeState(new PlayState(g)); }
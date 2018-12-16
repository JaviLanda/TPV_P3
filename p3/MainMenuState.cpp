#include "MainMenuState.h"

MainMenuState::MainMenuState(Game* g) : GameState(g) {
	//initBoton();
}

MainMenuState::~MainMenuState() {}

bool MainMenuState::OnEnter() {
	cout << "En el stateMenu" << endl;
	return true;
}

void MainMenuState::initBoton() {
	//x = 250;
	//y = 50;
	//stage.emplace_back(new Button(app, game->nTexturas[TPlay], x, y, Play));		//Probablemente este game se refiera a app
	//stage.emplace_back(new Button(app, game->nTexturas[TLoad], x, y + 150, Load));	//Probablemente este game se refiera a app
	//stage.emplace_back(new Button(app, game->nTexturas[TExit], x, y + 300, Exit));	//Probablemente este game se refiera a app
}
#include "MainMenuState.h"



MainMenuState::MainMenuState(Game* game) : GameState(game)
{
	initBoton();
}

void MainMenuState::initBoton() {
	x = 250;
	y = 50;
	stage.emplace_back(new Button(app, game->nTexturas[TPlay], x, y, Play));		//Probablemente este game se refiera a app
	stage.emplace_back(new Button(app, game->nTexturas[TLoad], x, y + 150, Load));	//Probablemente este game se refiera a app
	stage.emplace_back(new Button(app, game->nTexturas[TExit], x, y + 300, Exit));	//Probablemente este game se refiera a app
}


MainMenuState::~MainMenuState()
{
	delete stage.back();
	delete stage.back();
	delete stage.back();
	stage.pop_back();
	stage.pop_back();
	stage.pop_back();
}

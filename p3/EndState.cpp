#include "EndState.h"



EndState::EndState(Game* game) : GameState(game)
{
	initBoton();
}

void EndState::initBoton() {
	x = 250;
	y = 50;
	stage.emplace_back(new Button(app, game->nTexturas[TMenu], x, y, Menu));		 //Probablemente este game se refiera a app
	stage.emplace_back(new Button(app, game->nTexturas[TExit], x, y + 200, Exit));	//Probablemente este game se refiera a app
}


EndState::~EndState()
{
	delete stage.back();
	delete stage.back();
	stage.pop_back();
	stage.pop_back();
}

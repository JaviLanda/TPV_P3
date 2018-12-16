#include "PauseState.h"



PauseState::PauseState(Game* game) : GameState(game)
{
	initBoton();
}

void PauseState::initBoton() {
	//stage.emplace_back(new Button(app, game->nTexturas[TResume], x, y, Resume));	//Probablemente este game se refiera a app
	//stage.emplace_back(new Button(app, game->nTexturas[TMenu], x, y + 150, Menu));	//Probablemente este game se refiera a app
	//stage.emplace_back(new Button(app, game->nTexturas[TSave], x, y + 300, Save));	//Probablemente este game se refiera a app
}

PauseState::~PauseState()
{
	delete objects.back();
	delete objects.back();
	delete objects.back();
	objects.pop_back();
	objects.pop_back();
	objects.pop_back();
}

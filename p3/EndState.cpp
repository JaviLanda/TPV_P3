#include "EndState.h"

EndState::EndState(Game* g) : GameState(g) {
	//objects.emplace_back(new Button(app, g->nTexturas[TMenu], 200, 400, Menu));		 //Probablemente este game se refiera a app
	//objects.emplace_back(new Button(app, g->nTexturas[TExit], 500, 400, Exit));	//Probablemente este game se refiera a app
}

EndState::~EndState() {}

bool EndState::OnEnter() {
	cout << "En el EndState" << endl;
	return true;
}

void EndState::Menu(Game * g) {
	//g->getStateMachine()->changeState(new MainMenuState(g));
}
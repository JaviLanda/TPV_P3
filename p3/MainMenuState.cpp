#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

MainMenuState::MainMenuState(Game* g) : GameState(g) {
	app = g;

	initBoton();
}

bool MainMenuState::OnEnter() {
	cout << "En el MainMenu" << endl;
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
void MainMenuState::Load(Game* g) {
	g->getStateMachine()->changeState(new PlayState(g));
	PlayState* ps = dynamic_cast<PlayState*>(g->getStateMachine()->currentState());
	ps->loadBool(true);

}
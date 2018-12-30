#include "EndState.h"
#include "MainMenuState.h"

EndState::EndState(Game* g) : GameState(g) {
	app = g;

	initBoton();
}

bool EndState::OnEnter() {
	cout << "En el EndState" << endl;
	return true;
}

bool EndState::OnExit() {
	cout << "Saliendo del EndState" << endl;
	return true;
}

void EndState::initBoton() {
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonExit, 500, 450, Exit));
	objects.emplace_back(new Button(app, Game::Textures_T::TButtonMenu, 100, 450, Menu));
}

void EndState::render() {

	GameState::render();

	stringstream strm;
	strm << "Score: " << app->getScore();
	app->tScore->loadFont(app->getRend(), app->font, strm.str().c_str(), app->red);
	app->tScore->render(app->scoreRect);

	app->scoreRect.x = (WIN_WIDTH / 2) - 140;
	app->scoreRect.y = (WIN_HEIGHT / 2) - 100;
	app->scoreRect.w = 250;
	app->scoreRect.h = 50;
}

void EndState::Menu(Game * g) {	g->getStateMachine()->changeState(new MainMenuState(g)); }
void EndState::Exit(Game * g) { g->endGame(true); }
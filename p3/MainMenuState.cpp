#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* g) : GameState(g) {
	//initBoton();
	app = g;
}

MainMenuState::~MainMenuState() {}

bool MainMenuState::OnEnter() {
	cout << "En el MainMenu" << endl;
	return true;
}

bool MainMenuState::OnExit() {
	cout << "Saliendo del MainMenu" << endl;
	return true;
}

void MainMenuState::initBoton() {
	//x = 250;
	//y = 50;
	//objects.emplace_back(new Button(app, app->getText(Game::Textures_T::TPlay), 250, 50, Play));		//Probablemente este game se refiera a app
	//stage.emplace_back(new Button(app, game->nTexturas[TLoad], x, y + 150, Load));	//Probablemente este game se refiera a app
	//stage.emplace_back(new Button(app, game->nTexturas[TExit], x, y + 300, Exit));	//Probablemente este game se refiera a app
}

bool MainMenuState::handleEvent(SDL_Event &e) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.type) {
		case SDLK_e:
			
			break;
		default:
			break;
		}
	}

	GameState::handleEvent(e);
	return true;
}
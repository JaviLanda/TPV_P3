#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState : public GameState {
public:
	MainMenuState(Game* g);
	~MainMenuState();
		
	void initBoton();

	virtual void update() {};
	//virtual void render();
	//virtual bool handleEvent(SDL_Event &e);

	virtual bool OnEnter();
	virtual bool OnExit();
private:
	static void Play(Game* g);
	void Exit(Game* g) { /*game->funcion de salir de juego    juego->onExit();*/ }
	void Load(Game* g) { /*
						 game->load = true;
						 game->stateMachine->changeState(new PlayState(game));
						 if (static_cast<PlayState*>(game->getStateMachine()->currentState())->filenotfound)
						 game->stateMachine->changeState(new MenuState(game));
						 */
	}
};
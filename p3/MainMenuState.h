#pragma once
#include "GameState.h"
#include "Button.h"
#include "GameStateMachine.h"



class MainMenuState : public GameState
{
public:
	MainMenuState(Game* g);
	static void Play(Game* game) { game->stateMachine->changeState(new PlayState(game)); }
	static void Exit(Game* game) { /*game->funcion de salir de juego    juego->onExit();*/ }
	static void Load(Game* game) {

		game->load = true;
		game->stateMachine->changeState(new PlayState(game));
		if (static_cast<PlayState*>(game->getStateMachine()->currentState())->filenotfound)
			game->stateMachine->changeState(new MenuState(game));
	}
	void initBoton();

	virtual void update() {};
	~MainMenuState();

protected:
	GameStateMachine* state;
};


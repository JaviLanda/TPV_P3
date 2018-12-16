#pragma once
#include "GameState.h"
#include "Button.h"

#include <iostream>

class MainMenuState : public GameState {
public:
	MainMenuState(Game* g);
	~MainMenuState();
		
	void initBoton();
	void Play(Game* g) { /*game->stateMachine->changeState(new PlayState(game));*/ }
	void Exit(Game* g) { /*game->funcion de salir de juego    juego->onExit();*/ }
	void Load(Game* g) { /*
		game->load = true;
		game->stateMachine->changeState(new PlayState(game));
		if (static_cast<PlayState*>(game->getStateMachine()->currentState())->filenotfound)
			game->stateMachine->changeState(new MenuState(game));
			*/	
	}

	virtual void update() {};
	virtual void render() {};
	virtual void handleEvents() {};

	virtual bool OnEnter();

protected:
	
};


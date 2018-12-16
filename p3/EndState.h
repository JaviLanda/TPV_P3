#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "Button.h"

class Game;
class EndState : public GameState {
public:
	EndState(Game* g);
	~EndState();

	virtual bool OnEnter();

private:
	void Menu(Game* g);
	void Exit(Game* g) { /*game->funcion de salir de juego    juego->onExit();*/ }
};
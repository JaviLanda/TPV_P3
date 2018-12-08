#pragma once
#include "GameState.h"
class EndState : public GameState
{
public:
	EndState(Game* game);
	static void Menu(Game* juego) { juego->stateMachine->changeState(new MainMenuState(juego)); }
	static void Exit(Game* juego) { /*game->funcion de salir de juego    juego->onExit();*/ }
	void initBoton();
	~EndState();
};


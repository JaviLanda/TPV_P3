#pragma once
#include "GameState.h"
class PauseState : public GameState
{
public:
	PauseState(Game* game);
	static void Menu(Game* juego) { /*juego->stateMachine->changeState(new MainMenuState(juego));*/ }
	static void Resume(Game* juego) { /*juego->stateMachine->popState();*/ }
	//static void Save(Game* juego) {}	//Digo yo que habrá un save game no¿?¿?¿?¿?¿?¿?
	void initBoton();
	~PauseState();
};


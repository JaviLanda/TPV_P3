#pragma once
#include "GameState.h"
#include "Button.h"

class PauseState : public GameState {
public:
	PauseState(Game* g);
	
	void initBoton();

	virtual bool OnEnter();
	virtual bool OnExit();

private:
	static void Menu(Game* juego) { /*juego->stateMachine->changeState(new MainMenuState(juego));*/ }
	static void Continue(Game* juego) { /*juego->getStateMachine()->popState();*/ }
	static void Save(Game* juego) {}
};
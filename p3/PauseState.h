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
	static void Menu(Game* g);
	static void Continue(Game* g);
	static void Save(Game* g);
};
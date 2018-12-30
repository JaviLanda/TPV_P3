#pragma once
#include <sstream>

#include "GameState.h"
#include "Button.h"

class EndState : public GameState {
public:
	EndState(Game* g);

	void initBoton();

	virtual void render();
	virtual bool OnEnter();
	virtual bool OnExit();

private:
	static void Menu(Game* g);
	static void Exit(Game* g);
};
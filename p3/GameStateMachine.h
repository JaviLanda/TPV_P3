#pragma once

#include <iostream>
#include <stack>
using namespace std;

class GameState;

class GameStateMachine {
public:
	GameStateMachine();
	virtual ~GameStateMachine();

	void pushState(GameState* newSt);
	void changeState(GameState* newState);
	void popState();

	GameState* currentState();
private:
	stack <GameState*> pila;
};
#include "GameStateMachine.h"


GameStateMachine::GameStateMachine()
{
}


void GameStateMachine::pushState(GameState* newSt) {
	pila.push(newSt);
}

void GameStateMachine::changeState(GameState* newState) {
	popState();
	pushState(newState);
}

GameState* GameStateMachine::currentState() {
	return pila.top();
}

void GameStateMachine::popState() {
	if (!pila.empty()) {
		delete pila.top();
		pila.pop();
	}
}


GameStateMachine::~GameStateMachine()
{
	while (!pila.empty()) {
		popState();
	}
}

#include "GameStateMachine.h"
#include "GameState.h"

GameStateMachine::GameStateMachine() {}

void GameStateMachine::pushState(GameState* newSt) {
	pila.push(newSt);
	pila.top()->OnEnter();
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
		pila.top()->OnExit();
		delete pila.top();
		pila.pop();
	}
}

GameStateMachine::~GameStateMachine() {
	while (!pila.empty()) {
		popState();
	}
}
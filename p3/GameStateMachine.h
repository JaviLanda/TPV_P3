#pragma once
#include "SDL.h"
#include <vector>
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <list>
#include <fstream>
//#include "GameObject.h"
//#include "Game.h"
#include "GameState.h"
#include <string>
#include <iostream>
#include <stack>
using namespace std;

class GameStateMachine
{
	friend class GameState;
public:
	GameStateMachine();
	void pushState(GameState* newSt);
	void changeState(GameState* newState);
	void popState();
	GameState* currentState();
	~GameStateMachine();

private:
	stack <GameState*> pila;
	
	
};


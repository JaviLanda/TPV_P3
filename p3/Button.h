#pragma once
#include "GameState.h"
#include "Texture.h"
#include "SDL.h"
#include "GameObject.h"

class Game;

class Button : public GameObject
{
public:
	typedef void CallBackOnClick(Game* game);
	Button(Game* juego, Texture* text, int x, int y, CallBackOnClick* cb);

	Texture* ptext;
	virtual void render();
	virtual bool handleEvent(SDL_Event& e);
	~Button();

protected:
	CallBackOnClick* callB;
	SDL_Rect rect;
	SDL_Rect src;
	Game* game;

};


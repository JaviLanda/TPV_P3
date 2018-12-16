#pragma once
#include "Texture.h"
#include "SDL.h"
#include "GameObject.h"

class Game;

class Button : public GameObject {
public:
	typedef void CallBackOnClick(Game* game);
	Button(Game* juego, Texture* text, int x, int y, CallBackOnClick* cb);
	~Button();

	Texture* ptext;
	void update() {}
	void render();
	bool handleEvent(SDL_Event& e);

protected:
	CallBackOnClick* callB;
	SDL_Rect rect;

	Game* pGame = nullptr;
};
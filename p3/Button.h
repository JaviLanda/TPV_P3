#pragma once
#include "Texture.h"
#include "GameObject.h"

class Button : public GameObject {
public:
	typedef void CallBackOnClick(Game* game);
	Button(Game* juego, Game::Textures_T text, int x, int y, CallBackOnClick* cb);
	~Button();

	Texture* ptext;
	void update() {}
	void render();
	virtual bool handleEvent(SDL_Event& e);

protected:
	CallBackOnClick* callB;
	SDL_Rect rect;
};
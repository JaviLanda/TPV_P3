#include "Button.h"


Button::Button(Game* juego, Texture* text, int x, int y, CallBackOnClick* cb) : GameObject()
{
	ptext = text;
	callB = cb;
	rect.w = 300;
	rect.h = 200;
	rect.x = x;
	rect.y = y;
	src.w = ptext->getW();
	src.h = ptext->getH();
	
}

void Button::render() {
	//ptext->drawFrame(game->getRender(), src, rect);
}

bool Button::handleEvent(SDL_Event& e) {
	if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p = { e.button.x, e.button.y };
		SDL_Rect r = { rect.x,rect.y, rect.w, rect.h };
		
		if (SDL_PointInRect(&p, &r))
			//callB(game);
			cout << "Pulsado";
			return true;
	}
}



Button::~Button()
{
}

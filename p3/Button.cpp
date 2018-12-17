#include "Button.h"

Button::Button(Game* juego, Game::Textures_T text, int x, int y, CallBackOnClick* cb) {

	pApp = juego;

	ptext = pApp->getText(text);

	callB = cb;

	rect.w = 300;
	rect.h = 200;
	rect.x = x;
	rect.y = y;

	//src.w = ptext->getW();
	//src.h = ptext->getH();
}

void Button::render() {
	ptext->render(rect);
	//ptext->drawFrame(game->getRender(), src, rect);
}

bool Button::handleEvent(SDL_Event& e) {
	bool handle = false;

	if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p = { e.button.x, e.button.y };
		SDL_Rect r = { rect.x,rect.y, rect.w, rect.h };
		
		if (SDL_PointInRect(&p, &r)) {
			callB(pApp);
			cout << "Pulsado";
			handle = true;
		}
	}
	return handle;
}

Button::~Button() {}
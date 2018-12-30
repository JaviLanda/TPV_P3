#include "Paddle.h"
#include "PlayState.h"

Paddle::Paddle(SDL_Renderer* r, Texture* text, GameState* g) : MovingObject(r, text) {
	pState = g;

	x = WIN_WIDTH / 2 - texture->getW() / 2;
	y = WIN_HEIGHT - 100;
	h = texture->getH();
	w = texture->getW();

	destRect.h = h;
	destRect.w = w;
	destRect.x = x;
	destRect.y = y;

	moveL = false;
	moveR = false;
}

Paddle::~Paddle() {}

void Paddle::update() { //Revisar laterales
	destRect.x += vel.getX();
	x = destRect.x;
	if (x < WALL_WIDTH + 5 || (x + destRect.w) > WIN_WIDTH - WALL_WIDTH - 10) vel.setX(0);
}

//------------------------------------COLLISIONS-----------------------------------
bool Paddle::collides(const SDL_Rect& r) {
	bool hit = false;
	if (r.x >= destRect.x && r.x <= destRect.x + destRect.w) {
		if (r.y > destRect.y - destRect.h && r.y < destRect.y) {
			hit = true;
		}
	}
	return hit;
}

bool Paddle::collidesReward(const SDL_Rect& r) {
	bool hit = collides(r);
	return hit;
}

bool Paddle::collidesBall(const SDL_Rect& r, Vector2D& collVector) {
	bool hit = collides(r);
	if (hit) {
		float size = destRect.w / 3;
		collVector = { 0, 1 };
		/*float precision = r.x - destRect.x;
		if (precision <= destRect.w) {
			if (precision > 2 * size) { //Lado der
				collVector = { 1, 1 };
			} else if (precision > size) { //Medio
				collVector = { 0, 1 };
			} else { //Lado izq
				collVector = { -1, 1 };
			}
		}*/
	}
	return hit;
}

//-----------------------------------POWER UPS--------------------------
void Paddle::powerUp(int type) {
	givePower(type);
	switch (type) {
	case VidaExtra: //Vida extra
		static_cast<PlayState*>(pState)->addLife();
		break;
	case NextLv: //Pasar nivel
		static_cast<PlayState*>(pState)->setLevel(true);
		break;
	default:
		break;
	}
}

void Paddle::givePower(int p) {
	switch (p) {
	case None:	//None
		break;
	case Big:	//Alargar
		destRect.w = w;
		destRect.w *= 1.5;
		break;
	case Small:	//Acortar
		destRect.w = w;
		destRect.w *= 0.75;
		break;
	default:
		break;
	}
}

//------------------------------RESPAWN--------------------
void Paddle::respawn() {
	x = WIN_WIDTH / 2 - texture->getW() / 2;
	y = WIN_HEIGHT - 100;
	h = texture->getH();
	w = texture->getW();
	destRect.x = x;
	destRect.y = y;
	destRect.h = h;
	destRect.w = w;
}

//---------------------HANDLE_EVENTS--------------------
bool Paddle::handleEvent(SDL_Event& event) {
	bool b = false;
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (x > WALL_WIDTH) {
				b = true;
				vel.setX(-3);
			}
			break;
		case SDLK_RIGHT:
			if (x < WIN_WIDTH - WALL_WIDTH - destRect.w) {
				b = true;
				vel.setX(3);
			}
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		case (SDLK_RIGHT || SDLK_LEFT):
			vel.setX(0);
			b = true;
			break;
	}
	return b;
}

//-------------------------GUARDAR_Y_CARGAR-------------------------------
void Paddle::saveToFile(fstream& f) {
	f << power << " ";
	ArkanoidObject::saveToFile(f);
}

void Paddle::loadFromFile(ifstream& f) {
	int p = 0;
	f >> p;
	power = p;
	givePower(p);
	ArkanoidObject::loadFromFile(f);
}
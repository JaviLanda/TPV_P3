#pragma once
//#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "GameObject.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "SDLError.h"
#include <list>
#include <SDL_ttf.h>	//Para textos

const uint NUM_TEXTURES = 6;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;

const string IMAGES_PATH = "../images/";

struct TextureAtributtes {
	string nombre;
	int row;
	int col;
};

const TextureAtributtes TEXT_ATT[NUM_TEXTURES] = {
	{ "bricks.png", 2, 3 },{ "paddle.png", 1, 1 },
	{ "ball.png", 1, 1 },{ "side.png", 1, 1 },
	{ "topside.png", 1, 1 },{ "rewards.png", 10, 8 }
};

class Game {
public:
	Game();
	~Game();

	enum Textures_T { TBrick, TPaddle, TBall, TSide, TTopSide, TReward };
	Texture* getText(Textures_T et) const { return nTexturas[et]; }

	SDL_Renderer* getRend() { return renderer; }
	SDL_Window* getWin() { return window; }
	GameStateMachine* getStateMachine() { return stateMachine; }

	void run();

protected:
	SDL_Renderer *renderer = nullptr;
	SDL_Window *window = nullptr;
	GameStateMachine *stateMachine = nullptr;

	bool initSDL();
	void closeSDL();

	void initTextures();
	void destroyTextures();

	void update();
	void render();
	void handleEvents();

	Texture* nTexturas[NUM_TEXTURES];
private:
	bool end = false;
};
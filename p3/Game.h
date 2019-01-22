#pragma once
//#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "SDLError.h"

#include <list>
#include <SDL_ttf.h>	//Para textos

#include "GameStateMachine.h"

const uint NUM_TEXTURES = 13;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const string FONT = "";

const string IMAGES_PATH = "../images/";

struct TextureAtributtes {
	string nombre;
	int row;
	int col;
};

const TextureAtributtes TEXT_ATT[NUM_TEXTURES] = {
	{ "bricks.png", 2, 3 },{ "paddle.png", 1, 1 },
	{ "ball.png", 1, 1 },{ "side.png", 1, 1 },
	{ "topside.png", 1, 1 },{ "rewards.png", 10, 8 },
	{ "Button_Start.png", 1, 1}, {"Button_Exit.png", 1, 1},
	{ "Button_Load.png", 1, 1}, {"Button_MainMenu.png", 1, 1},
	{ "Button_Continue.png", 1, 1}, { "Button_Save.png", 1, 1},
	{ "paddleGun.png", 1, 1}
};

class Game {
public:
	Game();
	~Game();

	enum Textures_T {	TBrick, TPaddle, TBall, TSide, TTopSide, TReward, 
						TButtonPlay, TButtonExit, TButtonLoad, TButtonMenu,
						TButtonContinue, TButtonSave, TPaddleGun};

	Texture* getText(Textures_T et) const { return nTexturas[et]; }
	SDL_Renderer* getRend() { return renderer; }
	SDL_Window* getWin() { return window; }
	GameStateMachine* getStateMachine() { return stateMachine; }
	int getScore() { return puntuacion; }
	void addScore() { puntuacion++; }
	void setScore(int p) { puntuacion = p; }

	void endGame(bool b) { end = b; }
	void run();

	//Atributos textura/fuente de la vida y el score
	Texture* tScore;
	SDL_Color red = { 255, 0, 0 }; //The color of the font
	TTF_Font* font;
	SDL_Rect scoreRect;

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
	int puntuacion = 0;
};
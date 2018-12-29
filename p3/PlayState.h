#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include "GameState.h"

#include "BlockMap.h"
#include "Ball.h"
#include "Paddle.h"
#include "Wall.h"
#include "RewardX1.h"
#include "RewardX2.h"
#include "RewardX3.h"
#include "RewardX4.h"

const uint NUM_MAPS = 3;
const uint WALL_WIDTH = 40;
const uint BALL_SIZE = 25;
const uint PADDLE_MOVE = 5;
const uint REWARD_W = 30;
const uint REWARD_H = 20;
const uint REWARD_CHANCE = 5;

const string SAVEFILE = "../images/save.ark";

//Constantes de posiciones de los objetos
const Vector2D POS_WALL_L_ROOF = Vector2D(0, 0);
const Vector2D POS_WALL_R = Vector2D(WIN_WIDTH - WALL_WIDTH, 0);

const string maps[NUM_MAPS] = {
	{ "../images/level01.ark" },
	{ "../images/level02.ark" },
	{ "../images/level03.ark" }
};

class PlayState : public GameState {
public:
	PlayState(Game* game);
	virtual ~PlayState();

	virtual void update();
	virtual void render() ;
	virtual void handleEvents(SDL_Event& e);

	virtual bool OnEnter();
	virtual bool OnExit();

	//Destructora
	void deleteObjects();

	//Colisiones
	bool collidesBall(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector);
	bool collidesReward(const SDL_Rect& rect);

	//Variados
	void createReward(const SDL_Rect& rect);
	void powerUp(int type);
	void addLife() { vidas++; }
	void pierdeVida();
	void nextLevel();
	void setLevel(bool b) { nivel = b; }

	//Guardar y cargar
	void saveBool(bool b) { s = b; }
	void loadBool(bool b) { l = b; }
	void save();
	void load();
	void initObjectsFromFile(ifstream& f);


protected:
	SDL_Renderer *rend = nullptr;
	list<GameObject*> killObjects;

	bool nivel = false;
	bool win = false;
	bool lose = false;

	
	int vidas = 0;
	int level = 0;

private:
	void initObjects();
	void initMap();

	BlockMap* blockMap;
	list<GameObject*>::iterator mapIt, paddleIt, ballIt, lastIt;

	//Variables para la carga
	bool s = false;
	bool l = false;
	bool firstUpdate = false;
	int numRewards = 0, numLin;
	int code = 0;
	int tempCode = 0;

	
};
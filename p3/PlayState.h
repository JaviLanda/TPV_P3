#pragma once
#include "GameState.h"
#include "BlockMap.h"

const uint NUM_MAPS = 3;
const uint WALL_WIDTH = 40;
/*
const uint PADDLE_MOVE = 5;
const uint BALL_SIZE = 25;
const uint REWARD_W = 30;
const uint REWARD_H = 20;
const uint REWARD_CHANCE = 5;
*/

const string maps[NUM_MAPS] = {
	{ "../images/level01.ark" },
	{ "../images/level02.ark" },
	{ "../images/level03.ark" }
};

class PlayState : public GameState {
public:
	PlayState(Game* game);

	/*
	virtual void update() {};
	virtual void render() {};
	*/
	virtual bool handleEvent(SDL_Event& e);

	virtual bool OnEnter();
	virtual bool OnExit();

protected:
	SDL_Renderer *rend = nullptr;

	int puntuacion = 0;
	int vidas = 0;
	int level = 0;

private:
	void initObjects();
	void initMap();

	BlockMap* blockMap;
	list<GameObject*>::iterator mapIt, paddleIt, ballIt, lastIt;
};
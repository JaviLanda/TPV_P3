#include "RewardX2.h"
#include "Game.h"

RewardX2::RewardX2(SDL_Renderer* r, Texture* text, int x, int y, GameState* g) : Reward(r, text, x,  y, g) {
	fRow = 3;
	type = SmallPaddle;
}

RewardX2::~RewardX2(){}
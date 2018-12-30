#include "RewardX1.h"

RewardX1::RewardX1(SDL_Renderer* r, Texture* text, int x, int y, GameState* g) : Reward(r, text, x, y, g) {
	fRow = 1;
	type = BigPaddle;
}

RewardX1::~RewardX1() {}
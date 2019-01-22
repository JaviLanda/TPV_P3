#include "RewardX5.h"

RewardX5::RewardX5(SDL_Renderer* r, Texture* text, int x, int y, GameState* g) : Reward(r, text, x, y, g) {
	fRow = 2;
	type = Balas;
}

RewardX5::~RewardX5()
{
}

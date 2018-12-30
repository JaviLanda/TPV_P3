#include "RewardX3.h"

RewardX3::RewardX3(SDL_Renderer* r, Texture* text, int x, int y, GameState* g) : Reward(r, text, x, y, g) {
	fRow = 4;
	type = ExtraHp;
}

RewardX3::~RewardX3() {}
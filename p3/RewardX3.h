#pragma once
#include "Reward.h"
class RewardX3 : public Reward
{
public:
	RewardX3() {}
	RewardX3(SDL_Renderer* r, Texture* text, int x, int y, GameState* g);

	virtual ~RewardX3();
};


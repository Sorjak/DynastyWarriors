#pragma once
#include "BaseSystem.h"

#include "../Engine.h"

class PlayerInputSystem :
	public BaseSystem
{
public:
	PlayerInputSystem();
	~PlayerInputSystem();

	void update();

	void process(SDL_Event e);
};


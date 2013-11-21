#pragma once
#include "InputSystem.h"


#include "../Engine.h"

class PlayerInputSystem :
	public InputSystem
{
public:
	PlayerInputSystem();
	~PlayerInputSystem();

	void update();
};


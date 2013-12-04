#pragma once
#include "basesystem.h"

#include "../Engine.h"

class InputSystem :
	public BaseSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();

	SDL_Event mEvent;
	vector<BaseSystem*> inputList;
};


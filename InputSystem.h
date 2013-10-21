#pragma once
#include "basesystem.h"

#include "Engine.h"
#include "WASDInputComponent.h"

class InputSystem :
	public BaseSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();

};


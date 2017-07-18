#pragma once
#include "basesystem.h"

#include "../Components/ExpirationComponent.h"

#include "../Engine.h"

class ExpiresSystem :
	public BaseSystem
{
public:
	ExpiresSystem();
	~ExpiresSystem();

	void update();
};


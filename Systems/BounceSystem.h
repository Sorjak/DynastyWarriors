#pragma once
#include "basesystem.h"

#include "../Components/DimensionComponent.h"
#include "../Components/VelocityComponent.h"

class BounceSystem :
	public BaseSystem
{
public:
	BounceSystem(int, int);
	~BounceSystem();

	void update();

	int mWidth;
	int mHeight;
};


#pragma once
#include "basesystem.h"

#include "DimensionComponent.h"
#include "VelocityComponent.h"

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


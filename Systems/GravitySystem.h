#pragma once
#include "basesystem.h"

#include "../Components/VelocityComponent.h"
#include "../Components/PlayerMotionComponent.h"

#include "../Engine.h"

class GravitySystem :
	public BaseSystem
{
public:
	GravitySystem(float);
	~GravitySystem();

	void update();

	Vector2D* mStrength;
};


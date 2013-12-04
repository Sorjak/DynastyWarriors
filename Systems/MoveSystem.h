#pragma once
#include "basesystem.h"

#include "../Components/DimensionComponent.h"
#include "../Components/VelocityComponent.h"

#include "../Engine.h"

class MoveSystem :
	public BaseSystem
{
public:
	MoveSystem();
	~MoveSystem();

	void update();

	static const int MAX_H_SPEED = 150;
	static const int MAX_V_SPEED = 300;
};


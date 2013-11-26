#pragma once
#include "BaseSystem.h"

#include "../Components/DimensionComponent.h"
#include "../Components/VelocityComponent.h"

class CollisionSystem :
	public BaseSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void update();

};


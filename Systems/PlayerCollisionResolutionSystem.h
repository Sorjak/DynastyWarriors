#pragma once
#include "basesystem.h"

#include "../Components/DimensionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/StateComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/PlayerMotionComponent.h"

class PlayerCollisionResolutionSystem :
	public BaseSystem
{
public:
	PlayerCollisionResolutionSystem();
	~PlayerCollisionResolutionSystem();

	void update();

	string getPrettyDirection(int);

	enum DIRECTIONS { LEFT = 1, TOP = 2, RIGHT = 4, BOTTOM = 8 };
};


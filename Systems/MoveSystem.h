#pragma once
#include "basesystem.h"

#include "../Components/DimensionComponent.h"
#include "../Components/VelocityComponent.h"

class MoveSystem :
	public BaseSystem
{
public:
	MoveSystem();
	~MoveSystem();

	void update();

};


#pragma once
#include "basesystem.h"

#include "DimensionComponent.h"
#include "VelocityComponent.h"

class MoveSystem :
	public BaseSystem
{
public:
	MoveSystem();
	~MoveSystem();

	void update();

};

